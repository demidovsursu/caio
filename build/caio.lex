%option noyywrap
%option bison-locations noline
%top{
#include "caio.h"
%}

%{
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
^"%type"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return 1004; }
^"%code"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return 1001; }
^"%option"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return 1003; }
^"%using"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return 1005; }
^"%operator"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return 1002; }
^{ident}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 97 "caio.caio"
           yylval.f1_=yytext; BEGIN(S_RE2); return (1016); 	}
\d+	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1018; }
<INITIAL,S_LEX2>"%{"|"{"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 100 "caio.caio"
                           yy_push_state(S_CODE);  return (1006); 	}
<INITIAL,S_GRM>[a-zA-Z\xC0-\xFF\xB8\xA8][-_a-zA-Z0-9\xC0-\xFF\xB8\xA8]*	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1016; }
<INITIAL,S_LEX2,S_GRM,S_TOKEN>{cliteral}|{sliteral}|{qliteral}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 102 "caio.caio"
                                                                 
            yylval.f1_=yytext; if(YYSTATE==S_TOKEN) yy_pop_state(); return (1022); 	}
[ \t]	;
^"%%".*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 105 "caio.caio"
            if(yylex_flag) { BEGIN(S_LEX); caio_mode=M_LEX; return (1014); }
            if(yyparse_flag) { BEGIN(S_GRM); caio_mode=M_GRM; return (1013); }
            BEGIN(S_CODE); caio_mode=M_CODE; return (1012);
          	}
"//".*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '\n'; }
<S_LEX2>"//".*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 110 "caio.caio"
                   BEGIN(S_LEX); return ('\n'); 	}
<INITIAL,S_LEX2,S_GRM,S_NODE,S_LIST,S_TERM>"/*"(.|\n)*?"*/"	;
<S_RE2>[ \t]	;
<S_RE2>\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '\n'; }
<S_RE2>R\"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 115 "caio.caio"
          yylval.f1_=reinput(YY_SCANNER,0); BEGIN(INITIAL);  return (1019); 	}
<S_RE2>.	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 116 "caio.caio"
           re_str=""; yyunput(yytext[0]); BEGIN(INITIAL); yy_push_state(S_RE); 	}
<S_RE>\\.	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 118 "caio.caio"
            re_str+=yytext; 	}
<S_RE>\"([^\"\\\n]|\\.)*\"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 119 "caio.caio"
         re_str+=yytext; 	}
<S_RE>\[([^\]\\\n]|\\.)*\]	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 120 "caio.caio"
         re_str+=yytext; 	}
<S_RE>[ \t]	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 121 "caio.caio"
              yylval.f1_=re_str; yy_pop_state(); return (1019); 	}
<S_RE>.	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 122 "caio.caio"
          re_str+=yytext; 	}
<S_RE>\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 123 "caio.caio"
           yylval.f1_=re_str; yy_pop_state(); yyunput('\n'); return (1019); 	}
<S_LEX>^"%%".*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 125 "caio.caio"
                   if(yyparse_flag) { BEGIN(S_GRM); caio_mode=M_GRM; return (1013); }
                   BEGIN(S_CODE); caio_mode=M_CODE; return (1012);
            	}
<S_LEX>^"<"/[^<]	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 128 "caio.caio"
                   BEGIN(S_STATE); return ('<'); 	}
<S_LEX2>"<"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 129 "caio.caio"
              yy_push_state(S_TERM); return ('<'); 	}
<S_LEX>R\"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 130 "caio.caio"
          yylval.f1_=reinput(YY_SCANNER,0); BEGIN(S_LEX2);
             return (1019); 
           	}
<S_LEX>[ \t]	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 133 "caio.caio"
               BEGIN(S_LEX2); 	}
<S_LEX>[ \t]*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '\n'; }
<S_LEX>.	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 135 "caio.caio"
           re_str=""; yyunput(yytext[0]); BEGIN(S_LEX2); yy_push_state(S_RE); 	}
<S_LEX2>[ \t]	;
<S_LEX2,S_STATE>\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 137 "caio.caio"
                     BEGIN(S_LEX); return ('\n'); 	}
<S_STATE>{ident}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1016; }
<S_STATE>[ \t]	;
<S_STATE>">"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 141 "caio.caio"
               BEGIN(S_LEX); return ('>'); 	}
<S_GRM,S_TERM>[ \t\r\n]	;
<S_TERM>">"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 144 "caio.caio"
              yy_pop_state(); return ('>'); 	}
<S_TERM>"("	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 145 "caio.caio"
              yy_push_state(S_LIST); return ('('); 	}
<S_TERM,S_CODE,S_LIST>{char_const}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 146 "caio.caio"
                                     yylval.f1_=yytext; return (1015); 	}
<S_TERM,S_CODE,S_LIST>{string_const}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 147 "caio.caio"
                                       yylval.f1_=yytext; return (1015); 	}
