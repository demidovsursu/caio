# caio
Caio is All in One, compiler-compiler, AST, tree buider &amp; tree walker, EBNF parser generator

Caio translates the language definition to Flex, Bison and C++ files.

I recommend using [RE/flex](https://www.genivia.com/doc/reflex/html/index.html) instead of Flex, since it has a better implementation RE.

Directory src/ contains Caio's source. Use the previous generated files from directory build/ to build Caio's executable file. Run "make  rebuild" to generate files from changed Caio's source. 

See the code of the mini-Basic interpreter.
```cpp
%option case-insensitive locations
%operator <yfx> '+' '-'
%operator <yfx> '*' '/' 
%operator <fy> '-'
%type <int> ?number? ?ident?
%type <Statement> stmt
%type <Expr> expr
%{
#include <string>
#include <iostream>
#include <map>
#include <cctype>
using namespace std;
int find_id(string name);
}
%% // rules for lexer
[ \t\r] 				; // skip spaces
\d+ 					?number?  <stoi(yytext)>
[a-zA-Z]\w*				?ident?  <find_id(yytext)>
%% // rules for parser
program = stmts 			<$1>
 	;
stmts = { stmt '\n' }
	;
stmt = 					
  | ?ident? '=' expr 			<assign($1,$3)>
  | "input" ?ident?  			<input($2)>
  | "print" expr  			<print($2)> 
  | "while" expr '\n' stmts "wend" 	<whilestmt($2,$4)> 	
  | "if" expr ["then"] '\n'  stmts
     [ "else" '\n' stmts
     ] "end" "if" 			<ifstmt($2,$5,$6)> 	
  ;
expr = expr '+' expr			<plus($1,$3)>
    | expr '-' expr 			<minus($1,$3)>
    | expr '*' expr 			<mult($1,$3)>
    | expr '/' expr 			<divide($1,$3)>
    | '-' expr 				<neg($2)>
    | '(' expr ')'
    | ?number? 				<number($1)>
    | ?ident?				<ident($1)>
    ;
%%
int mem[1000]; // memory for data
visitor eval<Expr,int> { // evaluate the expression
  visit plus(x, y): return eval(x)+eval(y);
  visit minus(x, y): return eval(x)-eval(y);
  visit mult(x, y): return eval(x)*eval(y);
  visit divide(x, y): return eval(x)/eval(y);
  visit neg(x):  return -eval(x);
  visit number(x):  return x;
  visit ident(x): return mem[x];
}
void yyinterpret(List<Statement> p) // execute statements
{ for(auto s:p)
    match s {
      rule assign(v, e): mem[v]=eval(e);
      rule input(v): cin>>mem[v];
      rule print(e): cout<<eval(e)<<endl;
      rule whilestmt(e,p1): while(eval(e)) yyinterpret(p1);
      rule ifstmt(e,p1,p2): if(eval(e)) yyinterpret(p1);
                            else yyinterpret(p2);
    }
}
map<string,int> ti; // table of identifiers
int find_id(string name) // find an identifier
{ for(auto &ch:name) ch=toupper(ch);
  int k=ti[name];
  if(k==0) k=ti[name]=ti.size();
  return k;
}

```

TODO
1. Target Lemon
2. Target GPPG/GPLEX
