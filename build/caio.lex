%option noyywrap
%option bison-bridge noline
%top{
#include "caio.h"
#define YY_USER_ACTION yysetloc();
%}

%class {
public:
  std::vector<std::string> filenames;
  int activefile;
%}

%init {
  filenames.push_back("");
  activefile=0;
%}

%class {
public: YYLTYPE yylloc;
  void yysetloc(){
    yylloc.first.line=lineno();
    yylloc.first.file=activefile;
    yylloc.first.column=short(columno()+1);
    yylloc.last.line=lineno();
    yylloc.last.file=activefile;
    yylloc.last.column=short(columno()+size());
  }
%}

%{
int caio_mode=M_DECL;
string re_str,code_dest;
static string reinput(yyFlexLexer& scanner, int nl)
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
  if(err) 
  { yyerror(&(scanner.yylloc),&scanner,"RE error");
  }
  return re;
}
%}
%x S_CODE S_GRM S_LEX S_LEX2 S_LIST S_NODE S_RE S_RE2 S_STATE S_TERM S_TOKEN
cliteral	'([^'\\\n\t]|\\[^\n\t])+'
sliteral	\"([^\"\\\n\t]|\\[^\n\t])+\"
qliteral	\?[^?\n\ \t]+\?
symbol	[a-zA-Z\xC0-\xFF\xB8\xA8][-._a-zA-Z0-9\xC0-\xFF\xB8\xA8]*
symbolid	[a-zA-Z\xC0-\xFF\xB8\xA8][_a-zA-Z0-9\xC0-\xFF\xB8\xA8]*
ident	[_a-zA-Z][_a-zA-Z0-9]*
number	\d+[a-zA-Z0-9']*|\d[0-9']*(\.[0-9']*)?([eE][-+]?\d+[a-zA-Z0-9]*)?
char_const	'([^\\'\n]|\\(x[a-fA-F0-9]+|[0-9]+|.))'
string_const	\"([^\\\"\n]|\\.)*\"
%%
^"%type"	{ return 1004; }
^"%code"	{ return 1001; }
^"%option"	{ return 1003; }
^"%using"	{ return 1005; }
^"%operator"	{ return 1002; }
^{ident}	{
	#line 119 "caio.caio"
                            yylval.f1_=yytext; BEGIN(S_RE2); return (1016); 	}
\d+	{ yylval.f1_=yytext;  return 1018; }
<INITIAL,S_LEX2>"%{"|"{"	{
	#line 121 "caio.caio"
                                     yy_push_state(S_CODE);  return (1006); 	}
<INITIAL,S_GRM>{symbol}	{ yylval.f1_=yytext;  return 1016; }
<INITIAL,S_LEX2,S_GRM,S_TOKEN>{cliteral}|{sliteral}|{qliteral}	{
	#line 123 "caio.caio"
                                                                 
            yylval.f1_=yytext; if(YYSTATE==S_TOKEN) yy_pop_state(); return (1022); 	}
[ \t]	;
^"%%".*\n	{
	#line 126 "caio.caio"
            if(yylex_flag) { BEGIN(S_LEX); caio_mode=M_LEX; return (1014); }
            if(yyparse_flag) { BEGIN(S_GRM); caio_mode=M_GRM; return (1013); }
            BEGIN(S_CODE); caio_mode=M_CODE; return (1012);
          	}
"//".*\n	{ return '\n'; }
<S_LEX2>"//".*\n	{
	#line 131 "caio.caio"
                   BEGIN(S_LEX); return ('\n'); 	}
<INITIAL,S_LEX2,S_GRM,S_NODE,S_LIST,S_TERM>"/*"(.|\n)*?"*/"	;
<S_RE2>[ \t]	;
<S_RE2>\n	{ return '\n'; }
<S_RE2>R\"	{
	#line 136 "caio.caio"
                  yylval.f1_=reinput(YY_SCANNER,0); BEGIN(INITIAL);  return (1019); 	}
<S_RE2>.	{
	#line 137 "caio.caio"
           re_str=""; yyunput(yytext[0]); BEGIN(INITIAL); yy_push_state(S_RE); 	}
<S_RE>\\.	{
	#line 139 "caio.caio"
            re_str+=yytext; 	}
<S_RE>\"([^\"\\\n]|\\.)*\"	{
	#line 140 "caio.caio"
                                  re_str+=yytext; 	}
<S_RE>\[([^\]\\\n]|\\.)*\]	{
	#line 141 "caio.caio"
                                  re_str+=yytext; 	}
