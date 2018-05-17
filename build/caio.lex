%option noyywrap
%option bison-locations
%top{
#include "caio.h"
%}

%{
enum Caio_mode { M_DECL, M_LEX, M_GRM, M_CODE };
int caio_mode=M_DECL;
string re_str,code_dest;
static string reinput(FlexLexer& scanner, int nl)
{ string re="R\"";
  int k=0; 
  int r=0,c;
  bool err=0;
  while((c=scanner.input())!=0)
  { re+=char(c);
    if(c=='\n' && !nl) break;
    if(c=='(') break;
    ++k;
    if(r==0) r=c;
    else if(r!=c) break;
  }
  if(c=='(') 
  {
    int kk=-1;
    while((c=scanner.input())!=0)
    { re+=char(c);
      if(c=='\n' && !nl) break;
      if(c==')') kk=k;
      else if(kk==0 && c=='"') break;
      else if(kk>0 && c==r) --kk;
      else kk=-1;
    }
    if(c!='"' || re.size()<=5+2*k) err=1;
  }
  else err=1;
  if(err) yyerror(scanner.lineno(),scanner.columno(),"RE error");
  return re;
}
%}
%x S_CODE S_GRM S_LEX S_LEX2 S_LIST S_NODE S_RE S_RE2 S_STATE S_TERM S_TOKEN
cliteral	'([^'\\\n\t]|\\[^\n\t])+'
sliteral	\"([^\"\\\n\t]|\\[^\n\t])+\"
qliteral	\?[^?\n\ \t]+\?
ident	[_a-zA-Z][_a-zA-Z0-9]*
number	\d+[a-zA-Z0-9']*|\d[0-9']*(\.[0-9']*)?([eE][-+]?\d+[a-zA-Z0-9]*)?
char_const	'([^\\'\n]|\\(x[a-fA-F0-9]+|[0-9]+|.))'
string_const	\"([^\\\"\n]|\\.)*\"
%%
^"%type"	{ set_yyloc(lineno(),columno()); return 1004; }
^"%code"	{ set_yyloc(lineno(),columno()); return 1001; }
^"%option"	{ set_yyloc(lineno(),columno()); return 1003; }
^"%operator"	{ set_yyloc(lineno(),columno()); return 1002; }
^{ident}	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=yytext; BEGIN(S_RE2); return (1015); 	}
\d+	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1017; }
<INITIAL,S_LEX2>"%{"|"{"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_CODE);  return (1005); 	}
<INITIAL,S_GRM>[a-zA-Z\xC0-\xFF\xB8\xA8][-_a-zA-Z0-9\xC0-\xFF\xB8\xA8]*	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1015; }
<INITIAL,S_LEX2,S_GRM,S_TOKEN>{cliteral}|{sliteral}|{qliteral}	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 
            yylval.f1_=yytext; if(YYSTATE==S_TOKEN) yy_pop_state(); return (1021); 	}
[ \t]	;
^"%%".*\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 if(yylex_flag) { BEGIN(S_LEX); caio_mode=M_LEX; return (1013); }
            if(yyparse_flag) { BEGIN(S_GRM); caio_mode=M_GRM; return (1012); }
            BEGIN(S_CODE); caio_mode=M_CODE; return (1011);
          	}
.|\n	{ clear_attr(yylval); return yyliteral(yytext); }
"//".*\n	{ set_yyloc(lineno(),columno()); return '\n'; }
<S_LEX2>"//".*\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_LEX); return ('\n'); 	}
<INITIAL,S_LEX2,S_GRM,S_NODE,S_LIST,S_TERM>"/*"(.|\n)*?"*/"	;
<S_RE2>[ \t]	;
<S_RE2>\n	{ set_yyloc(lineno(),columno()); return '\n'; }
<S_RE2>R\"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=reinput(YY_SCANNER,0); BEGIN(INITIAL);  return (1018); 	}
<S_RE2>.	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 re_str=""; yyunput(yytext[0]); BEGIN(INITIAL); yy_push_state(S_RE); 	}
<S_RE>\\.	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 re_str+=yytext; 	}
<S_RE>\"([^\"\\\n]|\\.)*\"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 re_str+=yytext; 	}
<S_RE>\[([^\]\\\n]|\\.)*\]	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 re_str+=yytext; 	}
<S_RE>[ \t]	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=re_str; yy_pop_state(); return (1018); 	}
<S_RE>.	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 re_str+=yytext; 	}
<S_RE>\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=re_str; yy_pop_state(); yyunput('\n'); return (1018); 	}
<S_LEX>^"%%".*\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 if(yyparse_flag) { BEGIN(S_GRM); caio_mode=M_GRM; return (1012); }
                   BEGIN(S_CODE); caio_mode=M_CODE; return (1011);
            	}
<S_LEX>^"<"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_STATE); return ('<'); 	}
<S_LEX2>"<"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_TERM); return ('<'); 	}
<S_LEX>R\"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=reinput(YY_SCANNER,0); BEGIN(S_LEX2);
             return (1018); 
           	}