<S_TERM,S_CODE,S_LIST>R\"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 148 "caio.caio"
                         yylval.f1_=reinput(YY_SCANNER,1); return (1015); 	}
<S_CODE>default	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return 1007; }
<S_CODE>":"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return ':'; }
<S_CODE>match	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 151 "caio.caio"
                yy_push_state(S_LIST); return (1008); 	}
<S_CODE>visitor	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 152 "caio.caio"
                  yy_push_state(S_NODE); return (1011); 	}
<S_CODE>return/[\ \t\n\r]*['\"?]	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 153 "caio.caio"
           if(caio_mode==M_LEX) yy_push_state(S_TOKEN); yylval.f1_=yytext; return (1016); 	}
<S_CODE>token[\ \t\n\r]*/['\"?]	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 154 "caio.caio"
           yy_push_state(S_TOKEN); 	}
<S_CODE>rule	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 155 "caio.caio"
               yy_push_state(S_NODE); return (1009); 	}
<S_CODE>visit	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 156 "caio.caio"
                yy_push_state(S_NODE); return (1010); 	}
<S_TERM,S_CODE,S_LIST>{ident}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1016; }
<S_TERM,S_CODE,S_LIST>{number}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1015; }
<S_LIST,S_CODE>"$$"|"@$"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1020; }
<S_TERM,S_LIST,S_CODE>"$"[0-9]+	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1020; }
<S_GRM,S_NODE,S_LIST>"//".*\n	;
<S_GRM>^"%%".*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 163 "caio.caio"
                   BEGIN(S_CODE); caio_mode=M_CODE; return (1012); 	}
<S_GRM>"{"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 164 "caio.caio"
             if(bnf_flag!=1) { yy_push_state(S_CODE); return (1006); }  return ('{'); 	}
<S_GRM>"%{"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 165 "caio.caio"
              yy_push_state(S_CODE); return (1006); 	}
<S_GRM>!	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '|'; }
<S_GRM>"."	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return ';'; }
<S_GRM>"(/"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '['; }
<S_GRM>"/)"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return ']'; }
<S_GRM>"(:"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '{'; }
<S_GRM>":)"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '}'; }
<S_GRM>:	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '='; }
<S_GRM>"/"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return '|'; }
<S_GRM>"<"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 174 "caio.caio"
             yy_push_state(S_TERM); return ('<'); 	}
<S_LIST>"{"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 176 "caio.caio"
              BEGIN(S_CODE); return ('{'); 	}
<S_LIST>")"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 177 "caio.caio"
              yy_pop_state(); return (')'); 	}
<S_LIST>"("	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 178 "caio.caio"
              yy_push_state(S_LIST); return ('('); 	}
<S_LIST>[ \t\n]+	;
<S_NODE>":"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 181 "caio.caio"
              yy_pop_state(); return (':'); 	}
<S_NODE>"{"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 182 "caio.caio"
              BEGIN(S_CODE); return ('{'); 	}
<S_NODE>{ident}	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1016; }
<S_NODE>[ \t\n]	;
<S_CODE>"{"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 186 "caio.caio"
              yy_push_state(S_CODE); return ('{'); 	}
<S_CODE>"}"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 187 "caio.caio"
              if(state_.size()>0) yy_pop_state(); return ('}'); 	}
<S_CODE>"%}"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 188 "caio.caio"
               if(state_.size()>0 && yy_top_state()!=S_CODE) { yy_pop_state(); return ('}');} yyunput('}'); yylval.f1_="%"s; return (1017); 	}
<S_CODE,S_TOKEN>[ \t\n]+	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1021; }
<S_CODE>"/*".*?"*/"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 190 "caio.caio"
                      yylval.f1_=" "; return (1021); 	}
<S_CODE>"/*"(.|\n)*?"*/"	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 191 "caio.caio"
                           yylval.f1_="\n"; return (1021); 	}
<S_CODE>"//".*\n	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 192 "caio.caio"
                   yylval.f1_="\n"; return (1021); 	}
<S_LIST>","	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); return ','; }
<S_CODE,S_LIST>.	{ yyclear_attr(yylval); set_yyloc(lineno(),columno()); yylval.f1_=yytext;  return 1017; }
<S_TOKEN>.	{ yyclear_attr(yylval); set_yyloc(lineno(),columno());
	#line 195 "caio.caio"
             yy_pop_state(); yylval.f1_=yytext; return (1017); 	}
<INITIAL,S_CODE,S_GRM,S_LEX,S_LEX2,S_LIST,S_NODE,S_RE,S_RE2,S_STATE,S_TERM,S_TOKEN>.|\n	return yyliteral(yytext);
%%
void yystart(FILE *f)
{ yyrestart(f);
}
void yystart(std::istream& s)
{ yyrestart(s);
}
