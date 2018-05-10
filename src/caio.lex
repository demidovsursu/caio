%option noyywrap
%{
#include <iostream>
#include <string>
#include "caio/asttypes.h"
using namespace ast;
typedef Value<std::string> sVal;
#include "domains.h"

#include "y.tab.h"
#include <string>
//#include <iostream>
//#include <map>
using namespace std;
extern int bnf_flag;

enum Caio_mode { M_DECL, M_LEX, M_GRM, M_CODE };
int caio_mode=M_DECL;

string re_str,code_dest;
/*enum { SPLIT=1000,TYPE,OPTION,LCODE,CODE,OPERATOR,RETURN,
RULE,MATCH,VISIT,VISITOR,LEXEM,ID,TERMINAL,SPACES,REF,CONST,RE};
struct YYLVAL {
  string sval;
} yylval;*/
%}
%x S_LEX S_GRM S_CODE S_CODE2 S_LIST S_RE S_STATE S_RETURN S_TERM S_LEX2 S_NODE
%%
^"%type" { return TYPE; }
^"%code" { return CODE; }
^"%option" { return OPTION; }
^"%operator" { return OPERATOR; }
<INITIAL>[0-9]+ { yylval.sval=yytext; return NUMBER; }
<INITIAL,S_LEX2>"%{"|"{" { yy_push_state(S_CODE);  return LCODE; }
<INITIAL,S_GRM>[a-zA-Z\xC0-\xFF\xB8\xA8][-_a-zA-Z0-9\xC0-\xFF\xB8\xA8]* { yylval.sval=yytext; return ID; }
<INITIAL,S_LEX2,S_GRM,S_RETURN>'([^'\\\n\t]|\\[^\n\t])+'|\"([^"\\\n\t]|\\[^\n\t])+\"|\?[^?\n \t]+\? { yylval.sval=yytext; return TERMINAL; }
[ \t]  ;
^"%%".*\n { BEGIN(S_LEX); caio_mode=M_LEX; return SPLIT; }
.|\n return yytext[0]&0xFF;
"//".*\n { return '\n'; }
<S_LEX2>"//".*\n { BEGIN(S_LEX); return '\n'; }
<INITIAL,S_LEX2,S_GRM,S_NODE,S_LIST,S_RETURN,S_TERM>"/*"(.|\n)*?"*/" ;

<S_RE>\\. { re_str+=yytext; }
<S_RE>\"([^"\\\n]|\\.)*\" { re_str+=yytext; }
<S_RE>\[([^\]\\\n]|\\.)*\] { re_str+=yytext; }
<S_RE>[ \t] { yylval.sval=re_str; BEGIN(S_LEX2); return RE; }
<S_RE>. { re_str+=yytext; }
<S_RE>\n { yylval.sval=re_str; BEGIN(S_LEX2); yyunput('\n'); return RE; }

<S_LEX>^"%%".*\n { BEGIN(S_GRM); caio_mode=M_GRM; return SPLIT;}
<S_LEX>^"<" { BEGIN(S_STATE); return '<'; }
<S_LEX2>"<" { yy_push_state(S_TERM); return '<'; }
<S_LEX>R"\"(".*?")\""|R"\"_(".*?")_\"" { yylval.sval=yytext; BEGIN(S_LEX2); return RE; }
<S_LEX>[^ \t\n] { re_str=""; yyunput(yytext[0]); BEGIN(S_RE); }
<S_LEX>[ \t] ;
<S_LEX>\n return '\n';
<S_LEX2>[ \t] ;
<S_LEX2,S_STATE>\n { BEGIN(S_LEX); return '\n'; }
<S_LEX2>. return yytext[0]&0xFF;

<S_STATE>[_a-zA-Z][_a-zA-Z0-9]* {  yylval.sval=yytext; return ID; }
<S_STATE>[ \t] ;
<S_STATE>. return yytext[0]&0xff;