<S_RE>[ \t]	{
	#line 142 "caio.caio"
              yylval.f1_=re_str; yy_pop_state(); return (1019); 	}
<S_RE>.	{
	#line 143 "caio.caio"
          re_str+=yytext; 	}
<S_RE>\n	{
	#line 144 "caio.caio"
           yylval.f1_=re_str; yy_pop_state(); yyunput('\n'); return (1019); 	}
<S_LEX>^"%%".*\n	{
	#line 146 "caio.caio"
                   if(yyparse_flag) { BEGIN(S_GRM); caio_mode=M_GRM; return (1013); }
                   BEGIN(S_CODE); caio_mode=M_CODE; return (1012);
            	}
<S_LEX>^"<"/[^<]	{
	#line 149 "caio.caio"
                   BEGIN(S_STATE); return ('<'); 	}
<S_LEX2>"<"	{
	#line 150 "caio.caio"
              yy_push_state(S_TERM); return ('<'); 	}
<S_LEX>R\"	{
	#line 151 "caio.caio"
                  yylval.f1_=reinput(YY_SCANNER,0); BEGIN(S_LEX2);
             return (1019); 
           	}
<S_LEX>[ \t]	{
	#line 154 "caio.caio"
               BEGIN(S_LEX2); 	}
<S_LEX>[ \t]*\n	{ return '\n'; }
<S_LEX>.	{
	#line 156 "caio.caio"
           re_str=""; yyunput(yytext[0]); BEGIN(S_LEX2); yy_push_state(S_RE); 	}
<S_LEX2>[ \t]	;
<S_LEX2,S_STATE>\n	{
	#line 158 "caio.caio"
                     BEGIN(S_LEX); return ('\n'); 	}
<S_STATE>{ident}	{ yylval.f1_=yytext;  return 1016; }
<S_STATE>[ \t]	;
<S_STATE>">"	{
	#line 162 "caio.caio"
               BEGIN(S_LEX); return ('>'); 	}
<S_GRM,S_TERM>[ \t\r\n]	;
<S_TERM>">"	{
	#line 165 "caio.caio"
              yy_pop_state(); return ('>'); 	}
<S_TERM>"("	{
	#line 166 "caio.caio"
              yy_push_state(S_LIST); return ('('); 	}
<S_TERM,S_CODE,S_LIST>{char_const}	{
	#line 167 "caio.caio"
                                     yylval.f1_=yytext; return (1015); 	}
<S_TERM,S_CODE,S_LIST>{string_const}	{
	#line 168 "caio.caio"
                                       yylval.f1_=yytext; return (1015); 	}
<S_TERM,S_CODE,S_LIST>R\"	{
	#line 169 "caio.caio"
                                 yylval.f1_=reinput(YY_SCANNER,1); return (1015); 	}
<S_CODE>default	{ return 1007; }
<S_CODE>":"	{ return ':'; }
<S_CODE>match	{
	#line 172 "caio.caio"
                yy_push_state(S_LIST); return (1008); 	}
<S_CODE>visitor	{
	#line 173 "caio.caio"
                  yy_push_state(S_NODE); return (1011); 	}
<S_CODE>return/[\ \t\n\r]*['\"?]	{
	#line 174 "caio.caio"
                                       if(caio_mode==M_LEX) yy_push_state(S_TOKEN); yylval.f1_=yytext; return (1016); 	}
<S_CODE>token[\ \t\n\r]*/['\"?]	{
	#line 175 "caio.caio"
                                      yy_push_state(S_TOKEN); 	}
<S_CODE>rule	{
	#line 176 "caio.caio"
               yy_push_state(S_NODE); return (1009); 	}
<S_CODE>visit	{
	#line 177 "caio.caio"
                yy_push_state(S_NODE); return (1010); 	}
<S_TERM,S_CODE,S_LIST>{ident}	{ yylval.f1_=yytext;  return 1016; }
<S_TERM,S_CODE,S_LIST>{number}	{ yylval.f1_=yytext;  return 1015; }
<S_LIST,S_CODE>"$$"|"@$"	{ yylval.f1_=yytext;  return 1020; }
<S_TERM,S_LIST,S_CODE>"$"[0-9]+|"$"\[({symbol}|{cliteral}|{sliteral}|{qliteral})\]|"$"{symbolid}	{ yylval.f1_=yytext;  return 1020; }
<S_GRM,S_NODE,S_LIST>"//".*\n	;
<S_GRM>^"%%".*\n	{
	#line 184 "caio.caio"
                   BEGIN(S_CODE); caio_mode=M_CODE; return (1012); 	}
