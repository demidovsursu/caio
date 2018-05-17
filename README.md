# caio
Caio All in One, compiler-compiler, AST, tree buider &amp; tree walker, parse generator

Caio translates the language definition to Flex, Bison and C++ files.

I recommend using [RE/flex](https://www.genivia.com/doc/reflex/html/index.html) instead of Flex, since it has a better implementation RE.

To traverse the AST, improved syntax forms from the [Memphis](http://memphis.compilertools.net/) were used. I wrote an analog of this program to use in my project.

Below is the code of the mini-Basic interpreter.
```cpp
%option yylineno case-insensitive
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
void interp(List<Statement> p);
int find_id(string name);
}
%% // rules for lexical analizer
[ \t\r] 				; // skip spaces
\d+ 					?number?  <stoi(yytext)>
[a-zA-Z]\w*				?ident?  <find_id(yytext)>
.|\n					// return the literal
%% // rules for parse generator
program = stmts 			%{ interp($1); }
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
    | '(' expr ')' 			<$2>
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
void interp(List<Statement> p) // execute statements
{ for(auto s:p)
    match s {
      rule assign(v, e): mem[v]=eval(e);
      rule input(v): cin>>mem[v];
      rule print(e): cout<<eval(e)<<endl;
      rule whilestmt(e,p1): while(eval(e)) interp(p1);
      rule ifstmt(e,p1,p2): if(eval(e)) interp(p1);
                            else interp(p2);
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