<S_LEX>[ \t]	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_LEX2); 	}
<S_LEX>[ \t]*\n	{ set_yyloc(lineno(),columno()); return '\n'; }
<S_LEX>.	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 re_str=""; yyunput(yytext[0]); BEGIN(S_LEX2); yy_push_state(S_RE); 	}
<S_LEX2>[ \t]	;
<S_LEX2,S_STATE>\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_LEX); return ('\n'); 	}
<S_LEX2>.	{ clear_attr(yylval); return yyliteral(yytext); }
<S_STATE>{ident}	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1015; }
<S_STATE>[ \t]	;
<S_STATE>">"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_LEX); return ('>'); 	}
<S_STATE>.	{ clear_attr(yylval); return yyliteral(yytext); }
<S_GRM,S_TERM>[ \t\r\n]	;
<S_TERM>">"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_pop_state(); return ('>'); 	}
<S_TERM>"("	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_LIST); return ('('); 	}
<S_TERM,S_CODE,S_LIST>{char_const}	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=yytext; return (1014); 	}
<S_TERM,S_CODE,S_LIST>{string_const}	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=yytext; return (1014); 	}
<S_TERM,S_CODE,S_LIST>R\"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=reinput(YY_SCANNER,1); return (1014); 	}
<S_CODE>default	{ set_yyloc(lineno(),columno()); return 1006; }
<S_CODE>":"	{ set_yyloc(lineno(),columno()); return ':'; }
<S_CODE>match	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_LIST); return (1007); 	}
<S_CODE>visitor	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_NODE); return (1010); 	}
<S_CODE>return/[\ \t\n\r]*['\"?]	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 if(caio_mode==M_LEX) yy_push_state(S_TOKEN); yylval.f1_=yytext; return (1015); 	}
<S_CODE>token[\ \t\n\r]*/['\"?]	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_TOKEN); 	}
<S_CODE>rule	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_NODE); return (1008); 	}
<S_CODE>visit	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_NODE); return (1009); 	}
<S_TERM,S_CODE,S_LIST>{ident}	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1015; }
<S_TERM,S_CODE,S_LIST>{number}	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1014; }
<S_LIST,S_CODE>"$$"	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1019; }
<S_TERM,S_LIST,S_CODE>"$"[0-9]+	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1019; }
<S_TERM>.	{ clear_attr(yylval); return yyliteral(yytext); }
<S_GRM,S_NODE,S_LIST>"//".*\n	;
<S_GRM>^"%%".*\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_CODE); caio_mode=M_CODE; return (1011); 	}
<S_GRM>"{"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 if(bnf_flag!=1) { yy_push_state(S_CODE); return (1005); }  return ('{'); 	}
<S_GRM>"%{"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_CODE); return (1005); 	}
<S_GRM>!	{ set_yyloc(lineno(),columno()); return '|'; }
<S_GRM>"."	{ set_yyloc(lineno(),columno()); return ';'; }
<S_GRM>"(/"	{ set_yyloc(lineno(),columno()); return '['; }
<S_GRM>"/)"	{ set_yyloc(lineno(),columno()); return ']'; }
<S_GRM>"(:"	{ set_yyloc(lineno(),columno()); return '{'; }
<S_GRM>":)"	{ set_yyloc(lineno(),columno()); return '}'; }
<S_GRM>:	{ set_yyloc(lineno(),columno()); return '='; }
<S_GRM>"/"	{ set_yyloc(lineno(),columno()); return '|'; }
<S_GRM>"<"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_TERM); return ('<'); 	}
<S_GRM>.	{ clear_attr(yylval); return yyliteral(yytext); }
<S_LIST>"{"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_CODE); return ('{'); 	}
<S_LIST>")"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_pop_state(); return (')'); 	}
<S_LIST>"("	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_LIST); return ('('); 	}
<S_LIST>[ \t\n]+	;
<S_NODE>":"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_pop_state(); return (':'); 	}
<S_NODE>"{"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 BEGIN(S_CODE); return ('{'); 	}
<S_NODE>{ident}	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1015; }
<S_NODE>[ \t\n]	;
<S_NODE>.	{ clear_attr(yylval); return yyliteral(yytext); }
<S_CODE>"{"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_push_state(S_CODE); return ('{'); 	}
<S_CODE>"}"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 if(state_.size()>0) yy_pop_state(); return ('}'); 	}
<S_CODE>"%}"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 if(state_.size()>0 && yy_top_state()!=S_CODE) { yy_pop_state(); return ('}');} yyunput('}'); yylval.f1_="%"s; return (1016); 	}
<S_CODE,S_TOKEN>[ \t\n]+	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1020; }
<S_CODE>"/*".*?"*/"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_=" "; return (1020); 	}
<S_CODE>"/*"(.|\n)*?"*/"	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_="\n"; return (1020); 	}
<S_CODE>"//".*\n	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yylval.f1_="\n"; return (1020); 	}
<S_LIST>","	{ set_yyloc(lineno(),columno()); return ','; }
<S_CODE,S_LIST>.	{ set_yyloc(lineno(),columno()); yylval.f1_=yytext; return 1016; }
<S_TOKEN>.	{ clear_attr(yylval);
	set_yyloc(lineno(),columno());
	 yy_pop_state(); yylval.f1_=yytext; return (1016); 	}
%%
void yystart(FILE *f)
{ yyrestart(f);
}
void yystart(std::istream& s)
{ yyrestart(s);
}