<S_GRM>"{"	{
	#line 185 "caio.caio"
             if(bnf_flag!=1) { yy_push_state(S_CODE); return (1006); }  return ('{'); 	}
<S_GRM>"%{"	{
	#line 186 "caio.caio"
              yy_push_state(S_CODE); return (1006); 	}
<S_GRM>!	{ return '|'; }
<S_GRM>"."	{ return ';'; }
<S_GRM>"(/"	{ return '['; }
<S_GRM>"/)"	{ return ']'; }
<S_GRM>"(:"	{ return '{'; }
<S_GRM>":)"	{ return '}'; }
<S_GRM>"/"	{ return '|'; }
<S_GRM>"<"	{
	#line 194 "caio.caio"
             yy_push_state(S_TERM); return ('<'); 	}
<S_LIST>"{"	{
	#line 196 "caio.caio"
              BEGIN(S_CODE); return ('{'); 	}
<S_LIST>")"	{
	#line 197 "caio.caio"
              yy_pop_state(); return (')'); 	}
<S_LIST>"("	{
	#line 198 "caio.caio"
              yy_push_state(S_LIST); return ('('); 	}
<S_LIST>[ \t\n]+	;
<S_NODE>":"	{
	#line 201 "caio.caio"
              yy_pop_state(); return (':'); 	}
<S_NODE>"{"	{
	#line 202 "caio.caio"
              BEGIN(S_CODE); return ('{'); 	}
<S_NODE>{ident}	{ yylval.f1_=yytext;  return 1016; }
<S_NODE>[ \t\n]	;
<S_CODE>"{"	{
	#line 206 "caio.caio"
              yy_push_state(S_CODE); return ('{'); 	}
<S_CODE>"}"	{
	#line 207 "caio.caio"
              if(state_.size()>0) yy_pop_state(); return ('}'); 	}
<S_CODE>"%}"	{
	#line 208 "caio.caio"
               if(state_.size()>0 && yy_top_state()!=S_CODE) { yy_pop_state(); return ('}');} yyunput('}'); yylval.f1_="%"s; return (1017); 	}
<S_CODE,S_TOKEN>[ \t\n]+	{ yylval.f1_=yytext;  return 1021; }
<S_CODE>"/*".*?"*/"	{
	#line 210 "caio.caio"
                      yylval.f1_=" "; return (1021); 	}
<S_CODE>"/*"(.|\n)*?"*/"	{
	#line 211 "caio.caio"
                           yylval.f1_="\n"; return (1021); 	}
<S_CODE>"//".*\n	{
	#line 212 "caio.caio"
                   yylval.f1_="\n"; return (1021); 	}
<S_LIST>","	{ return ','; }
<S_CODE,S_LIST>.	{ yylval.f1_=yytext;  return 1017; }
<S_TOKEN>.	{
	#line 215 "caio.caio"
             yy_pop_state(); yylval.f1_=yytext; return (1017); 	}
<INITIAL,S_CODE,S_GRM,S_LEX,S_LEX2,S_LIST,S_NODE,S_RE,S_RE2,S_STATE,S_TERM,S_TOKEN>.|\n	return yyliteral(yytext);
%%

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner) {
  yyscanner_t* scanp=static_cast<yyscanner_t*>(scanner);
  yyclear_attr(*lvalp);
  int t=scanp->yylex(*lvalp);
  *llocp=scanp->yylloc;
  return t;
}

const char *yylex_filename(void* scanner, int i)
{ yyscanner_t* scanp=static_cast<yyscanner_t*>(scanner);
  if(i>=scanp->filenames.size()) return "";
  if(i<0) i=scanp->activefile;
  return scanp->filenames[i].c_str();
}
void yylex_init(yyscan_t *scanner, FILE *f, const std::string& n)
{ yyscanner_t* scanp=new yyscanner_t;
  *scanner = static_cast<yyscan_t>(scanp);
  scanp->in(f);
  scanp->filenames[0]=n;
}
void yylex_init(yyscan_t *scanner, std::istream &s, const std::string& n)
{ yyscanner_t* scanp=new yyscanner_t;
  *scanner = static_cast<yyscan_t>(scanp);
  scanp->in(s);
  scanp->filenames[0]=n;
}