<S_GRM,S_TERM>[ \t\r\n] ;
<S_TERM>">" { yy_pop_state(); return '>'; }
<S_TERM>"(" { yy_push_state(S_LIST); return '('; }
<S_TERM,S_CODE,S_LIST>'([^\\'\n]|\\(x[a-fA-F0-9]+|[0-9]+|.))' { yylval.sval=yytext; return CONST; }
<S_TERM,S_CODE,S_LIST>\"([^\\"\n]|\\.)*\"|R"\"(".*?")\""|R"\"_(".*?")_\"" { yylval.sval=yytext; return CONST; }
<S_CODE>"match" { yy_push_state(S_LIST); return MATCH; }
<S_CODE>"visitor" { yy_push_state(S_NODE); return VISITOR; }
<S_CODE>"return"[ \t\n\r]*/['"?] { if(caio_mode==S_LEX) { yy_push_state(S_RETURN); return RETURN; } yylval.sval=yytext; return LEXEM; }
<S_CODE>"rule" { yy_push_state(S_NODE); return RULE; }
<S_CODE>"visit" { yy_push_state(S_NODE); return VISIT; }
<S_TERM,S_CODE,S_LIST>[_a-zA-Z][_a-zA-Z0-9]* { yylval.sval=yytext; return ID; }
<S_TERM,S_CODE,S_LIST>[0-9]+[a-zA-Z0-9']*|[0-9][0-9']*(\.[0-9']*)?([eE][-+]?[0-9]+[a-zA-Z0-9]*)? { yylval.sval=yytext; return CONST; }
<S_LIST,S_CODE>"$$" { yylval.sval=yytext; return REF; }
<S_TERM,S_LIST,S_CODE>"$"[0-9]+ { yylval.sval=yytext; return REF; }
<S_TERM>. { return yytext[0]&0xFF; }

<S_GRM,S_NODE,S_LIST,S_RETURN>"//".*\n ;
<S_GRM>^"%%".*\n { BEGIN(S_CODE); caio_mode=M_CODE; return SPLIT;}
<S_GRM>"{" { if(bnf_flag!=1) { yy_push_state(S_CODE); return LCODE; }  return '{'; }
<S_GRM>"%{" { yy_push_state(S_CODE); return LCODE; }
<S_GRM>! { return '|'; }
<S_GRM>"." { return ';'; }
<S_GRM>"(/" { return '['; }
<S_GRM>"/)" { return ']'; }
<S_GRM>"(:" { return '{'; }
<S_GRM>":)" { return '}'; }
<S_GRM>: { return '='; }
<S_GRM>"/" { return '|'; }
<S_GRM>"<" { yy_push_state(S_TERM); return '<'; }
<S_GRM>. return yytext[0]&0xFF;

<S_LIST>"{" { BEGIN(S_CODE); return '{'; }
<S_LIST>")" { yy_pop_state(); return ')'; }
<S_LIST>"(" { yy_push_state(S_LIST); return '('; }
<S_LIST>[ \t\n]+ ;

<S_NODE>":" { yy_pop_state(); return ':'; }
<S_NODE>"{" { BEGIN(S_CODE); return '{'; }
<S_NODE>[_a-zA-Z][_a-zA-Z0-9]* { yylval.sval=yytext; return ID; }
<S_NODE>[ \t\n] ;
<S_NODE>. { return yytext[0]&0xFF; }

<S_RETURN>[ \t\n] ;
<S_RETURN>; { yy_pop_state(); return ';'; }
<S_RETURN>. { return yytext[0]&0xFF; }

<S_CODE>"{" { yy_push_state(S_CODE); return '{'; }
<S_CODE>"}" { if(state_.size()>0) yy_pop_state(); return '}'; }
<S_CODE>"%}" { if(state_.size()>0 && yy_top_state()!=S_CODE) { yy_pop_state(); return '}';} yyunput('}'); yylval.sval="%"s; return LEXEM; }
<S_CODE>[ \t\n]+ { yylval.sval=yytext; return SPACES; }
<S_CODE>"/*".*?"*/" { yylval.sval=" "; return SPACES; }
<S_CODE>"/*"(.|\n)*?"*/" { yylval.sval="\n"; return SPACES; }
<S_CODE>"//".*\n { yylval.sval="\n"; return SPACES; }
<S_LIST>"," { return ','; }
<S_CODE,S_LIST>. { yylval.sval=yytext; return LEXEM; }
%%
int fromfile(FILE *f)
{ yyrestart(f);
}
/*map<int,string> tokens;
map<int,string> states;
int main()
{
  for(int i=32;i<=255;++i)
    tokens[i]=string(1,char(i));
   states[0]="INITIAL";
   states[S_LEX]="S_LEX";
   states[S_GRM]="S_GRM";
   states[S_CODE]="S_CODE";
   states[S_LIST]="S_LIST";
   states[S_RE]="S_RE";
   states[S_STATE]="S_STATE";
   states[S_RETURN]="S_RETURN";
   states[S_TERM]="S_TERM";
   states[S_LEX2]="S_LEX2";
   states[S_NODE]="S_NODE";
  tokens['\n']="\\n";
  tokens['\t']="\\t";
  tokens['\\']="\\\\";
  tokens[' ']="' '";
  tokens[SPLIT]="SPLIT";
  tokens[TYPE]="TYPE";
  tokens[OPTION]="OPTION";
  tokens[LCODE]="LCODE";
  tokens[CODE]="CODE";
  tokens[NUMBER]="NUMBER";
  tokens[OPERATOR]="OPERATOR";
  tokens[RETURN]="RETURN";
  tokens[RULE]="RULE";
  tokens[MATCH]="MATCH";
  tokens[VISIT]="VISIT";
  tokens[VISITOR]="VISITOR";
  tokens[LEXEM]="LEXEM";
  tokens[ID]="ID";
  tokens[TERMINAL]="TERMINAL";
  tokens[SPACES]="SPACES";
  tokens[REF]="REF";
  tokens[CONST]="CONST";
  tokens[RE]="RE";
  while(1)
  { yylval.sval="";
    int r=yylex();
    if(r<=0) break;
    cout<<tokens[r]<<" "<<yylval.sval<<" "<<states[YYSTATE]<<endl;
  }
}
*/
