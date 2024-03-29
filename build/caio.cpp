#include "caio.hpp"

	#line 340 "caio.caio"
void get_args(int &yyargc, char **&yyargv)
{ for(int i=1;i<yyargc;++i)
    if(yyargv[i][0]=='-' && yyargv[i][1]=='o')
      filepath=yyargv[i]+2;
    else if(yyargv[i][0]=='-' && yyargv[i][1]=='-')
      switch_option(yyargv[i]+2);
}
int bnf_flag=1;
int ast_flag=0;
int case_flag=0;
int inter_flag=0;
int main_flag=1;
int locations_flag=0;
int literal_flag=1;
int yywrap_flag=0;
int matcherr_flag=1;
int astprint_flag=1;
int lexprint_flag=0;
int yyparse_flag=1;
int visitor_flag=1;
int yylex_flag=1;
int yyerror_flag=1;
int expect_flag=-1;
int yyinterpret_flag=1;
int usevalue_flag=0;
int usestring_flag=0;
int uselist_flag=0;
int reentrant_flag=0;
int lexdefault_flag=-1;
int line_flag=1;

int grmfile_exist=0;
int lexfile_exist=0;

int gen_mode=0;
int return_field=0;

int symbol_uid=0;
int terminal_uid=1000;
string filename,filepath;
string root_tip;

struct symbolinfo {
  string altname;
  int generated;
  int terminalnumber;
  string tip;
  Grule defrule;
  int used;
  vector<pair<string,int>> node_link;
  vector<pair<string,int>> symbol_link;
  symbolinfo():altname(""s),generated(0),terminalnumber(0),tip(""),defrule(nullptr),used(0){}
};
struct constinfo {
  string tip;
  constinfo():tip(""){}
};
struct nodeinfo {
  vector<string> types;
  vector<string> symbol_link;
  nodeinfo(int n=0):types(n){}
};
struct domaininfo {
  set<string> nodes;
  domaininfo(){}
};
struct operinfo {
  string name;
  string tip;
  int prior;
  operinfo(const string &name, const string &tip, int prior):name(name),tip(tip),prior(prior){}
};
struct lexdefinfo {
  string id;
  string re;
  lexdefinfo(const string &id, const string&re):id(id),re(re) {}
};
map<string,symbolinfo> symbols;
map<string,constinfo> consts;
map<string,domaininfo> domains;
map<string,nodeinfo> nodes;
vector<operinfo> opers;
vector<lexdefinfo> lexdefs;
set<string> defined_symbols;
set<string> symbol_names;
set<string> lex_states;
map<string,int> union_fields;
ostringstream vout;
string default_tip="int"s;
vector<string> using_list;

namespace ast {
Gelem symelem(const string& sym)
{ return symelem(sym,"");
}
Gelem varelem(List<Xrule> xl)
{ return varelem(xl,"");
}
}
void add_symbol(const string&id, const string&tip);
void set_input(const char* name)
{
  bnf_flag=1;
  ast_flag=0;
  case_flag=0;
  inter_flag=0;
  main_flag=1;
  locations_flag=0;
  literal_flag=1;
  yywrap_flag=0;
  matcherr_flag=1;
  astprint_flag=1;
  lexprint_flag=0;
  yyparse_flag=1;
  visitor_flag=1;
  yylex_flag=1;
  yyerror_flag=1;
  expect_flag=-1;
  yyinterpret_flag=1;
  usevalue_flag=0;
  usestring_flag=0;
  uselist_flag=0;
  reentrant_flag=0;
  lexdefault_flag=-1;
  line_flag=1;

  grmfile_exist=0;
  lexfile_exist=0;

  gen_mode=0;
  return_field=0;

  symbol_uid=0;
  terminal_uid=1000;
  root_tip=""s;
  caio_mode=M_DECL;

  symbols.clear();
  add_symbol("error","");
  consts.clear();
  domains.clear();
  nodes.clear();
  opers.clear();
  lexdefs.clear();
  defined_symbols.clear();
  defined_symbols.insert("error"s);
  symbol_names.clear();
  lex_states.clear();
  union_fields.clear();
  vout.clear();
  default_tip="int"s;
  using_list.clear();
  
  filename=name;
  size_t p=filename.rfind('/');
  if(p!=string::npos) filename=filename.substr(p+1);
  p=filename.rfind('\\');
  if(p!=string::npos) filename=filename.substr(p+1);
  p=filename.rfind('.');
  if(p!=string::npos) filename=filename.substr(0,p);
}

void add_using(const string &o)
{ using_list.push_back(o);
}
void switch_option(const string &o)
{
   if(o=="ebnf"s)
     bnf_flag=1;
   else if(o=="bnf"s)
     bnf_flag=0;
   else if(o=="rebnf"s)
     bnf_flag=2;
   else if(o=="aebnf"s)
     bnf_flag=3;
   else if(o=="case-insensitive"s)
     case_flag=1;
   else if(o=="case-sensitive"s)
     case_flag=0;
   else if(o=="interactive"s)
     inter_flag=1;
   else if(o=="nointeractive"s)
     inter_flag=0;
   else if(o=="nomain"s)
     main_flag=0;
   else if(o=="main"s)
     main_flag=1;
   else if(o=="noyyparse"s)
     yyparse_flag=0;
   else if(o=="yyparse"s)
     yyparse_flag=1;
   else if(o=="noyylex"s)
     yylex_flag=0;
   else if(o=="yylex"s)
     yylex_flag=1;
   else if(o=="reentrant"s)
     reentrant_flag=1;
   else if(o=="yylineno"s)
     locations_flag=1;
   else if(o=="locations"s)
     locations_flag=2;
   else if(o=="nolocations"s)
     locations_flag=0;
   else if(o=="literal-rules"s)
     literal_flag=1;
   else if(o=="noliteral-rules"s)
     literal_flag=0;
   else if(o=="nodefault"s)
     lexdefault_flag=0;
   else if(o=="default-skip"s)
     lexdefault_flag=2;
   else if(o=="default-literal"s)
     lexdefault_flag=3;
   else if(o=="default-echo"s)
     lexdefault_flag=1;
   else if(o=="yywrap"s)
     yywrap_flag=1;
   else if(o=="noyywrap"s)
     yywrap_flag=0;
   else if(o=="matcherror"s)
     matcherr_flag=1;
   else if(o=="nomatcherror"s)
     matcherr_flag=0;
   else if(o=="visitor"s)
     visitor_flag=2;
   else if(o=="novisitor"s)
     visitor_flag=0;
   else if(o=="yyinterpret"s)
     yyinterpret_flag=1;
   else if(o=="noyyinterpret"s)
     yyinterpret_flag=0;
   else if(o=="astprint"s)
     astprint_flag=1;
   else if(o=="noastprint"s)
     astprint_flag=0;
   else if(o=="lexprint"s)
     lexprint_flag=1;
   else if(o=="nolexprint"s)
     lexprint_flag=0;
   else if(o=="yyerror"s)
     yyerror_flag=1;
   else if(o=="noyyerror"s)
     yyerror_flag=0;
   else if(o=="line"s)
     line_flag=1;
   else if(o=="noline"s)
     line_flag=0;
   else if(o=="ast"s)
   {
     main_flag=0;
     yylex_flag=0;
     yyparse_flag=0;
     ast_flag=1;
     locations_flag=0;
   }
   else if(o.substr(0,7)=="expect="s && o.size()>7 && isdigit(o[7]))
     expect_flag=stoi(o.substr(7));
}
Gelem replace_altid(Gelem &e, const string &newid)
{
  { auto &_match1=e;
if(auto _node1=dynamic_cast<trmelem_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 601 "caio.caio"
                          
    altid=newid;
  }
else if(auto _node1=dynamic_cast<symelem_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 603 "caio.caio"
                         
    altid=newid;
  }
else if(auto _node1=dynamic_cast<varelem_node *>(_match1)) {
  auto &xl=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 605 "caio.caio"
                         
    altid=newid;
  }
else if(auto _node1=dynamic_cast<optelem_node *>(_match1)) {
  auto &xl=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 607 "caio.caio"
                         
    altid=newid;
  }
else if(auto _node1=dynamic_cast<repelem1_node *>(_match1)) {
  auto &xl=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 609 "caio.caio"
                          
    altid=newid;
  }
else if(auto _node1=dynamic_cast<repelem0_node *>(_match1)) {
  auto &xl=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 611 "caio.caio"
                          
    altid=newid;
  }
}

	#line 613 "caio.caio"
  
  Gelem r=e;
  e=nullptr;
  return r;
}
set<string> builtin_types={"int"s,"std::string"s,"long"s,"double"s,"int64_t"s,"char"s};
bool is_pointer_type(const string &t)
{
  return t[t.size()-1]=='*';
}
bool is_builtin_type(const string &t)
{ 
  return builtin_types.find(t)!=builtin_types.end();
}
bool is_big_builtin_type(const string &t)
{ 
  return t=="std::string"s;
}
bool is_domain(const string &s)
{ return domains.find(s)!=domains.end();
}
bool is_domain_name(const string &s)
{
  for(auto c:s)
    if(!isalnum(c)) return 0;
  return !is_builtin_type(s);
}
bool is_list_type(const string &s)
{ return s.substr(0,5)=="List<"s;
}
string list_of_type(string s)
{ if(s.back()=='?') s.pop_back();
  return "List<"s+s+">"s;
}
string type_of_list(const string &s)
{ if(s.substr(0,5)=="List<"s) return s.substr(5,s.size()-6);
  return s;
}
bool empty_type(const string& t)
{ return t==""s || t=="?"s;
}
string encode_string(const string &s, int enc_hex=1)
{ string r;
  for(auto c:s)
  { if(c=='\n') r+="\\n";
    else if(c=='\t') r+="\\t";
    else if(c=='\\' || c=='\'' || c=='\"') { r+='\\'; r+=c; }
    else if((c&0xFF)>=0x7F && enc_hex) { 
      r+="\\x"s; 
      ostringstream v;
      v<<hex<<(c&0xFF);
      r+=v.str();
    }
    else
      r+=c;
  }
  return r;
}
static int todigit(char c)
{ if(c>='0' && c<='9')
     return c-'0';
   else if(c>='a' && c<='f')
      return c-'a'+10;
   else if(c>='A' && c<='F')
      return c-'A'+10;
   return 0;
}
string decode_string(const string&t)
{ string s="";
  for(int i=0;i<t.size();++i)
  { if(i+1<t.size() && t[i]=='\\' && t[i+1]=='n')
    { ++i; s+='\n';
    }
    else if(i+1<t.size() && t[i]=='\\' && t[i+1]=='t')
    { ++i; s+='\t';
    }  
    else if(i+1<t.size() && t[i]=='\\' && t[i+1]=='\\')
    { ++i; s+='\\';
    }  
    else if(i+3<t.size() && t[i]=='\\' && t[i+1]=='x' && isxdigit(t[i+2]) && isxdigit(t[i+3]))
    {
      s+=char(todigit(t[i+2])*16+todigit(t[i+3]));
      i+=3;
    }
    else
      s+=t[i];
  }
  return s;
}
string normalize_terminal(const string &t)
{ if(t[0]=='?') return t;
  string s=decode_string(t.substr(1,t.size()-2));
  if(s.size()==1) return "'"s+encode_string(s)+"'"s;
  return "\""s+encode_string(s)+"\""s;
}
bool isterminal(const string &o)
{ return o[0]=='?' || o[0]=='\'' || o[0]=='\"';
}
bool isliteral(const string &o)
{ return o[0]=='\'' || o[0]=='\"';
}
const char* cyr_enc[32]={
      "a","b","v","g","d","e","zh","z","i","y","k","l","m","n","o",
      "p","r","s","t","u","f","kh","ts","ch","sh","tsh","q","iq","j","eq","yu","ya"};
string encode_symbol(const string &sym)
{ string r,s;
  for(auto c:sym)
  { int ch=c&0xFF;
    if(ch>=224)
      s=cyr_enc[ch-224];
    else if(ch>=192)
    { s=cyr_enc[ch-192];
      s[0]=toupper(s[0]);
    }
    else if(ch=='-')
      s="_";
    else if(ch=='.')
      s="_";
    else if(ch==168)
      s="Yo";
    else if(ch==184)
      s="yo";
    else
      s=string(1,c);
    r+=s;
  }
  return r;
}
int oper_prior(const string &o, int n)
{ string op=normalize_terminal(o);
  for(auto &x:opers)
    if(x.name==op)
    { if(n==2) 
      { if(x.tip=="xfx"s || x.tip=="xfy"s || x.tip=="yfx") return x.prior;
      }
      else if(n==1)
      { if(x.tip=="fx" || x.tip=="fy") return x.prior;
      }
      else
      { if(x.tip=="xf" || x.tip=="yf") return x.prior;
      }
    }
  return 0;
}
string oper_type(const string &o, int n)
{ string op=normalize_terminal(o);
  for(auto &x:opers)
    if(x.name==op)
    { if(n==2) 
      { if(x.tip=="xfx"s || x.tip=="xfy"s || x.tip=="yfx") return x.tip;
      }
      else if(n==1)
      { if(x.tip=="fx" || x.tip=="fy") return x.tip;
      }
      else
      { if(x.tip=="xf" || x.tip=="yf") return x.tip;
      }
    }
  return ""s;
}
string type_mark(const string &t, int cf)
{ if(t.back()=='?')
    return "ast::Value<"s+t.substr(0,t.size()-1)+">"s;
  if(is_big_builtin_type(t) && cf==1) 
    return "const "s+t+"&";
  return t;
}
void gen_coderef(ostream& fout, const string &t, int mlevel, int limit)
{ 
  if(t=="$$"s)
  {
    if(gen_mode==0 && mlevel==0)
      yyerror("Can't use $$ without rule"s);
    else if(gen_mode==0)
      fout<<"(*_node"<<mlevel<<")";
    else if(gen_mode==1)
      fout<<"yylval.f"<<return_field<<"_";
    else
      fout<<t;
  }
  else if(t=="@$"s)
  {
    if(gen_mode==0 && mlevel==0 || locations_flag!=2)
      yyerror("Can't use @$ without rule or locations option"s);
    else if(gen_mode==0)
      fout<<"(_node"<<mlevel<<"->yyloc)";
    else if(gen_mode==1)
      fout<<"(yylloc)";
    else
      fout<<t;
  }
  else if(t.size()>=2 && t[0]=='$' && t[1]>='1' && t[1]<='9')
  { int n=stoi(t.substr(1));
    if(n<1 || n>limit)
      yyerror(t+" don't exist"s);
    if(gen_mode==0)
      fout<<"_node"<<mlevel<<"->f"<<t.substr(1)<<"_";
    else
      fout<<t;
  }
  else
    fout<<t;
}
void show_line(ostream& fout, int l, int c)
{
    if(line_flag==0 || l<=1) return;
    fout<<"\n\t#line "<<l<<" \""<<yyinputfile<<"\"\n";
    if(c<=0) c=2;
    while(--c>0) fout<<' ';
}
void gen_code_line(ostream& fout, List<Code> code, int mlevel,int limit);
void gen_code(ostream& fout, List<Code> code, int mlevel,int limit)
{ for(auto c:code)
  { auto &_match1=c;
if(auto _node1=dynamic_cast<lexem_node *>(_match1)) {
  auto &t=_node1->f1_;

	#line 827 "caio.caio"
                   
      gen_coderef(fout,t,mlevel,limit);
    }
else if(auto _node1=dynamic_cast<pcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 829 "caio.caio"
                   
      fout<<"{";
      gen_code(fout,cc,mlevel,limit);
      fout<<"}";
    }
else if(auto _node1=dynamic_cast<mcode_node *>(_match1)) {
  auto &cc=_node1->f1_;
  auto &rules=_node1->f2_;

	#line 833 "caio.caio"
                         
      { int old_mode=gen_mode;
        gen_mode=0;
        fout<<"{ auto &_match"<<(mlevel+1)<<"=";
        for(auto s:cc)
        { gen_coderef(fout,s,mlevel,limit);
        } 
        fout<<";\n";
        int flg=0,dflt=0;
        for(auto r:rules)
        {          
          { auto &_match2=r;
if(auto _node2=dynamic_cast<mrule_node *>(_match2)) {
  auto &m=_node2->f1_;
  auto &co=_node2->f2_;

	#line 845 "caio.caio"
                              
            { int nlimit=0,mtip=0;
              List<string> a(nullptr);
              string idn;
              { auto &_match3=m;
if(_match3==nullptr) {

	#line 850 "caio.caio"
                             
                  idn=""s;
                  mtip=1;
                }
else if(auto _node3=dynamic_cast<node2_node *>(_match3)) {
  auto &id=_node3->f1_;
  auto &args=_node3->f2_;

	#line 853 "caio.caio"
                                    
                  { idn=id;
                    a=args;
                  }
                }
else if(auto _node3=dynamic_cast<node1_node *>(_match3)) {
  auto &id=_node3->f1_;

	#line 857 "caio.caio"
                               
                  { mtip=1;
                    idn=id;
                  }
              }
}

	#line 861 "caio.caio"
              
              if(idn=="nullptr"s)
              { if(flg) yyerror("rule nullptr should be first in match"s);
                nlimit=0;
              }
              else if(idn=="")
              { 
                nlimit=0;
                dflt=1;
              }
              else
              {
                auto it=nodes.find(idn);
                if(it==nodes.end() && using_list.size()==0)
                  yyerror("Node "s+idn+" don't exist"s);
                if(mtip==0) 
                { int n=0;
                  for(auto x:a) ++n;
                  if(it!=nodes.end() && n!=it->second.types.size()-1)
                    yyerror("Node "s+idn+"' args can't matched"s);
                  nlimit=0;
                }
                else
                { if(it!=nodes.end())
                    nlimit=it->second.types.size()-1;
                  else 
                    nlimit=100;
                }
              }
              if(flg) fout<<"else ";
              if(idn=="nullptr"s)
                fout<<"if(_match"<<(mlevel+1)<<"==nullptr) {\n";
              else if(idn==""s)
                fout<<" {\n";
              else 
                fout<<"if(auto _node"<<(mlevel+1)<<"=dynamic_cast<"<<idn<<"_node *>(_match"<<(mlevel+1)<<")) {\n";
              int n=0;
              for(auto f:a)
              { ++n;
                fout<<"  auto &"<<f<<"=_node"<<(mlevel+1)<<"->f"<<n<<"_;\n";
              }
              gen_code_line(fout,co,mlevel+1,nlimit);
              fout<<"}\n";
              flg=1;
            }
          }
}

	#line 906 "caio.caio"
          
        }
        if(!dflt && matcherr_flag)
        {  if(flg) fout<<"else ";
           fout<<"{ yyerror(\""<<yyinputfile<<":"<<(_node1->yyloc).last.line<<":"<<(_node1->yyloc).last.column<<": Match error\"); }\n";
        }
        fout<<"}\n";
        show_line(fout,(_node1->yyloc).last.line,(_node1->yyloc).last.column);

        gen_mode=old_mode;
      }
    }
else if(auto _node1=dynamic_cast<vcode_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &tip=_node1->f2_;
  auto &ret=_node1->f3_;
  auto &cc=_node1->f4_;
  auto &rules=_node1->f5_;

	#line 917 "caio.caio"
                                    
      { if(gen_mode!=0 || mlevel>0)
          yyerror("Can't define visitor at this point"s);
        if(visitor_flag==0)
          yyerror("Visitor is disabled"s);
        visitor_flag=2;
        int old_mode=gen_mode;
        gen_mode=0;
        fout<<"struct "<<id<<"_visitor:"<<tip<<"_Tvisitor<"<<ret<<"> {\n";
        gen_code_line(fout,cc,mlevel+1,0);
        fout<<"\n";
        for(auto r:rules)
        {          
          { auto &_match2=r;
if(auto _node2=dynamic_cast<vrule_node *>(_match2)) {
  auto &m=_node2->f1_;
  auto &co=_node2->f2_;

	#line 931 "caio.caio"
                              
            { int nlimit=0,mtip=0;
              List<string> a(nullptr);
              string idn;
              { auto &_match3=m;
if(auto _node3=dynamic_cast<node2_node *>(_match3)) {
  auto &idt=_node3->f1_;
  auto &args=_node3->f2_;

	#line 936 "caio.caio"
                                     
                  { idn=idt;
                    a=args;
                  }
                }
else if(auto _node3=dynamic_cast<node1_node *>(_match3)) {
  auto &idt=_node3->f1_;

	#line 940 "caio.caio"
                                
                  { mtip=1;
                    idn=idt;
                  }
              }
}

	#line 944 "caio.caio"
              
              auto it=nodes.find(idn);
              if(it==nodes.end() && using_list.size()==0)
                yyerror("Node "s+idn+" don't exist"s);
              if(mtip==0) 
              { int n=0;
                for(auto x:a) ++n;
                if(it!=nodes.end() && n!=it->second.types.size()-1)
                  yyerror("Node "s+idn+"' args can't matched"s);
                nlimit=0;
              }
              else
              { if(it!=nodes.end())
                  nlimit=it->second.types.size()-1;
                else
                  nlimit=100;
              }
              fout<<ret<<" visit("<<idn<<"_node*);\n";
              vout<<ret<<" "<<id<<"_visitor::visit("<<idn<<"_node* _node"<<(mlevel+1)<<") {\n";
              int n=0;
              for(auto f:a)
              { ++n;
                vout<<"  auto &"<<f<<"=_node"<<(mlevel+1)<<"->f"<<n<<"_;\n";
              }
              gen_code_line(vout,co,mlevel+1,nlimit);
              vout<<"}\n";
            }
          }
}

	#line 971 "caio.caio"
          
        }
        fout<<"} "<<id<<";\n";
        show_line(fout,(_node1->yyloc).last.line,(_node1->yyloc).last.column);
        gen_mode=old_mode;
      }
    }
else if(auto _node1=dynamic_cast<token_node *>(_match1)) {
  auto &val=_node1->f1_;

	#line 977 "caio.caio"
                    
      { string id=normalize_terminal(val);
        auto it=symbols.find(id);
        if(it==symbols.end())
          yyerror(id+" isn't used in rules");
        if(it->second.terminalnumber>0)
          fout<<"("<<it->second.terminalnumber<<")";
        else 
          fout<<"("<<it->second.altname<<")";
      }
  }
}

	#line 987 "caio.caio"
  
}
void gen_code_line(ostream& fout, List<Code> code, int mlevel,int limit)
{ if(code)
  { 
    show_line(fout,code[0]->yyloc.first.line,code[0]->yyloc.first.column);
    gen_code(fout,code,mlevel,limit);
  }
}
void add_symbol(const string&id, const string&tip)
{ if(symbols.find(id)!=symbols.end()) return;
  symbols[id]=symbolinfo();
  symbols[id].tip=tip;
}
void add_constant(const string&id, const string&tip)
{ if(consts.find(id)!=consts.end()) return;
  consts[id]=constinfo();
  consts[id].tip=tip;
}
List<Code> hcode(nullptr);
List<Code> grmcode(nullptr);
List<Code> lexcode(nullptr);
List<Code> lexinitcode(nullptr);
void collect_terminals(List<Code> code)
{ for(auto c:code)
  { auto &_match1=c;
if(auto _node1=dynamic_cast<pcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 1013 "caio.caio"
                   
      collect_terminals(cc);
    }
else if(auto _node1=dynamic_cast<token_node *>(_match1)) {
  auto &val=_node1->f1_;

	#line 1015 "caio.caio"
                    
      add_symbol(normalize_terminal(val),"");
  }
}

	#line 1017 "caio.caio"
  
}
void collect_decls(List<Decl> decls)
{ int prior=0;
  string tip="";
  for(auto d:decls)
  { { auto &_match1=d;
if(auto _node1=dynamic_cast<decloper_node *>(_match1)) {
  auto &ops=_node1->f1_;

	#line 1024 "caio.caio"
                       
      prior++; 
      for(auto o:ops)
      { if(isterminal(o))
          opers.push_back(operinfo(normalize_terminal(o),tip,prior));
        else
          tip=o;
      }
    }
else if(auto _node1=dynamic_cast<decltypes_node *>(_match1)) {
  auto &tip=_node1->f1_;
  auto &syms=_node1->f2_;

	#line 1032 "caio.caio"
                              
      if(is_domain_name(tip)) {
        if(!is_domain(tip))
          domains[tip]=domaininfo();
      }
      if(!syms)  default_tip=tip;
      for(auto sym:syms)
      { { auto &_match2=sym;
if(auto _node2=dynamic_cast<terminal_node *>(_match2)) {
  auto &id=_node2->f1_;

	#line 1040 "caio.caio"
                          
          add_symbol(normalize_terminal(id),tip);
        }
else if(auto _node2=dynamic_cast<ident_node *>(_match2)) {
  auto &id=_node2->f1_;

	#line 1042 "caio.caio"
                       
        {
          if(defined_symbols.find(id)!=defined_symbols.end())
            add_symbol(id,tip);
          else
            add_constant(id,tip);
        }
        }
else if(auto _node2=dynamic_cast<node_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &args=_node2->f2_;

	#line 1049 "caio.caio"
                            
          if(!is_domain_name(tip))
            yyerror("Type of node can't assign to "s+tip);
          if(nodes.find(id)!=nodes.end())
            yyerror("Node "s+id+" is assigned to domain "s+nodes[id].types[0]);
          auto &v=nodes[id];
          v.types.push_back(tip);
          for(auto &t:args)
          { if(t.back()=='?')
              if(!is_builtin_type(t.substr(0,t.size()-1)))
                yyerror("Wrong type "s+t);
            v.types.push_back(t);
          }
          domains[tip].nodes.insert(id);
        }
}

	#line 1063 "caio.caio"
        
      }
    }
else if(auto _node1=dynamic_cast<declcode_node *>(_match1)) {
  auto &dest=_node1->f1_;
  auto &cc=_node1->f2_;

	#line 1065 "caio.caio"
                           
      if(!dest || dest=="h"s)
        hcode=cons(hcode,cc);
      else if(dest=="grm"s)
        grmcode=cons(grmcode,cc);
      else if(dest=="lex"s)
        lexcode=cons(lexcode,cc);
      collect_terminals(cc);
    }
else if(auto _node1=dynamic_cast<declre_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &re=_node1->f2_;

	#line 1073 "caio.caio"
                       
      lexdefs.push_back(lexdefinfo(id,re));
    }
}

	#line 1075 "caio.caio"
    
  }
}
void collect_terminals(List<Lrule> rules)
{ for(auto r:rules)
  {
    { auto &_match1=r;
if(auto _node1=dynamic_cast<lexrule_node *>(_match1)) {
  auto &sts=_node1->f1_;
  auto &re=_node1->f2_;
  auto &act=_node1->f3_;

	#line 1082 "caio.caio"
                               
       { auto &_match2=act;
if(auto _node2=dynamic_cast<lterm_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &t=_node2->f2_;

	#line 1084 "caio.caio"
                        
          if(id)
            add_symbol(normalize_terminal(id),"");
       }
}

	#line 1087 "caio.caio"
       
       }
else if(auto _node1=dynamic_cast<lcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 1088 "caio.caio"
                      
         collect_terminals(cc);
    }
}

	#line 1090 "caio.caio"
    
  }
}
regex ref_re(R"(\$(\d+|\$))");
void collect_ref(const string& t, set<int>& refs)
{ 
  for(auto it=sregex_iterator(t.begin(),t.end(),ref_re);
     it!=sregex_iterator();++it) 
  { if(it->str(1)=="$"s)
      refs.insert(0);
    else 
      refs.insert(stoi(it->str(1)));
  }
}
void collect_refs(Term t, set<int>& refs)
{ { auto &_match1=t;
if(auto _node1=dynamic_cast<tnode_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &args=_node1->f2_;

	#line 1106 "caio.caio"
                         
    { for(auto a:args)
        collect_ref(a,refs);
    }
    }
else if(auto _node1=dynamic_cast<snode_node *>(_match1)) {
  auto &str=_node1->f1_;

	#line 1110 "caio.caio"
                     
      collect_ref(str,refs);
  }
}

	#line 1112 "caio.caio"
  
}
bool is_string_use(Term t, int r)
{ { auto &_match1=t;
if(auto _node1=dynamic_cast<tnode_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &args=_node1->f2_;

	#line 1116 "caio.caio"
                         
    { 
      auto it=nodes.find(id);
      if(it!=nodes.end())
      {
        int n=0;
        string rs="$"s+to_string(r);
        for(auto a:args)
        { ++n;
          if(a==rs)
            if(it->second.types[n]=="std::string?") return 1;
        }
      }
    }
    }
else if(auto _node1=dynamic_cast<snode_node *>(_match1)) {
  auto &str=_node1->f1_;

	#line 1130 "caio.caio"
                    
      return str=="$"s+to_string(r);
  }
}

	#line 1132 "caio.caio"
  
  return 0;
}

void collect_refs(List<Code> code, set<int>& refs)
{ for(auto c:code)
  { auto &_match1=c;
if(auto _node1=dynamic_cast<pcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 1139 "caio.caio"
                   
      collect_refs(cc,refs);
    }
else if(auto _node1=dynamic_cast<lexem_node *>(_match1)) {
  auto &val=_node1->f1_;

	#line 1141 "caio.caio"
                    
      collect_ref(val,refs);
  }
}

	#line 1143 "caio.caio"
  
}
void collect_terminals(List<Xrule> rules)
{ for(auto r:rules)
  { set<int> refs;
    { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1149 "caio.caio"
                         
      { auto &_match2=a;
if(auto _node2=dynamic_cast<gterm_node *>(_match2)) {
  auto &t=_node2->f1_;

	#line 1151 "caio.caio"
                    
        collect_refs(t,refs);
      }
else if(auto _node2=dynamic_cast<gcode_node *>(_match2)) {
  auto &cc=_node2->f1_;

	#line 1153 "caio.caio"
                     
        collect_terminals(cc);
        collect_refs(cc,refs);
      }
}

	#line 1156 "caio.caio"
      
      int n=0;
      for(auto e:elist)
      { ++n;
        bool flg=refs.find(n)!=refs.end();
        { auto &_match2=e;
if(auto _node2=dynamic_cast<trmelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1162 "caio.caio"
                                
          add_symbol(normalize_terminal(id),"");
        }
else if(auto _node2=dynamic_cast<symelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1164 "caio.caio"
                               
          if(flg)
            symbols[id].used=true;
        }
else if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1167 "caio.caio"
                               
          collect_terminals(xl);
        }
else if(auto _node2=dynamic_cast<optelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1169 "caio.caio"
                               
          collect_terminals(xl);
        }
else if(auto _node2=dynamic_cast<repelem1_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1171 "caio.caio"
                                
          collect_terminals(xl);
        }
else if(auto _node2=dynamic_cast<repelem0_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1173 "caio.caio"
                                
          collect_terminals(xl);
        }
}

	#line 1175 "caio.caio"
        
      }
    }
}

	#line 1177 "caio.caio"
    
  }
}
void collect_terminals(List<Grule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1183 "caio.caio"
                           
      collect_terminals(body);
    }
}

	#line 1185 "caio.caio"
    
  } 
}
bool is_empty_rule(List<Xrule> rules)
{
  for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1192 "caio.caio"
                         
      { auto &_match2=a;
if(auto _node2=dynamic_cast<gempty_node *>(_match2)) {

	#line 1194 "caio.caio"
                    
        for(auto e:elist)
        {
          { auto &_match3=e;
if(auto _node3=dynamic_cast<trmelem_node *>(_match3)) {
  auto &id=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1198 "caio.caio"
                                 
            if(!empty_type(symbols[normalize_terminal(id)].tip)) return false;
          }
else if(auto _node3=dynamic_cast<varelem_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1200 "caio.caio"
                                 
            if(!is_empty_rule(xl)) return false;
          }
else if(auto _node3=dynamic_cast<optelem_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1202 "caio.caio"
                                 
            if(!is_empty_rule(xl)) return false;
          }
else if(auto _node3=dynamic_cast<repelem1_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1204 "caio.caio"
                                  
            if(!is_empty_rule(xl)) return false;
          }
else if(auto _node3=dynamic_cast<repelem0_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1206 "caio.caio"
                                  
            if(!is_empty_rule(xl)) return false;
          }
else  {

	#line 1208 "caio.caio"
                  
            return false;
          }
}

	#line 1210 "caio.caio"
          
        }
      }
else  {

	#line 1212 "caio.caio"
              
        return false;
      }
}

	#line 1214 "caio.caio"
      
    }
}

	#line 1215 "caio.caio"
    
  }
  return true;
}
void setup_default(List<Xrule> rules, bool need, const string& idr)
{ 
  for(auto r:rules)
  { set<int> refs;
    { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1224 "caio.caio"
                         
      { auto &_match2=a;
if(auto _node2=dynamic_cast<gempty_node *>(_match2)) {

	#line 1226 "caio.caio"
                    
        if(need)
        { int n=0;
          vector<int> u;
          bool urep=0, uopt=0;
          for(auto e:elist)
          { ++n;
            { auto &_match3=e;
if(auto _node3=dynamic_cast<trmelem_node *>(_match3)) {
  auto &id=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1234 "caio.caio"
                                   
              if(!empty_type(symbols[normalize_terminal(id)].tip))
              { u.push_back(n);
              }
            }
else if(auto _node3=dynamic_cast<varelem_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1238 "caio.caio"
                                   
              if(!is_empty_rule(xl))
              { u.push_back(n); uopt=1;
              }
            }
else if(auto _node3=dynamic_cast<optelem_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1242 "caio.caio"
                                   
              if(!is_empty_rule(xl))
              { u.push_back(n); uopt=1;
              }
            }
else if(auto _node3=dynamic_cast<repelem1_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1246 "caio.caio"
                                    
              if(!is_empty_rule(xl))
              { u.push_back(n); urep=1;
              }
            }
else if(auto _node3=dynamic_cast<repelem0_node *>(_match3)) {
  auto &xl=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 1250 "caio.caio"
                                    
              if(!is_empty_rule(xl))
              { u.push_back(n); urep=1;
              }
            }
else  {

	#line 1254 "caio.caio"
                    
              { u.push_back(n);
              }
            }
}

	#line 1257 "caio.caio"
            
          }
          if(u.size()==1) {
            destroy(a); a=gterm(snode("$"s+to_string(u[0])));
            refs.insert(u[0]);
          }
          else if(u.size()==2 && urep) {
            destroy(a);
            a=gterm(tnode("cons"s,List<string>({"$"s+to_string(u[0]),"$"s+to_string(u[1])})));
            refs.insert(u[0]);
            refs.insert(u[1]);
            astprint(cout,a);
          }
          else if(u.size()==2 && uopt) {
            destroy(a);
            a=gterm(tnode("cons"s,List<string>({"cons($"s+to_string(u[0])+")"s,"$"s+to_string(u[1])})));
            refs.insert(u[0]);
            refs.insert(u[1]);
          }
          else if(u.size()>1)
            std::cerr<<"Warning: ambiguity rule for "<<idr<<" to select value by default, write direct action\n";
        }
      }
else if(auto _node2=dynamic_cast<gterm_node *>(_match2)) {
  auto &t=_node2->f1_;

	#line 1279 "caio.caio"
                    
        collect_refs(t,refs);
      }
else if(auto _node2=dynamic_cast<gcode_node *>(_match2)) {
  auto &cc=_node2->f1_;

	#line 1281 "caio.caio"
                     
        collect_refs(cc,refs);
      }
}

	#line 1283 "caio.caio"
      
      int n=0;
      for(auto &e:elist)
      { ++n;
        bool flg=refs.find(n)!=refs.end();
        { auto &_match2=e;
if(auto _node2=dynamic_cast<trmelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1289 "caio.caio"
                               
          if(flg)
            if(empty_type(symbols[normalize_terminal(id)].tip))
              std::cerr<<"Warning: ref to terminal "<<id<<" with undefined type\n";
        }
else if(auto _node2=dynamic_cast<symelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1293 "caio.caio"
                                
          if(flg) 
          { if(!symbols[id].used)
            {
              symbols[id].used=true;
              { auto &_match3=symbols[id].defrule;
if(auto _node3=dynamic_cast<grmrule_node *>(_match3)) {
  auto &id2=_node3->f1_;
  auto &body2=_node3->f2_;

	#line 1299 "caio.caio"
                                       
                setup_default(body2, true,id2);
              }
}

	#line 1301 "caio.caio"
              
            }
          }
        }
else if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1304 "caio.caio"
                               
          setup_default(xl,flg,idr);
        }
else if(auto _node2=dynamic_cast<optelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1306 "caio.caio"
                               
          setup_default(xl,flg,idr);
        }
else if(auto _node2=dynamic_cast<repelem1_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1308 "caio.caio"
                                
          setup_default(xl,flg,idr);
        }
else if(auto _node2=dynamic_cast<repelem0_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1310 "caio.caio"
                                
          setup_default(xl,flg,idr);
        }
}

	#line 1312 "caio.caio"
        
      }
    }
}

	#line 1314 "caio.caio"
    
  }
}
void setup_default(List<Grule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1320 "caio.caio"
                           
      if(!empty_type(symbols[id].tip))
        symbols[id].used=true;
      setup_default(body, symbols[id].used,id);
    }
}

	#line 1324 "caio.caio"
    
  } 
}
void collect_states(List<Lrule> rules)
{
  for(auto r:rules)
  {
    { auto &_match1=r;
if(auto _node1=dynamic_cast<lexrule_node *>(_match1)) {
  auto &sts=_node1->f1_;
  auto &re=_node1->f2_;
  auto &act=_node1->f3_;

	#line 1332 "caio.caio"
                               
      for(auto s:sts)
      { if(s!="*"s && s!="INITIAL")
        { lex_states.insert(s);
        }
      }
    }
else if(auto _node1=dynamic_cast<lexinit_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 1338 "caio.caio"
                     
       lexinitcode=cc;
    }
}

	#line 1340 "caio.caio"
    
  }
}
void collect_defsymbols(List<Grule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1346 "caio.caio"
                           
       if(defined_symbols.find(id)!=defined_symbols.end())
         yyerror("Redefined symbol "s+id);
       defined_symbols.insert(id);
    }
}

	#line 1350 "caio.caio"
    
  }
}
void check_undefsymbols(List<Xrule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1356 "caio.caio"
                         
      for(auto e:elist)
      { { auto &_match2=e;
if(auto _node2=dynamic_cast<trmelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1359 "caio.caio"
                                ;
        }
else if(auto _node2=dynamic_cast<symelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1360 "caio.caio"
                                
        { if(defined_symbols.find(id)==defined_symbols.end())
            yyerror("Undefined symbol "s+id);
        }
        }
else if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1364 "caio.caio"
                               
          check_undefsymbols(xl);
        }
else if(auto _node2=dynamic_cast<optelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1366 "caio.caio"
                               
          check_undefsymbols(xl);
        }
else if(auto _node2=dynamic_cast<repelem1_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1368 "caio.caio"
                                
          check_undefsymbols(xl);
        }
else if(auto _node2=dynamic_cast<repelem0_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1370 "caio.caio"
                                
          check_undefsymbols(xl);
        }
}

	#line 1372 "caio.caio"
        
      }
    }
}

	#line 1374 "caio.caio"
    
  }
}
void check_undefsymbols(List<Grule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1380 "caio.caio"
                           
      check_undefsymbols(body);
    }
}

	#line 1382 "caio.caio"
    
  }
}
List<Grule> new_rules=nullptr;
string new_symbol(const string &id1)
{ string id=encode_symbol(id1);
  while(id==""s || symbol_names.find(id)!=symbol_names.end()) {
    id="g_"s+to_string(++symbol_uid);
  } 
  add_symbol(id,"");
  return id;
}
string new_symbol()
{ return new_symbol(""s);
}
bool is_symelem(Gelem e, const string &id)
{ bool res=false;
  { auto &_match1=e;
if(auto _node1=dynamic_cast<symelem_node *>(_match1)) {
  auto &s=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 1400 "caio.caio"
                           if(s==id) res=true;
  }
}

	#line 1401 "caio.caio"
  
  return res;
}
bool is_trmelem(Gelem e)
{ bool res=false;
  { auto &_match1=e;
if(auto _node1=dynamic_cast<trmelem_node *>(_match1)) {
  auto &s=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 1407 "caio.caio"
                           res=true;
  }
}

	#line 1408 "caio.caio"
  
  return res; 
}
int prior_elem(Gelem e, int n)
{
  int res=0;
  { auto &_match1=e;
if(auto _node1=dynamic_cast<trmelem_node *>(_match1)) {
  auto &s=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 1415 "caio.caio"
                           res=oper_prior(s,n);
    }
else if(auto _node1=dynamic_cast<varelem_node *>(_match1)) {
  auto &xl=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 1416 "caio.caio"
                           
       res=100;
       for(auto x:xl)
       { { auto &_match2=x;
if(auto _node2=dynamic_cast<xrule_node *>(_match2)) {
  auto &elist=_node2->f1_;
  auto &a=_node2->f2_;

	#line 1420 "caio.caio"
                              
           if(elist.size()!=1) return 0;
           if(!is_trmelem(elist[0])) return 0;
           int p=prior_elem(elist[0],n);
           if(p==0 && n==2) return 0;
           if(p>0 && res>p) res=p;
         }
}

	#line 1426 "caio.caio"
         
       }
  }
}

	#line 1428 "caio.caio"
  
  return res;
}
string type_elem(Gelem e, int n)
{
  string res=""s;
  { auto &_match1=e;
if(auto _node1=dynamic_cast<trmelem_node *>(_match1)) {
  auto &s=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 1435 "caio.caio"
                           res=oper_type(s,n);
  }
}

	#line 1436 "caio.caio"
  
  return res;
}
bool is_operrule(Xrule x, int prior, int n, const string &tip)
{ 
  { auto &_match1=x;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1442 "caio.caio"
                       
    if(elist.size()!=1) return false;
    if(!is_trmelem(elist[0])) return false;
    return prior_elem(elist[0],n)==prior && type_elem(elist[0],n)==tip;
  }
}

	#line 1446 "caio.caio"
  
  return false;
}
struct copy_xrule_node : xrule_node {
	copy_xrule_node(List<Gelem> a1, Gaction a2):xrule_node(a1,a2){}
	~copy_xrule_node() {
          f2_=nullptr;
	}
};
inline Xrule copy_xrule(List<Gelem> a1, Gaction a2) {
	return new copy_xrule_node(a1, a2);
}

void reorder_body(const string &gid, const string &id, List<Xrule> &rules)
{ int min_prior=100;
  for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1463 "caio.caio"
                         
      if(elist.size()==3 && is_symelem(elist[0],id) && is_symelem(elist[2],id))
      { int p=prior_elem(elist[1],2);
        if(p==0) yyerror("Wrong rule for "s+gid);
        if(min_prior>p) min_prior=p;
      }
      else if(elist.size()==2 && is_symelem(elist[1],id))
      { int p=prior_elem(elist[0],1);
        if(p>0 && min_prior>p) min_prior=p;
        if(p==0 && is_symelem(elist[0],id)) yyerror("Wrong rule for "s+gid);
      }
      else if(elist.size()==2 && is_symelem(elist[0],id))
      { int p=prior_elem(elist[1],0);
        if(p>0 && min_prior>p) min_prior=p;
      }
    }
}

	#line 1478 "caio.caio"
    
  }
  if(min_prior==100) return;
  
  List<Xrule> rules1=nullptr;
  List<Xrule> rules2=nullptr;
  string id1(new_symbol());
  for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1487 "caio.caio"
                         
      if(elist.size()==3 && is_symelem(elist[0],id) && is_symelem(elist[2],id))
      { int p=prior_elem(elist[1],2);
        if(p>min_prior)
        { destroy(elist[0]); elist[0]=symelem(id1); 
          destroy(elist[2]); elist[2]=symelem(id1);
          rules2=cons(rules2,r);
        }
        else
        { 
          if(is_trmelem(elist[1]))
          {
            string t=type_elem(elist[1],2);
            if(t[0]=='x') { destroy(elist[0]); elist[0]=symelem(id1); }
            if(t[2]=='x') { destroy(elist[2]); elist[2]=symelem(id1); }
            rules1=cons(rules1,r);
          }
          else
          { List<Xrule> part1=nullptr;
            { auto &_match2=elist[1];
if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1507 "caio.caio"
                                   
              part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,2,"xfx"s);} );
              if(!xl)
              { 
                destroy(elist[0]); elist[0]=symelem(id1);
                destroy(elist[2]); elist[2]=symelem(id1);
                xl=part1;
                rules1=cons(rules1,r);
              }
              else 
              { if(part1)
                { rules1=cons(rules1,copy_xrule(List<Gelem>({symelem(id1),varelem(part1),symelem(id1)}),a));
                }
                part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,2,"xfy"s);} );
                if(!xl)
                { 
                  destroy(elist[0]); elist[0]=symelem(id1);
                  xl=part1;
                  rules1=cons(rules1,r);
                }
                else
                {
                  if(part1)
                  { rules1=cons(rules1,copy_xrule(List<Gelem>({symelem(id1),varelem(part1),symelem(id)}),a));
                  }
                  part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,2,"yfx"s);} );
                  if(!xl)
                  { 
                    destroy(elist[2]); elist[2]=symelem(id1);
                    xl=part1;
                    rules1=cons(rules1,r);
                  }
                  else
                  {
                    if(part1)
                    { rules1=cons(rules1,copy_xrule(List<Gelem>({symelem(id),varelem(part1),symelem(id1)}),a));
                    }
                    rules2=cons(rules2,r);
                    destroy(elist[0]); elist[0]=symelem(id1);
                    destroy(elist[2]); elist[2]=symelem(id1);
                  }    
                }    
              }
            }
}

	#line 1550 "caio.caio"
            
          }
        }
      }
      else if(elist.size()==2 && is_symelem(elist[1],id))
      { int p=prior_elem(elist[0],1);
        if(p==0)
        { rules2=cons(rules2,r);
        }
        else if(p>min_prior)
        { rules2=cons(rules2,r);
          destroy(elist[1]); elist[1]=symelem(id1);
        }
        else
        { 
          if(is_trmelem(elist[0]))
          {
            string t=type_elem(elist[0],1);
            if(t[1]=='x') { destroy(elist[1]); elist[1]=symelem(id1); }
            rules1=cons(rules1,r);
          }
          else
          { List<Xrule> part1=nullptr;
            { auto &_match2=elist[0];
if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1574 "caio.caio"
                                   
              part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,1,"fx"s);} );
              if(!xl)
              { 
                destroy(elist[1]); elist[1]=symelem(id1);
                xl=part1;
                rules1=cons(rules1,r);
              }
              else 
              { if(part1)
                { rules1=cons(rules1,copy_xrule(List<Gelem>({varelem(part1),symelem(id1)}),a));
                }
                part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,1,"fy"s);} );
                if(!xl)
                { 
                  xl=part1;
                  rules1=cons(rules1,r);
                }
                else
                {
                  if(part1)
                  { rules1=cons(rules1,copy_xrule(List<Gelem>({varelem(part1),symelem(id)}),a));
                  }
                  rules2=cons(rules2,r);
                  destroy(elist[1]); elist[1]=symelem(id1);
                }    
              }
            }
}

	#line 1601 "caio.caio"
            
          }
        }
      }
      else if(elist.size()==2 && is_symelem(elist[0],id))
      { int p=prior_elem(elist[1],0);
        if(p==0)
        { rules2=cons(rules2,r);
        }
        else if(p>min_prior)
        { rules2=cons(rules2,r);
          destroy(elist[0]); elist[0]=symelem(id1);
        }
        else
        { 
          if(is_trmelem(elist[1]))
          {
            string t=type_elem(elist[1],0);
            if(t[0]=='x') { destroy(elist[0]); elist[0]=symelem(id1); }
            rules1=cons(rules1,r);
          }
          else
          { List<Xrule> part1=nullptr;
            { auto &_match2=elist[1];
if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1625 "caio.caio"
                                   
              part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,0,"xf"s);} );
              if(!xl)
              { 
                destroy(elist[1]); elist[1]=symelem(id1);
                xl=part1;
                rules1=cons(rules1,r);
              }
              else 
              { if(part1)
                { rules1=cons(rules1,copy_xrule(List<Gelem>({symelem(id1),varelem(part1)}),a));
                }
                part1=xl.split([=](Xrule x) { return is_operrule(x,min_prior,0,"yf"s);} );
                if(!xl)
                { 
                  xl=part1;
                  rules1=cons(rules1,r);
                }
                else
                {
                  if(part1)
                  { rules1=cons(rules1,copy_xrule(List<Gelem>({symelem(id),varelem(part1)}),a));
                  }
                  rules2=cons(rules2,r);
                  destroy(elist[0]); elist[0]=symelem(id1);
                }    
              }
            }
}

	#line 1652 "caio.caio"
            
          }
        }
      }
      else
      { rules2=cons(rules2,r);
      }
    }
}

	#line 1659 "caio.caio"
    
  }
  if(rules2.size()==0) yyerror("Wrong rule for "s+gid);
  rules1=cons(rules1,xrule(cons(symelem(id1)),gterm(snode("$1"s))));
  rules=rules1;
  reorder_body(gid,id1,rules2);
  new_rules=cons(new_rules,grmrule(id1,rules2));
}
void reorder_rules(List<Grule> grules)
{ for(auto r:grules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1670 "caio.caio"
                           
      reorder_body(id,id, body);
    }
}

	#line 1672 "caio.caio"
     
  }
}
bool check_all_gempty(List<Xrule> rules) 
{ bool res=true;
  for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1679 "caio.caio"
                         
      { auto &_match2=a;
if(auto _node2=dynamic_cast<gterm_node *>(_match2)) {
  auto &t=_node2->f1_;

	#line 1681 "caio.caio"
                     res=false;
      }
else if(auto _node2=dynamic_cast<gcode_node *>(_match2)) {
  auto &cc=_node2->f1_;

	#line 1682 "caio.caio"
                      res=false;
      }
}

	#line 1683 "caio.caio"
      
    }
}

	#line 1684 "caio.caio"
    
  }  
  return res;
}
void split_rules(List<Xrule> rules);
void make_rep(int one, List<Xrule> &xl, Gelem &e, const string& altid)
{ 
  split_rules(xl);
  string id1(new_symbol(altid));
  string id2(new_symbol(altid==""s?""s:"elem_"s+altid));
  Gaction g1;
  Gaction g2;
  if(check_all_gempty(xl))
  { g1=gempty();
    g2=gempty();
  }
  else
  { if(one) g1=gterm(tnode("cons"s,cons("$1"s)));
    else g1=gempty();
    g2=gterm(tnode("cons"s,List<string>({"$1"s,"$2"s})));
  }
  new_rules=cons(new_rules,grmrule(id2,xl));
  new_rules=cons(new_rules,grmrule(id1,
           cons(cons(xrule(one?cons(symelem(id2)):nullptr,g1)),
           xrule(cons(cons(symelem(id1)),symelem(id2)),g2))));
  xl=nullptr; destroy(e); e=symelem(id1);
}
void split_rules(List<Xrule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1714 "caio.caio"
                         
      for(auto &e:elist)
      { { auto &_match2=e;
if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1717 "caio.caio"
                               
          split_rules(xl);
          string id(new_symbol(altid));
          new_rules=cons(new_rules,grmrule(id,xl));
          xl=nullptr; destroy(e); e=symelem(id);
        }
else if(auto _node2=dynamic_cast<optelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1722 "caio.caio"
                               
          split_rules(xl);
          string id(new_symbol(altid));
          new_rules=cons(new_rules,grmrule(id,cons(xrule(nullptr,gempty()),xl)));
          xl=nullptr; destroy(e); e=symelem(id);
        }
else if(auto _node2=dynamic_cast<repelem1_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1727 "caio.caio"
                                 
          make_rep(1,xl,e,altid);
        }
else if(auto _node2=dynamic_cast<repelem0_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1729 "caio.caio"
                                 
          make_rep(0,xl,e,altid);
        }
}

	#line 1731 "caio.caio"
        
      }
    }
}

	#line 1733 "caio.caio"
    
  }
}
void split_rules(List<Grule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1739 "caio.caio"
                           
      split_rules(body);
    }
}

	#line 1741 "caio.caio"
     
  }
}
regex xref_re(R"(\$(\[('.*?'|\".*?\"|\?.*?\?|[a-zA-Z\xC0-\xFF\xB8\xA8][-._a-zA-Z0-9\xC0-\xFF\xB8\xA8]*)\]|[a-zA-Z\xC0-\xFF\xB8\xA8][_a-zA-Z0-9\xC0-\xFF\xB8\xA8]*))");
void replace_ref(string& t, map<string,int>& refs)
{ string r,a;
  string s=t;
  smatch m;
  while(regex_search(s,m,xref_re))
  { r+=m.prefix().str();
    a=m.str().substr(1);
    int n=-2;
    if(a[0]=='[')
      a=a.substr(1,a.size()-2);
    auto it=refs.find(a);
    if(it!=refs.end())
      n=it->second;
    if(n==0)
      r+="$$"s;
    else if(n>0)
      r+="$"s+to_string(n);
    else if(n==-2)
      yyerror("Unknown ref to "s+a);
    else
      yyerror("Ambiguous ref to "s+a);
    s=m.suffix();
  }
  r+=s;
  t=r;
}
void replace_refs(Term t, map<string,int>& refs)
{ { auto &_match1=t;
if(auto _node1=dynamic_cast<tnode_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &args=_node1->f2_;

	#line 1773 "caio.caio"
                         
    { for(auto &a:args)
        replace_ref(a,refs);
    }
    }
else if(auto _node1=dynamic_cast<snode_node *>(_match1)) {
  auto &str=_node1->f1_;

	#line 1777 "caio.caio"
                     
      replace_ref(str,refs);
  }
}

	#line 1779 "caio.caio"
  
}
void replace_refs(List<Code> code, map<string,int>& refs)
{ for(auto c:code)
  { auto &_match1=c;
if(auto _node1=dynamic_cast<pcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 1784 "caio.caio"
                   
      replace_refs(cc,refs);
    }
else if(auto _node1=dynamic_cast<lexem_node *>(_match1)) {
  auto &val=_node1->f1_;

	#line 1786 "caio.caio"
                    
      if(val.size()>0 && val[0]=='$')
        replace_ref(val,refs);
  }
}

	#line 1789 "caio.caio"
  
}
void add_altid(map<string,int>& refs, const string &id, int n)
{ auto it=refs.find(id);
  if(it==refs.end())
    refs[id]=n;
  else
    it->second=-1;
}
void replace_refs(List<Xrule> rules, const string &idr)
{
  for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<xrule_node *>(_match1)) {
  auto &elist=_node1->f1_;
  auto &a=_node1->f2_;

	#line 1802 "caio.caio"
                         
      map<string,int> refs;
      if(idr!=""s) add_altid(refs,idr,0);
      int n=0;
      for(auto &e:elist)
      { ++n;
        { auto &_match2=e;
if(auto _node2=dynamic_cast<trmelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1809 "caio.caio"
                               
          if(altid!=""s)
            add_altid(refs,altid,n);
          else
            add_altid(refs,id,n);
        }
else if(auto _node2=dynamic_cast<symelem_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1814 "caio.caio"
                               
          if(altid!=""s)
            add_altid(refs,altid,n);
          else
            add_altid(refs,id,n);
        }
else if(auto _node2=dynamic_cast<varelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1819 "caio.caio"
                               
          if(altid!=""s)
            add_altid(refs,altid,n);
          replace_refs(xl,altid);
        }
else if(auto _node2=dynamic_cast<optelem_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1823 "caio.caio"
                               
          if(altid!=""s)
            add_altid(refs,altid,n);
          replace_refs(xl,altid);
        }
else if(auto _node2=dynamic_cast<repelem1_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1827 "caio.caio"
                                 
          if(altid!=""s)
            add_altid(refs,altid,n);
          replace_refs(xl,altid);
        }
else if(auto _node2=dynamic_cast<repelem0_node *>(_match2)) {
  auto &xl=_node2->f1_;
  auto &altid=_node2->f2_;

	#line 1831 "caio.caio"
                                 
          if(altid!=""s)
            add_altid(refs,altid,n);
          replace_refs(xl,altid);
        }
}

	#line 1835 "caio.caio"
        
      }
      { auto &_match2=a;
if(auto _node2=dynamic_cast<gempty_node *>(_match2)) {

	#line 1838 "caio.caio"
                    
      }
else if(auto _node2=dynamic_cast<gterm_node *>(_match2)) {
  auto &t=_node2->f1_;

	#line 1839 "caio.caio"
                    
        replace_refs(t,refs);
      }
else if(auto _node2=dynamic_cast<gcode_node *>(_match2)) {
  auto &cc=_node2->f1_;

	#line 1841 "caio.caio"
                     
        replace_refs(cc,refs);
      }
}

	#line 1843 "caio.caio"
      
    }
}

	#line 1844 "caio.caio"
    
  }
}
void replace_refs(List<Grule> rules)
{ for(auto r:rules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 1850 "caio.caio"
                           
      replace_refs(body,id);
    }
}

	#line 1852 "caio.caio"
    
  }
}
string literal_to_re(const string &s)
{ string t=decode_string(s.substr(1,s.size()-2));
  string r="";
  static string meta="\\\'\"{}()*+.?[]/|$^ ";
  for(auto c:t)
  { if(c=='\n') r+="\\n";
    else if(c=='\t') r+="\\t";
    else if(meta.find(c)!=string::npos) { r+='\\'; r+=c; }
    else if((c&0xFF)>=0x7F || c=='<' || c=='>') { 
      r+="\\x"s; 
      ostringstream v;
      v<<hex<<(c&0xFF);
      r+=v.str();
    }
    else
      r+=c;
  }
  return r;
}
void gen_altnames()
{
  for(auto &s:symbols)
  {
    if(s.first[0]=='\'')
    { s.second.altname=s.first;
      if(!empty_type(s.second.tip))
      { s.second.altname="\""s+encode_string(decode_string(s.first.substr(1,s.first.size()-2)),0)+"\""s;
        s.second.terminalnumber=++terminal_uid;
      }
    }
    else if(s.first[0]=='?')
    { s.second.altname="\""s+encode_string(s.first,0)+"\""s;
      s.second.terminalnumber=++terminal_uid;
    }
    else if(s.first[0]=='\"')
    { s.second.altname="\""s+encode_string(decode_string(s.first.substr(1,s.first.size()-2)),0)+"\""s;
      s.second.terminalnumber=++terminal_uid;
    }
    else
    { 
      string a=encode_symbol(s.first);
      while(symbol_names.find(a)!=symbol_names.end())
      { a="g_"s+to_string(++symbol_uid);
      }
      symbol_names.insert(a);
      s.second.altname=a;
    }
  }
}
void find_return_field(List<Code> code)
{ for(auto c:code)
  { auto &_match1=c;
if(auto _node1=dynamic_cast<pcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 1907 "caio.caio"
                   
      find_return_field(cc);
    }
else if(auto _node1=dynamic_cast<token_node *>(_match1)) {
  auto &val=_node1->f1_;

	#line 1909 "caio.caio"
                    
      { string id=normalize_terminal(val);
        auto it=symbols.find(id);
        if(it==symbols.end())
          yyerror(id+" isn't used in rules");
        int rf=0;
        string tip=it->second.tip;
        if(!empty_type(tip))
        { if(union_fields.find(tip)!=union_fields.end())
            rf=union_fields[tip];
        }
        if(return_field!=0 && rf!=0 && return_field!=rf)
          yyerror("Return terminals with different types"s);
        if(rf!=0) return_field=rf;
      }
  }
}

	#line 1924 "caio.caio"
  
}
void gen_code(ostream& fout, Term t, int limit)
{ { auto &_match1=t;
if(auto _node1=dynamic_cast<tnode_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &args=_node1->f2_;

	#line 1928 "caio.caio"
                         
    { bool flg=0;
      bool loc;
      if((loc=nodes.find(id)!=nodes.end()) || id=="cons"s)
        fout<<"ast::";
      fout<<id<<"(";
      for(auto a:args)
      { if(flg) fout<<",";
        gen_coderef(fout,a,0,limit);
        flg=1;
      }
      if(gen_mode>=1 && loc && locations_flag==2)
      { if(flg) fout<<",";
        if(gen_mode==2)
          fout<<"&@$";
        else
          fout<<"&yylloc";
      }
      fout<<")";
    }
    }
else if(auto _node1=dynamic_cast<snode_node *>(_match1)) {
  auto &str=_node1->f1_;

	#line 1948 "caio.caio"
                     
      gen_coderef(fout,str,0,limit);
  }
}

	#line 1950 "caio.caio"
  
}
void print_re(ostream& fout, string s)
{
  if(s.substr(0,2)=="R\""s)
  { 
    
    size_t p1=s.find('(');
    size_t p2=s.rfind(')');
    if(p1>=2 && s.size()-p2-2==p1-2 && 
       string(p1-2,s[2])==s.substr(2,p1-2) && string(p1-2,s[2])==s.substr(p2+1,p1-2))
    { s=s.substr(p1+1,p2-p1-1);
      for(auto c:s)
      { if(c==' ') fout<<"\\ ";
        else fout<<c;
      }
    }
    else
      fout<<s;
  }
  else
    fout<<s;
}
void gen_lexrules(ostream& fout, List<Lrule> rules)
{ for(auto r:rules)
  {
    { auto &_match1=r;
if(auto _node1=dynamic_cast<lexrule_node *>(_match1)) {
  auto &sts=_node1->f1_;
  auto &re=_node1->f2_;
  auto &act=_node1->f3_;

	#line 1977 "caio.caio"
                               
      if(sts) {
        fout<<"<";
        bool flg=0;
        for(auto s:sts)
        { if(flg) fout<<",";
          fout<<s;
          flg=1;
        }
        fout<<">";
      }
      print_re(fout,re);
      fout<<"\t";
      { auto &_match2=act;
if(auto _node2=dynamic_cast<lterm_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &t=_node2->f2_;

	#line 1991 "caio.caio"
                       
         {
           fout<<"{";
           if(id)
           { string nid=normalize_terminal(id);
             auto it=symbols.find(nid);
             int rf=0;
             if(!empty_type(it->second.tip))
               rf=union_fields[it->second.tip];
             if(t)
             { 
               show_line(fout,t->yyloc.first.line-1,t->yyloc.first.column-(7+to_string(rf).size()+1));
               fout<<"yylval.f"<<to_string(rf)<<"_=";
               gen_mode=1;
               gen_code(fout,t,0);
               fout<<"; ";
             }
             else if(it->second.tip=="std::string"s || it->second.tip=="std::string?"s)
               fout<<" yylval.f"<<to_string(rf)<<"_=yytext; ";
             else if(it->second.tip=="char"s || it->second.tip=="char?"s)
               fout<<" yylval.f"<<to_string(rf)<<"_=yytext[0]; ";
             fout<<" return ";
             auto idt=symbols.find(nid);
             if(idt->second.terminalnumber>0)
               fout<<idt->second.terminalnumber;
             else 
               fout<<idt->second.altname;
           }
           else
             fout<<" return yyliteral(yytext)";
           fout<<"; }\n";
         }
      }
else if(auto _node2=dynamic_cast<lskip_node *>(_match2)) {

	#line 2023 "caio.caio"
                    fout<<";\n";
      }
else if(auto _node2=dynamic_cast<lnext_node *>(_match2)) {

	#line 2024 "caio.caio"
                    fout<<"|\n";
      }
else if(auto _node2=dynamic_cast<lcode_node *>(_match2)) {
  auto &code=_node2->f1_;

	#line 2025 "caio.caio"
                       
         return_field=0;
         find_return_field(code);
         gen_mode=1;
         fout<<"{";
         show_line(fout,(_node2->yyloc).first.line-1,(_node2->yyloc).first.column+1);
         gen_code(fout,code,0,0);
         fout<<"\t}\n";
      }
}

	#line 2033 "caio.caio"
      
    }
}

	#line 2034 "caio.caio"
    
  }
}
void create_lexfile(ostream& fout,const string &fn,List<Lrule> lrules)
{
  if(case_flag)
    fout<<"%option case-insensitive\n";
  if(inter_flag)
    fout<<"%option interactive\n";
  if(yywrap_flag==0)
    fout<<"%option noyywrap\n";
  fout<<"%option bison-bridge noline\n";
  fout<<"%top{\n"
        "#include \""<<fn<<".hpp\"\n";
  if(locations_flag!=0)
    fout<<"#define YY_USER_ACTION yysetloc();\n";
  if(locations_flag==1)
    fout<<"int yylineno;\n";
  fout<<"%}\n";
  fout<<R"___(
%class {
public:
  std::vector<std::string> filenames;
  int activefile;
%}
)___";
  fout<<R"___(
%init {
  filenames.push_back("");
  activefile=0;
%}
)___";
  if(locations_flag==2)
  fout<<R"___(
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
)___";
  else if(locations_flag==1)
  fout<<R"___(
%class {
  void yysetloc(){
#undef yylineno
    yylineno=lineno();
  }
%}
)___";
  gen_code(fout,lexcode,0,0);
  if(lex_states.size()>0)
  {
    fout<<"%x";
    for(auto s:lex_states)
      fout<<" "<<s;
    fout<<"\n";
  }
  for(auto &ld:lexdefs) {
    fout<<ld.id<<"\t";
    print_re(fout,ld.re);
    fout<<"\n";
  }
  fout<<"%%\n";
  if(locations_flag==1 || lexinitcode)
  {
    fout<<"%{\n";
    if(lex_states.size()>0)
      fout<<"default:";
    if(locations_flag==1)
      fout<<"\tyyclear_attr(yylval);\n";
    gen_code_line(fout,lexinitcode,0,0);
    fout<<"%}\n";
  }
  if(literal_flag)
  { 
    for(auto s:symbols)
    { if(isliteral(s.first))
      {
        fout<<literal_to_re(s.first)<<"\t";
        int rf=0;
        if(!empty_type(s.second.tip))
          rf=union_fields[s.second.tip];
        if(s.second.tip=="std::string"s || s.second.tip=="std::string?"s)
          fout<<"yylval.f"<<to_string(rf)<<"_=yytext; ";
        else if(s.second.tip=="char"s || s.second.tip=="char?"s)
          fout<<"yylval.f"<<to_string(rf)<<"_=yytext[0]; ";
        fout<<"return ";
        if(s.second.terminalnumber>0)
          fout<<s.second.terminalnumber;
        else 
          fout<<s.second.altname;
        fout<<";\n";
      }
    }
  }
  gen_lexrules(fout,lrules);
  if(lexdefault_flag!=1)
  {
    if(lex_states.size()>0)
    { fout<<"<INITIAL";
      for(auto s:lex_states)
        fout<<","<<s;
      fout<<">";
    }
    fout<<".|\\n\t";
    if(lexdefault_flag==0)
      fout<<"yyerror(\"No rules for char \"+std::to_string(yytext[0]&0xFF));\n";
    else if(lexdefault_flag==2)
      fout<<";\n";
    else
      fout<<"return yyliteral(yytext);\n";
  }
  fout<<"%%\n";
  if(locations_flag==2)
    fout<<R"___(
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner) {
  yyscanner_t* scanp=static_cast<yyscanner_t*>(scanner);
  yyclear_attr(*lvalp);
  int t=scanp->yylex(*lvalp);
  *llocp=scanp->yylloc;
  return t;
}
)___";
  fout<<R"___(
const char *yylex_filename(void* scanner, int i)
{ yyscanner_t* scanp=static_cast<yyscanner_t*>(scanner);
  if(i>=scanp->filenames.size()) return "";
  if(i<0) i=scanp->activefile;
  return scanp->filenames[i].c_str();
}
void yylex_init(yyscan_t *scanner, FILE *f, const std::string& n)
{ yyscanner_t* scanp=new yyscanner_t;
  *scanner = static_cast<yyscan_t>(scanp);
  scanp->in(reflex::Input(f));
  scanp->filenames[0]=n;
}
void yylex_init(yyscan_t *scanner, const std::string& s)
{ yyscanner_t* scanp=new yyscanner_t;
  *scanner = static_cast<yyscan_t>(scanp);
  scanp->in(s);
}
void yylex_init(yyscan_t *scanner, std::istream &s, const std::string& n)
{ yyscanner_t* scanp=new yyscanner_t;
  *scanner = static_cast<yyscan_t>(scanp);
  scanp->in(reflex::Input(s));
  scanp->filenames[0]=n;
}
)___";
}
bool need_destroy(const string &t)
{ if(empty_type(t)) return 0;
  if(t=="std::string?"s || t=="std::string"s) return 1;
  if(t.back()=='?' || is_builtin_type(t)) return 0;
  return 1;
}
void create_grmfile(ostream& fout,const string &fn, List<Grule> rules)
{
  if(locations_flag==2)
    fout<<"%locations\n";
  fout<<"%define parse.error verbose\n"
        "%define api.pure full\n"
        "%param { void *scanner }\n"
        "%no-lines\n";
  if(expect_flag>=0)
    fout<<"%expect "<<expect_flag<<"\n";
  fout<<"%{\n";
  fout<<"#include \""<<fn<<".hpp\"\n";
if(locations_flag==2)
  fout<<R"___(
#define YYLLOC_DEFAULT(Current, Rhs, N)                        \
    do {                                                       \
      if (N)                                                   \
        {                                                      \
          (Current).first   = YYRHSLOC (Rhs, 1).first;         \
          (Current).last  = YYRHSLOC (Rhs, N).last;            \
        }                                                      \
      else                                                     \
        {                                                      \
          (Current).first = (Current).last = YYRHSLOC (Rhs, 0).last; \
        }                                                      \
      yyclear_attr(yyval);                                     \
    } while (0)
)___";
  fout<<"%}\n";
  gen_code(fout,grmcode,0,0);
  for(auto s:symbols)
  { if(isterminal(s.first))
    {
      if(s.second.terminalnumber)
      { fout<<"%token ";
        if(!empty_type(s.second.tip))
          fout<<"<f"<<union_fields[s.second.tip]<<"_> ";
        fout<<"T_"<<s.second.terminalnumber<<" "<<s.second.terminalnumber<<" "<<s.second.altname<<"\n";
      }
    }
    else if(!empty_type(s.second.tip))
    { fout<<"%type <f"<<union_fields[s.second.tip]<<"_> "<<s.second.altname<<"\n";
    }
  }
  string root_id;
  { auto &_match1=rules[0];
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 2241 "caio.caio"
                          
      if(!empty_type(symbols[id].tip)) {
        string tip=symbols[id].tip;
        root_id=id;
        root_tip=tip;
        if(tip.back()=='?') tip.pop_back();
        fout<<"%destructor { ";
        if(astprint_flag && main_flag)
          fout<<"if(yydebug_flag==2) ast::astprint(std::cout,$$); else ";
        fout<<"YYINTERPRET($$,scanner); ";
        if(need_destroy(tip))
           fout<<"ast::destroy($$); ";
        fout<<"} "<<symbols[id].altname<<"\n";
      }
      else
        root_tip="";
  }
}

	#line 2257 "caio.caio"
  
  for(auto &uf:union_fields)
  { string t=uf.first;
    if(root_tip!=""s && t==root_tip && need_destroy(t))
    { vector<string> root_syms;
      for(auto &sym:symbols)
      { if(sym.second.tip==root_tip && sym.first!=root_id)
          root_syms.push_back(sym.second.altname);
      }
      if(root_syms.size()>0)
      { 
        fout<<"%destructor { ast::destroy($$); }";
        for(auto &sym:root_syms)
          fout<<" "<<sym;
        fout<<"\n";
      }
    }
    else if(need_destroy(t))
    { 
      fout<<"%destructor { ast::destroy($$); } <f"<<uf.second<<"_>\n";
    }
  }
  fout<<"%%\n";
  for(auto r:rules)
  {
    { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 2283 "caio.caio"
                           
      fout<<symbols[id].altname<<"\t:";
      int flg=0;
      for(auto x : body)
      { if(flg) fout<<"\t|";
        { auto &_match2=x;
if(auto _node2=dynamic_cast<xrule_node *>(_match2)) {
  auto &elist=_node2->f1_;
  auto &act=_node2->f2_;

	#line 2289 "caio.caio"
                               
          {
            for(auto &e:elist)
            { { auto &_match3=e;
if(auto _node3=dynamic_cast<trmelem_node *>(_match3)) {
  auto &str=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 2293 "caio.caio"
                                       
                auto &sym=symbols[normalize_terminal(str)];


                  fout<<" "<<sym.altname;
              }
else if(auto _node3=dynamic_cast<symelem_node *>(_match3)) {
  auto &str=_node3->f1_;
  auto &altid=_node3->f2_;

	#line 2299 "caio.caio"
                                       
                fout<<" "<<symbols[str].altname;
              }
}

	#line 2301 "caio.caio"
              
            }
            { auto &_match3=act;
if(auto _node3=dynamic_cast<gempty_node *>(_match3)) {

	#line 2304 "caio.caio"
                             
                if(locations_flag!=2)
                  fout<<"\t{ yyclear_attr(yyval); }\n";
                else
                  fout<<"\n";
              }
else if(auto _node3=dynamic_cast<gcode_node *>(_match3)) {
  auto &cc=_node3->f1_;

	#line 2309 "caio.caio"
                             
                { fout<<"\t{";
                  if(locations_flag!=2)
                    fout<<" yyclear_attr(yyval);";
                  set<int> refs;
                  collect_refs(cc,refs);
                  gen_mode=2;
                  gen_code_line(fout,cc,0,elist.size());
                  int n=0;
                  bool used=refs.find(0)!=refs.end();
                  for(auto &e:elist)
                  { ++n;
                    if(!used || refs.find(n)==refs.end())
                    { 
                      symbolinfo *sym=nullptr;
                      { auto &_match4=e;
if(auto _node4=dynamic_cast<trmelem_node *>(_match4)) {
  auto &str=_node4->f1_;
  auto &altid=_node4->f2_;

	#line 2325 "caio.caio"
                                               
                        sym=&symbols[normalize_terminal(str)];
                      }
else if(auto _node4=dynamic_cast<symelem_node *>(_match4)) {
  auto &str=_node4->f1_;
  auto &altid=_node4->f2_;

	#line 2327 "caio.caio"
                                              
                        sym=&symbols[str];
                      }
}

	#line 2329 "caio.caio"
                      
                      if(sym!=nullptr && need_destroy(sym->tip))
                          fout<<" ast::destroy($"<<n<<");";
                    }
                  }
                  fout<<" }\n";
                }
              }
else if(auto _node3=dynamic_cast<gterm_node *>(_match3)) {
  auto &t=_node3->f1_;

	#line 2336 "caio.caio"
                            
                { fout<<"\t{";
                  if(locations_flag!=2)
                    fout<<" yyclear_attr(yyval);";
                  show_line(fout,t->yyloc.first.line,t->yyloc.first.column-2);
                  fout<<"$$=";
                  gen_mode=2;
                  set<int> refs;
                  refs.insert(0);
                  collect_refs(t,refs);
                  gen_code(fout,t,elist.size());
                  fout<<";\n";
                  int n=0;
                  for(auto &e:elist)
                  { ++n;
                    symbolinfo *sym=nullptr;
                    { auto &_match4=e;
if(auto _node4=dynamic_cast<trmelem_node *>(_match4)) {
  auto &str=_node4->f1_;
  auto &altid=_node4->f2_;

	#line 2353 "caio.caio"
                                             
                      sym=&symbols[normalize_terminal(str)];
                    }
else if(auto _node4=dynamic_cast<symelem_node *>(_match4)) {
  auto &str=_node4->f1_;
  auto &altid=_node4->f2_;

	#line 2355 "caio.caio"
                                            
                      sym=&symbols[str];
                    }
}

	#line 2357 "caio.caio"
                    
                    if(sym!=nullptr && need_destroy(sym->tip)) 
                    { 
                      if(refs.find(n)==refs.end())
                         fout<<" ast::destroy($"<<n<<");";
                      else if(sym->tip=="std::string"s || sym->tip=="std::string?"s)
                      { if(!is_string_use(t,n))
                          fout<<" ast::destroy($"<<n<<");";
                      }
                    }
                  }
                  fout<<" }\n";
                }
            }
}

	#line 2370 "caio.caio"
            
          }
        }
}

	#line 2372 "caio.caio"
        
        flg=1;
      }
      fout<<"\t;\n";
    }
}

	#line 2376 "caio.caio"
    
  }
  fout<<"%%\n";
}
string to_field_type(const string &tip)
{ if(tip.back()=='?')
    return "ast::Value<"s+tip.substr(0,tip.size()-1)+">"s;
  else if(is_big_builtin_type(tip))
    return "ast::Value<"s+tip+">"s;
  else
    return tip;
}
void create_hfile(ostream& fout,const string &fn)
{ 
  string ufn=fn;
  for(auto &c:ufn)
    c=toupper(c);
  fout<<"#ifndef "<<ufn<<"_H\n";
  fout<<"#define "<<ufn<<"_H 1\n";
if(using_list.size()>0)
{
  for(auto &ul:using_list)
    fout<<"#include \""<<ul<<".hpp\""<<"\n";
}
else
{
  fout<<R"___(
#ifndef ASTTYPES_H
#define ASTTYPES_H 1
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <exception>
#include <utility>
#include <vector>
#include <initializer_list>
)___";
if(locations_flag==2)
fout<<R"___(
struct YYPTYPE {
  int line;
  short file, column;
};
struct YYLTYPE {
  YYPTYPE first,last;
  YYLTYPE(int fl=0,int fc=0,int ll=0,int lc=0, int ff=0){ 
     first.line=fl; first.column=fc;
     last.line=ll; last.column=lc;
     first.file=last.file=ff;
  }
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
)___";
fout<<R"___(
namespace ast {

template <typename T> inline void destroy(T& p) { }
template <typename T> inline void destroy(T*& p) { if(p) delete p; p=nullptr; }
)___";
if(usestring_flag || usevalue_flag)
fout<<R"___(
template <typename T>
class Value {
  int _assigned;
  T _value;
  void check() const { if(!_assigned) throw std::logic_error("value isn't assigned"); }
public:
  Value()=default;
  explicit Value(const T& v){ _assigned=1; _value=v; }
  Value(const Value<T>& v)=default;
  Value(std::nullptr_t) { _assigned=0; }
  operator T() const { check(); return _value; }
  operator bool() const{ return _assigned!=0; }
  bool operator!() const{ return !_assigned; }
  Value<T> operator~() const{ check(); return Value<T>(~_value); }
  Value<T> operator-() const{ check(); return Value<T>(-_value); }
  Value<T> &operator=(const T& v) { _assigned=1; _value=v; }
  Value<T> &operator=(std::nullptr_t) { _assigned=0; }
  Value<T> &operator=(const Value<T>& v)=default;
  Value<T> &operator+=(const T& v) { check(); _value+=v; return *this; }
  Value<T> &operator-=(const T& v) { check(); _value-=v; return *this; }
  Value<T> &operator*=(const T& v) { check(); _value*=v; return *this; }
  Value<T> &operator/=(const T& v) { check(); _value/=v; return *this; }
  Value<T> &operator%=(const T& v) { check(); _value%=v; return *this; }
  Value<T> &operator<<=(const T& v) { check(); _value<<=v; return *this; }
  Value<T> &operator>>=(const T& v) { check(); _value>>=v; return *this; }
  Value<T> &operator&=(const T& v) { check(); _value&=v; return *this; }
  Value<T> &operator|=(const T& v) { check(); _value|=v; return *this; }
  Value<T> &operator^=(const T& v) { check(); _value^=v; return *this; }
  Value<T> &operator++() { check(); ++_value; return *this; }
  Value<T> &operator--() { check(); --_value; return *this; }
  T *operator&() { _assigned=1; return &_value; }
  friend inline std::istream &operator>>(std::istream&s, Value<T> &v) { v._assigned=1; return s>>v._value; }
  friend inline std::ostream &operator<<(std::ostream&s, const Value<T> &v) { return s<<T(v); }
};
template <typename T>
inline Value<T> operator+(Value<T> v1, const Value<T>& v2) { return v1+=v2; }
template <typename T>
inline Value<T> operator-(Value<T> v1, const Value<T>& v2) { return v1-=v2; }
template <typename T>
inline Value<T> operator*(Value<T> v1, const Value<T>& v2) { return v1*=v2; }
template <typename T>
inline Value<T> operator/(Value<T> v1, const Value<T>& v2) { return v1/=v2; }
template <typename T>
inline Value<T> operator%(Value<T> v1, const Value<T>& v2) { return v1%=v2; }
template <typename T>
inline Value<T> operator<<(Value<T> v1, const Value<T>& v2) { return v1<<=v2; }
template <typename T>
inline Value<T> operator>>(Value<T> v1, const Value<T>& v2) { return v1>>=v2; }
template <typename T>
inline Value<T> operator&(Value<T> v1, const Value<T>& v2) { return v1&=v2; }
template <typename T>
inline Value<T> operator|(Value<T> v1, const Value<T>& v2) { return v1|=v2; }
template <typename T>
inline Value<T> operator^(Value<T> v1, const Value<T>& v2) { return v1^=v2; }
template <typename T>
bool operator==(const Value<T> &v1, const Value<T>& v2) {
   if(!v1 && !v2) return 1;
   if(!v1 || !v2) return 0;
   return  T(v1)==T(v2); 
}
template <typename T>
bool operator<(const Value<T> &v1, const Value<T>& v2) { 
  if(!v1 && !v2) return 0;
  if(!v1) return 1;
  if(!v2) return 0;
  return T(v1)<T(v2); 
}
template <typename T>
inline bool operator!=(const Value<T> &v1, const Value<T>& v2) { return !(v1==v2); }
template <typename T>
inline bool operator>(const Value<T> &v1, const Value<T>& v2) { return v2<v1; }
template <typename T>
inline bool operator<=(const Value<T> &v1, const Value<T>& v2) { return !(v2<v1); }
template <typename T>
inline bool operator>=(const Value<T> &v1, const Value<T>& v2) { return !(v1<v2); }
template <typename T>
Value<T> operator++(Value<T> &v, int)
{ Value<T> v2(v);
  ++v;
  return v2;
}
template <typename T>
Value<T> operator--(Value<T> &v, int)
{ Value<T> v2(v);
  --v;
  return v2;
}
)___";
if(usestring_flag)
fout<<R"___(
template <>
class Value<std::string> {
  size_t _len;
  char *_str;
  void check() const { if(!_str) throw std::logic_error("value isn't assigned"); }
  void del_ptr() { if(_str) free(_str); _str=nullptr; _len=0; }
  void new_ptr(const char *s, size_t l) { _len=l; if(s) _str=strdup(s); else _str=nullptr; }
public:
  Value()=default;
  explicit Value(const char *s) { new_ptr(s,strlen(s)); }
  Value(const char *s, int l) { new_ptr(s,l); }
  explicit Value(const std::string &s) { new_ptr(s.c_str(),s.length()); }
  Value(std::nullptr_t) { new_ptr(nullptr,0); }
  operator std::string() const { check(); return _str; }
  operator bool() const{ return _str!=nullptr; }
  bool operator!() const{ return !_str; }
  const char *c_str() const { check(); return _str; }
  size_t size() const { check(); return _len; }
  size_t length() const { check(); return _len; }
  char operator[](size_t i) const { check(); return _str[i]; }
  char at(size_t i) const { check(); if(i>=_len) throw std::out_of_range("index out of range"); return _str[i]; }
  std::string substr(size_t i, size_t n=std::string::npos) const { check(); return ((std::string)_str).substr(i,n); }
  Value<std::string> &operator=(const std::string& s) { del_ptr(); new_ptr(s.c_str(),s.length()); return *this; }
  Value<std::string> &operator=(const char *s) { del_ptr(); new_ptr(s,strlen(s)); return *this; }
  Value<std::string> &operator=(std::nullptr_t) { del_ptr(); new_ptr(nullptr,0); return *this; }
  Value<std::string> &operator=(const Value<std::string>& v)=default;
  Value<std::string> &operator+=(const std::string& s) { check(); (*this)=(std::string)_str+s; return *this; }
  Value<std::string> &operator+=(const char *s) { check(); (*this)=(std::string)_str+(std::string)s; return *this; }
  Value<std::string> &operator+=(char c) { check(); (*this)=(std::string)_str+std::string(1,c); return *this; }
  friend inline std::istream &operator>>(std::istream&s, Value<std::string> &v) { std::string x; s>>x; v=x; return s; }
  friend inline std::ostream &operator<<(std::ostream&s, const Value<std::string> &v) { v.check(); return s<<v._str; }
  friend inline void destroy(Value<std::string> &v) { v.del_ptr(); }
};
template <typename T>
inline T operator+(const T &v1, const Value<T>& v2) { return v1+T(v2); }
template <typename T>
inline T operator+(const Value<T>& v1, const T& v2) { return T(v1)+v2; }
template <typename T>
bool operator==(const T &v1, const Value<T>& v2) { 
  if(!v2) return 0;
  return v1==T(v2); 
}
template <typename T>
bool operator==(const Value<T> &v1, const T& v2) {
  if(!v1) return 0;
  return T(v1)==v2; 
}
template <typename T>
bool operator<(const T &v1, const Value<T>& v2) { 
  if(!v2) return 0;
  return v1<T(v2); 
}
template <typename T>
bool operator<(const Value<T> &v1, const T& v2) { 
  if(!v1) return 1;
  return T(v1)<v2; 
}
template <typename T>
inline bool operator!=(const T &v1, const Value<T>& v2) { return !(v1==v2); }
template <typename T>
inline bool operator!=(const Value<T> &v1, const T& v2) { return !(v1==v2); }
template <typename T>
inline bool operator>(const T &v1, const Value<T>& v2) { return v2<v1; }
template <typename T>
inline bool operator>(const Value<T> &v1, const T& v2) { return v2<v1; }
template <typename T>
inline bool operator<=(const T &v1, const Value<T>& v2) { return !(v2<v1); }
template <typename T>
inline bool operator<=(const Value<T> &v1, const T& v2) { return !(v2<v1); }
template <typename T>
inline bool operator>=(const T &v1, const Value<T>& v2) { return !(v1<v2); }
template <typename T>
inline bool operator>=(const Value<T> &v1, const T& v2) { return !(v1<v2); }
)___";
if(uselist_flag)
fout<<R"___(
template <typename T> class List;
template <typename T> List<T> cons(const T& p);
template <typename T> List<T> cons(List<T> l, const T& p);
template <typename T> List<T> cons(const T& p, List<T> l);
)___";
if(uselist_flag && (usestring_flag || usevalue_flag))
fout<<R"___(
template <typename T> List<T> cons(const Value<T> &p);
template <typename T> List<T> cons(List<T> l, const Value<T> &p);
template <typename T> List<T> cons(const Value<T> & p, List<T> l);
)___";
if(uselist_flag)
fout<<R"___(
template <typename T> List<T> cons(List<T> l1, List<T> l2);
template <typename T> List<T> begin(List<T> l);
template <typename T> List<T> end(List<T> l);
template <typename T> bool operator==(const List<T> &l, const List<T> &r);
template <typename T> List<T> &operator++(List<T> &l);
template <typename T> void destroy(List<T> &l);

template <typename T>
class List {
  struct Node {
    T head;
    Node *tail;
    Node(const T& h, Node* t):head(h),tail(t){}
  };
  Node *first;
  Node *last;
  size_t _size;
  void add_last(Node *n) { 
    n->tail=nullptr;
    ++_size;  
    if(first==nullptr) first=last=n;
    else { last->tail=n; last=n; }
  }
  void add_first(Node *n) { 
    n->tail=first;
    ++_size;
    if(first==nullptr) first=last=n; 
    else first=n;
  }
public:
  List()=default;
  List(std::nullptr_t) { first=last=nullptr; _size=0; }
  List(std::initializer_list<T> v);
  T &operator*() { return first->head; }
  T *operator->() { return &(first->head); }
  T &operator[](size_t i);
  size_t size() const { return _size; }
  template <typename UnaryPredicate> List<T> split(UnaryPredicate pred);
  List<T>& operator=(std::nullptr_t) { first=nullptr; last=nullptr; return *this; }
  
  friend List<T> cons<T>(const T& p);
  friend List<T> cons<T>(List<T> l, const T& p);
  friend List<T> cons<T>(const T& p, List<T> l);
)___";
if(uselist_flag && (usestring_flag || usevalue_flag))
fout<<R"___(
  friend List<T> cons<T>(const Value<T> &p);
  friend List<T> cons<T>(List<T> l, const Value<T> &p);
  friend List<T> cons<T>(const Value<T> & p, List<T> l);
)___";
if(uselist_flag)
fout<<R"___(
  template <typename Z> friend List<Z*> cons(Z *p);
  template <typename Z> friend List<Z*> cons(List<Z*> l, Z *p);
  template <typename Z> friend List<Z*> cons(Z* p, List<Z*> l);
  
  friend List<T> cons<T>(List<T> l1, List<T> l2);
  friend List<T> begin<T>(List<T> l);
  friend List<T> end<T>(List<T> l);
  friend void destroy<T>(List<T> &l);
  friend bool operator==<T>(const List<T> &l, const List<T> &r);
  friend List<T> &operator++ <T>(List<T> &l);
  operator bool() const { return first!=nullptr; }
  bool operator!() const { return first==nullptr; }
};
template <typename T> 
void destroy(List<T> &l) {
  List<T> t,r=begin(l),e=end(l); 
  while(r!=e)
  { t=r; 
    ++r;
    destroy(t.first->head);
    delete t.first;
  }
  l=nullptr;
}
template <typename T> 
  template <typename UnaryPredicate>
List<T> List<T>::split(UnaryPredicate pred)
{ List<T> r1=nullptr,r2=nullptr;
  List<T> t,r=begin(*this),e=end(*this); 
  while(r!=e)
  { t=r;
    ++r;
    if(pred(t.first->head))
      r1.add_last(t.first);
    else
      r2.add_last(t.first);
  }
  *this=r2;
  return r1;
}
template <typename T>
List<T>::List(std::initializer_list<T> v)
{ first=nullptr;
  last=nullptr;
  _size=v.size();
  for(auto &x:v)
  { Node *t=new typename List<T>::Node(x,nullptr);
    if(!first) first=last=t;
    else 
    { last->tail=t;
      last=t;
    }
  }
}
template <typename T>
T &List<T>::operator[](size_t i)
{ if(i>=_size) throw std::out_of_range(std::string("index ")+std::to_string(i)+std::string(" is out List's size ")+std::to_string(_size));
  if(i==0) return first->head;
  if(i==_size-1) return last->head;
  Node *t=first;
  while(i>0) { t=t->tail; --i; }
  return t->head;
}
template <typename T>
List<T> cons(const T& p)
{ List<T> r; 
  r.first=r.last=new typename List<T>::Node(p,nullptr);
  r._size=1;
  return r;
}
template <typename T>
List<T> cons(List<T> l, const T& p)
{ 
  if(l.first==nullptr) return cons(p);
  List<T> r;
  r.first=l.first;
  l.last->tail=new typename List<T>::Node(p,nullptr);
  r.last=l.last->tail;
  r._size=l._size+1;
  return r;
}
template <typename T>
List<T> cons(const T& p, List<T> l)
{
  if(l.first==nullptr) return cons(p);
  List<T> r;
  r.first=new typename List<T>::Node(p,l.first);
  r.last=l.last;
  r._size=l._size+1;
  return r;
}
template <typename T>
inline List<T> cons(List<T> l)
{
  return l;
}
)___";
if(uselist_flag && (usestring_flag || usevalue_flag))
fout<<R"___(
template <typename T>
List<T> cons(const Value<T> & p)
{ 
  if(!p) return List<T>(nullptr);
  return cons(static_cast<T>(p));
}
template <typename T>
List<T> cons(List<T> l, const Value<T> &p)
{ 
  if(!p) return l;
  return cons(l,static_cast<T>(p));
}
template <typename T>
List<T> cons(const Value<T> &p, List<T> l)
{
  if(!p) return l;
  return cons(static_cast<T>(p),l);
}
)___";
if(uselist_flag)
fout<<R"___(
template <typename T>
List<T *> cons(T* p)
{ List<T*> r(nullptr);
  if(!p) return r;
  r.first=r.last=new typename List<T*>::Node(p,nullptr);
  r._size=1;
  return r;
}
template <typename T>
List<T*> cons(List<T*> l, T *p)
{ 
  if(!p) return l;
  if(l.first==nullptr) return cons(p);
  List<T*> r;
  r.first=l.first;
  r.last=l.last->tail=new typename List<T*>::Node(p,nullptr);
  r._size=l._size+1;
  return r;
}
template <typename T>
List<T*> cons(T *p, List<T*> l)
{
  if(!p) return l;
  if(l.first==nullptr) return cons(p);
  List<T*> r;
  r.first=new typename List<T*>::Node(p,l.first);
  r.last=l.last;
  r._size=l._size+1;
  return r;
}

template <typename T>
List<T> cons(List<T> l1, List<T> l2)
{ 
  if(l1.first==nullptr) return l2;
  if(l2.first==nullptr) return l1;
  List<T> r;
  r.first=l1.first;
  l1.last->tail=l2.first;
  r.last=l2.last;
  r._size=l1._size+l2._size;
  return r;
}
template <typename T>
inline List<T> begin(List<T> l)
{ return l;
}
template <typename T>
inline List<T> end(List<T> l)
{ l.first=0;
  l._size=0;
  return l;
}
template <typename T>
inline bool operator==(const List<T> &l, const List<T> &r)
{ return l.first==r.first && l.last==r.last;
}
template <typename T>
inline bool operator!=(const List<T> &l, const List<T> &r)
{ return !(l==r);
}
template <typename T>
inline List<T> &operator++(List<T> &l)
{ if(l.first==l.last) l.first=nullptr;
  else l.first=l.first->tail;
  --l._size;
  return l;
}
template <typename T>
inline List<T> operator++(List<T> &l, int)
{ List<T> r(l);
  ++l;
  return r;
}
)___";
fout<<R"___(
#ifndef AST_BASE_DOMAIN
#define AST_BASE_DOMAIN 1
struct _domain {
)___";
if(locations_flag==2)
fout<<R"___(
  YYLTYPE yyloc;
  _domain(const YYLTYPE *_loc) { if(_loc) yyloc=*_loc; else memset(&yyloc,0,sizeof(yyloc)); }
)___";
fout<<R"___(
  virtual ~_domain(){}
};
#endif
}
#endif
)___";
}
  if(domains.size()>0)
  {
  fout<<"namespace ast {\n";
  for(auto &d:domains)
  { 
    if(visitor_flag==2)
      fout<<"struct "<<d.first<<"_visitor;\n";
    fout<<"struct "<<d.first<<"_domain : _domain {\n";
    if(locations_flag==2)
      fout<<"\t"<<d.first<<"_domain(const YYLTYPE *_loc):_domain(_loc) {}\n";
    if(visitor_flag==2)
      fout<<"\tvirtual void accept("<<d.first<<"_visitor*, void*)=0;\n";
    fout<<"};\n";
    fout<<"typedef "<<d.first<<"_domain *"<<d.first<<";\n";
    if(astprint_flag)
      fout<<"int astprint(std::ostream&, "<<d.first<<", int=0, const char* =nullptr);\n";
  }
  for(auto &n:nodes)
  { 
    fout<<"struct "<<n.first<<"_node : "<<n.second.types[0]<<"_domain {\n";
    for(int j=1;j<n.second.types.size();++j)
    {
      fout<<"\t"<<type_mark(n.second.types[j],0)<<" f"<<j<<"_;\n";
    }
    fout<<"\t"<<n.first<<"_node(";
    if(n.second.types.size()>1)
    {
      for(int j=1;j<n.second.types.size();++j) 
      {
        fout<<type_mark(n.second.types[j],1)<<" a"<<j;
        if(j<n.second.types.size()-1)
          fout<<", ";
        else if(locations_flag==2)
          fout<<", const YYLTYPE *_loc=nullptr):"<<n.second.types[0]<<"_domain(_loc), ";
        else
          fout<<"):";
      }
      for(int j=1;j<n.second.types.size();++j)
      {
        fout<<"f"<<j<<"_(a"<<j<<")";
        if(j<n.second.types.size()-1)
          fout<<", ";
      }
    }
    else if(locations_flag==2)
      fout<<"const YYLTYPE *_loc=nullptr):"<<n.second.types[0]<<"_domain(_loc) ";
    else
      fout<<")";
    fout<<"{}\n";
    int kd=0;
    for(int j=1;j<n.second.types.size();++j)
    { string t=n.second.types[j];
      if(t=="std::string"s) ;
      else if(need_destroy(t))
        ++kd;
    }
    if(kd>0)
    {
      fout<<"\t~"<<n.first<<"_node() {\n";
      for(int j=1;j<n.second.types.size();++j)
      { string t=n.second.types[j];
        if(t=="std::string"s) ;
        else if(need_destroy(t))
        {
          fout<<"\t  destroy(f"<<j<<"_);\n";
        }
      }
      fout<<"\t}\n";
    }
    if(visitor_flag==2)
      fout<<"\tvoid accept("<<n.second.types[0]<<"_visitor*, void*);\n";
    fout<<"};\n";
  }
  for(auto &n:nodes)
  { 
    fout<<"inline "<<n.second.types[0]<<" "<<n.first<<"(";
     
    for(int j=1;j<n.second.types.size();++j) 
    {
      fout<<type_mark(n.second.types[j],1)<<" a"<<j;
      if(j<n.second.types.size()-1)
        fout<<", ";
    }
    if(locations_flag==2)
    { if(n.second.types.size()>1)
        fout<<", ";
      fout<<"const YYLTYPE *_loc=nullptr";
    }
    fout<<") {\n";
    fout<<"\treturn new "<<n.first<<"_node(";
    for(int j=1;j<n.second.types.size();++j) 
    {
      fout<<"a"<<j;
      if(j<n.second.types.size()-1)
        fout<<", ";
    }
    if(locations_flag==2)
    { if(n.second.types.size()>1)
        fout<<", ";
      fout<<"_loc";
    }
    fout<<");\n"
        <<"}\n";
  }
  if(visitor_flag==2)
  {
    for(auto &d:domains)
    { 
      fout<<"struct "<<d.first<<"_visitor {\n\tvirtual ~"<<d.first<<"_visitor(){}\n";
      for(auto &n:d.second.nodes)
      { fout<<"\tvirtual void visit("<<n<<"_node*, void*) {}\n";
      }
      fout<<"};\n";
      fout<<"template <typename T> struct "<<d.first<<"_Tvisitor: "<<d.first<<"_visitor {\n";
      fout<<"\tT operator()("<<d.first<<" v){ T r; if(v) v->accept(this,&r); return r; }\n";
      for(auto &n:d.second.nodes)
      { fout<<"\tvirtual T visit("<<n<<"_node*) { return T(); }\n";
        fout<<"\tvoid visit("<<n<<"_node* n,void* r) { *static_cast<T*>(r)=visit(n); }\n";
      }
      fout<<"};\n";
      fout<<"template <> struct "<<d.first<<"_Tvisitor<void>: "<<d.first<<"_visitor {\n";
      fout<<"\tvoid operator()("<<d.first<<" v){ if(v) v->accept(this,nullptr); }\n";
      for(auto &n:d.second.nodes)
      { fout<<"\tvirtual void visit("<<n<<"_node*) {}\n";
        fout<<"\tvoid visit("<<n<<"_node* n,void* r) { visit(n); }\n";
      }
      fout<<"};\n";
    }
    for(auto &n:nodes)
    { 
      fout<<
        "inline void "<<n.first<<"_node::accept("<<n.second.types[0]<<"_visitor* v, void* r) {\n"
        "\tv->visit(this, r);\n}\n";
    }
  }
  fout<<"}\n";
  }
  fout<<"using namespace ast;\n";
if(using_list.size()==0 && ast_flag==0)
{
  if(locations_flag==1)
    fout<<"extern int yylineno;\n";
  fout<<"int yyliteral(const std::string&);\n"
        "int yywrap();\n"
        "int yyparse(void*);\n";
  if(main_flag)
    fout<<"extern const char* yyinputfile;\n"
          "extern int yydebug_flag;\n";
  if(union_fields.size()>0)
  { fout<<"union YYSTYPE {\n";
    for(auto &f:union_fields)
      fout<<"  "<<to_field_type(f.first)<<" f"<<f.second<<"_;\n";
    fout<<"};\n";
    fout<<"template <typename T> inline T& YYSTYPE_cast(YYSTYPE &v){ return *reinterpret_cast<T*>(&v); }\n";
  }
  else
    fout<<"typedef int YYSTYPE;\n";
  fout<<"inline void yyclear_attr(YYSTYPE&v) { memset(&v,0,sizeof(v)); }\n"
          "#define YYSTYPE_IS_TRIVIAL 1\n"
          "#define YYSTYPE_IS_DECLARED 1\n";
  fout<<"void yylex_destroy(void*);\n"
        "const char* yylex_filename(void*, int=-1);\n"
        "void yylex_init(void**);\n"
        "void yylex_init(void**, const std::string&);\n"
        "void yylex_init(void**, FILE*, const std::string&);\n"
        "void yylex_init(void**, std::istream &, const std::string&);\n";
  if(locations_flag==2)
    fout<<"int yylex(YYSTYPE*, YYLTYPE*, void*);\n";
  else
    fout<<"int yylex(YYSTYPE*, void*);\n";
  if(lexprint_flag)
    fout<<"void lexprint(std::ostream&, int, YYSTYPE&);\n";
}
if(using_list.size()==0)
{
  fout<<"void yyerror(const std::string &);\n";
  if(locations_flag==2)
    fout<<"void yyerror(YYLTYPE*, void*, const char*);\n";
  else
    fout<<"void yyerror(void*, const char*);\n";
}
if(yyinterpret_flag && root_tip!="") {
  fout<<"void yyinterpret("<<type_mark(root_tip,1)<<");\n";
  fout<<"#define YYINTERPRET(ast,scanner) yyinterpret(ast)\n";
}
else
  fout<<"#define YYINTERPRET(ast,scanner)\n";
fout<<"#define YYONERROR exit(1)\n";
gen_mode=0;
gen_code_line(fout,hcode,0,0);

if((astprint_flag || lexprint_flag) && using_list.size()==0)
{
    fout<<R"___(
namespace ast {
#ifndef ASTPRINT_BUILTIN
#define ASTPRINT_BUILTIN 1
static void print_char(std::ostream &s, char v)
{ if(v=='\n') s<<"\\n";
  else if(v=='\'' || v=='\\' || v=='\"') s<<'\\'<<v;
  else s<<v;
}
static void print_indent(std::ostream &s, int i)
{ s<<'\n';
  if(i) { s.width(i); s<<' '; }
}
static int astprint(std::ostream &s, char v, int=0, const char *p=nullptr)
{ s<<"'";
  print_char(s,v);
  s<<"'";
  if(p) s<<p;
  return 0;
}
static int astprint(std::ostream &s, const std::string &v, int=0, const char *p=nullptr)
{ s<<'\"';
  for(auto x:v) print_char(s,x);
  s<<'\"';
  if(p) s<<p;
  return 0;
}
template <typename T> 
inline int astprint(std::ostream &s, T v, int=0, const char *p=nullptr)
{ s<<v; 
  if(p) s<<p;
  return 0;
}
#endif
)___";
if(usevalue_flag || usestring_flag)
fout<<R"___(
template <typename T>
int astprint(std::ostream &s, Value<T> v, int=0, const char *p=nullptr)
{ if(!v) s<<"nullptr";
  else astprint(s,T(v));
  if(p) s<<p;
  return 0;
}
)___";
if(uselist_flag)
fout<<R"___(
template <typename T>
int astprint(std::ostream &s, List<T> v, int i=0, const char *p=nullptr)
{ bool fl=0, r=0;
  s<<"[";
  for(auto x:v)
  {
    if(fl) s<<",";
    r+=astprint(s,x,i+2);
    fl=1;
  }
  if(r) print_indent(s,i);
  s<<"]";
  if(p) s<<p;
  return r;
}
)___";
fout<<"}\n";
}
  fout<<"#endif\n";
}
void create_cppfile(ostream& fout,const string &fn, List<Code> code)
{
  fout<<"#include \""<<fn<<".hpp\"\n";
  gen_mode=0;
  gen_code_line(fout,code,0,0);
  fout<<"\n";
  fout<<vout.str();
  vout.clear();
  fout<<"\n";
  if(using_list.size()==0 && ast_flag==0)
  {
    unsigned cset[8]={0};
    fout<<"#include <map>\nstatic std::map<std::string,int> yyliterals{\n";
    int flg=0;
    for(auto &s:symbols)
    { if(isliteral(s.first))
      { string t=decode_string(s.first.substr(1,s.first.size()-2));
        if(s.second.terminalnumber>0)
        { if(flg) fout<<",\n";
          fout<<"\t{\""<<encode_string(t,0)<<"\","<<s.second.terminalnumber<<"}";
          flg=1;
        }
        else
        { int c=t[0]&0xFF;
          cset[c>>5]|=1<<(c&31);
        }
      }
    }
    fout<<"};\n";
    fout<<"static unsigned yyliteral1[8]={";
    for(int i=0;i<8;++i) {
      fout<<cset[i]<<"u";
      if(i<7) fout<<",";
    }
    fout<<"};\n";
    fout<<"int yyliteral(const std::string&s) {\n"
        "  if(s.length()==0) return 0;\n"
        "  if(s.length()==1)\n"
        "  { int c=s[0]&0xFF;\n"
        "    if(yyliteral1[c>>5]&(1<<(c&31))) return c; else return 1;\n"
        "  }\n"
        "  auto it=yyliterals.find(s);\n"
        "  if(it==yyliterals.end()) return 1;\n"
        "  return it->second;\n"
        "}\n";
  }
  if(yyerror_flag && using_list.size()==0)
  {
    if(locations_flag==2)
    {
      fout<<"void yyerror(YYLTYPE *yyloc, void *scanner, const char* msg) {\n"
            "  std::cerr<<yylex_filename(scanner,yyloc->last.file)<<':'<<yyloc->last.line<<':'<<yyloc->last.column<<\": \";\n"
            "  yyerror(msg);\n"
            "}\n";
    }
    else if(locations_flag==1)
      fout<<"void yyerror(void *scanner, const char* msg) {\n"
            "  std::cerr<<yylex_filename(scanner,-1)<<':'<<yylineno<<\": \";\n"
            "  yyerror(msg);\n"
            "}\n";
    else
      fout<<"void yyerror(void *, const char* msg)\n{ yyerror(msg); }\n";
    fout<<"void yyerror(const std::string& msg)\n"
          "{ std::cerr<<msg<<std::endl;\n"
          "  YYONERROR;\n"
          "}\n";
  }
  if(main_flag)
  {
    fout<<"int yydebug_flag=0;\n"
          "const char* yyinputfile=\"\";\n"
          "int yylex_loop(void *scanner)\n"
          "{ int t;\n"
          "  YYSTYPE yylval;\n";
    if(locations_flag==2)
      fout<<"  YYLTYPE yylloc;\n"
            "  while(t=yylex(&yylval,&yylloc,scanner))\n";
    else  
      fout<<"  while(t=yylex(&yylval,scanner))\n";
    if(lexprint_flag) {
      fout<<"    if(yydebug_flag==1) {\n";
    if(locations_flag==2)
      fout<<"      std::cout<<yylloc.first.line<<':'<<yylloc.first.column<<' '<<yylloc.last.line<<':'<<yylloc.last.column<<' ';\n";
      fout<<"      lexprint(std::cout,t,yylval); std::cout<<std::endl;\n"
            "    }\n";
    }
    else
      fout<<"    ;\n";
    fout<<"  return 0;\n"
          "}\n"
          "int yyparse_file(const char* name)\n"
          "{ void *scanner=nullptr;\n"
          "  FILE *f=nullptr;\n"
          "  yyinputfile=name;\n"
          "#ifdef YYINIT\n"
          "  YYINIT(name);\n"
          "#endif\n"
          "  if(name[0])\n"
          "  { f=fopen(name,\"r\");\n"
          "    if(!f) yyerror(\"Can't open file \"+std::string(name));\n"
          "    yylex_init(&scanner,f,name);\n"
          "  }\n"
          "  else yylex_init(&scanner);\n";
    if(!grmfile_exist && yyparse_flag)
      fout<<"  int res=yylex_loop(scanner);\n";
    else
      fout<<"  int res=(yydebug_flag==1)?yylex_loop(scanner):yyparse(scanner);\n";
    fout<<"  yylex_destroy(scanner);\n"
          "  return res;\n"
          "}\n"
          "int main(int argc, char **argv)\n"
          "{\n"
          "#ifdef YYARGINIT\n"
          "  YYARGINIT(argc,argv);\n"
          "#endif\n"
          "  for(int i=1; i<argc; ++i)\n"
          "    if(argv[i][0]=='-')\n"
          "    { if(argv[i][1]=='d') yydebug_flag=argv[i][2]-'0';\n"
          "    }\n"
          "    else if(yyparse_file(argv[i])) return 1;\n"
          "  if(!yyinputfile[0]) return yyparse_file(\"\"); \n"
          "}\n";
  }
  if(lexprint_flag && using_list.size()==0)
  {
    fout<<"void lexprint(std::ostream &s, int t,YYSTYPE& a) {\n"
          "  if(t==1) s<<\"undef\";\n"
          "  else if(t<256) astprint(s,char(t));\n"
          "  else switch(t) {\n";
    for(auto s:symbols)
    { if(isterminal(s.first) && s.second.terminalnumber)
      {
        fout<<"  case "<<s.second.terminalnumber<<": s<<\"";
        fout<<encode_string(string(1,s.first[0])+encode_string(decode_string(s.first.substr(1,s.first.size()-2)),0)+
              string(1,s.first[0]),0)<<"\";\n";
        if(!empty_type(s.second.tip))
          fout<<"\ts<<\" : \"; astprint(s,a.f"<<union_fields[s.second.tip]<<"_);\n";
        fout<<"\tbreak;\n";
      }
    }
    fout<<"  }\n}\n";
  }
  if(astprint_flag && domains.size()>0)
  {
    fout<<"namespace ast {\n";
    for(auto &d:domains)
    { 
      fout<<"int astprint(std::ostream& s,"<<d.first<<" v, int i, const char* p) {\n"
            "  int r=0;\n  if(!v) s<<\"nullptr\";\n";
      for(auto &n:d.second.nodes)
      {  
        fout<<"  else if(auto _node=dynamic_cast<"<<n<<"_node*>(v)) {\n";
        auto &ni=nodes[n];
        if(ni.types.size()>1)
        {
          fout<<"    print_indent(s,i);\n"
                "    s<<\""<<n<<"(\";\n";
          for(int j=1;j<ni.types.size();++j)
            fout<<"    r+=astprint(s,_node->f"<<j<<"_,i+1,"<<((j<ni.types.size()-1)?"\",\"":"nullptr")<<");\n";
          fout<<"    if(r) print_indent(s,i);\n"
                 "    s<<\")\";\n"
                 "    ++r;\n";
        }
        else
           fout<<"    s<<\""<<n<<"()\";\n";
        fout<<"  }\n";
      }
      fout<<"  if(p) s<<p;\n"
            "  return r;\n"
            "}\n";
    }
    fout<<"}\n";
  }
}
string linked_symbol;
string type_arg(const string &a, List<Gelem> gl, const string &nd, int nn, bool flg=true)
{ string s;
  int i=0;
  linked_symbol.clear();
  if(a.size()==0) return ""s;
  if(a[0]=='\'') return "char"s;
  if(a[0]=='\"') return "std::string"s;
  if(a.size()>1 && a[0]=='$' && isdigit(a[1])) 
  { int na=0;
    i=1;
    while(i<a.size() && isdigit(a[i]))
      na=na*10+(a[i++]-'0');
    if(na<1 || na>gl.size())
      yyerror("Reference "s+a+" to unknown element");
    Gelem e=gl[na-1];
    { auto &_match1=e;
if(auto _node1=dynamic_cast<trmelem_node *>(_match1)) {
  auto &s=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 3335 "caio.caio"
                          
         string idn=normalize_terminal(s);
         if(empty_type(symbols[idn].tip))
            yyerror("Terminal "s+string(s)+" don't have a type"s);
         return symbols[idn].tip;
    }
else if(auto _node1=dynamic_cast<symelem_node *>(_match1)) {
  auto &s=_node1->f1_;
  auto &altid=_node1->f2_;

	#line 3340 "caio.caio"
                          
         auto &sym=symbols[s];
         if(!flg)
         {
           sym.node_link.push_back(make_pair(nd,-nn));
           return sym.tip;
         }
         else if(nn>0) 
           sym.node_link.push_back(make_pair(nd,nn));
         else if(s!=nd)
         {
           linked_symbol=s;
           symbols[nd].symbol_link.push_back(make_pair(s,-nn));
           sym.symbol_link.push_back(make_pair(nd,nn));
         }
    }
}

	#line 3355 "caio.caio"
    
    return ""s;
  }
  while(i<a.size() && (isdigit(a[i]) || a[i]=='\''))
    s+=a[i++];
  if(s.size()>0)
  { s=a.substr(i,1);
    if(s=="."s || s=="e"s || s=="E"s) return "double"s;
    if(a.substr(i,2)=="ll"s) return "int64_t"s;
    if(s=="l"s) return "long"s;
    return "int"s;
  }
  s.clear();
  i=0;
  while(i<a.size() && (isalnum(a[i]) || a[i]=='_' || a[i]==':'))
    s+=a[i++];
  if(is_builtin_type(s) || is_domain(s)) return s;
  if(s=="yytext"s || s=="text"s || s=="YYText"s) 
  { if(i<a.size() && a[i]=='[') return "char"s;
    return "std::string"s;
  }
  if(s=="nullptr"s) return "?"s;
  if(i<a.size() && a[i]=='(')
  {
    if(s=="cons"s)
    { 
      s=type_arg(a.substr(i+1),gl,nd,nn,0);
      if(s!=""s && !is_list_type(s))
        return "List<"s+s+">"s;
      return s;
    }
    auto it=nodes.find(s);
    if(it==nodes.end()) return ""s;
    return it->second.types[0];
  }
  auto it=consts.find(s);
  if(it!=consts.end()) return it->second.tip;
  return ""s;  
}
void assign_type(string &t, const string &nt, const string &id)
{ if(yydebug_flag==3)
    cout<<id<<": "<<t<<" <- "<<nt<<"\n";
  if(nt==""s) return;
  if(nt=="?"s)
  { if(t==""s)
      t=nt;
    else if(t.back()!='?' && is_builtin_type(t))
      t+='?';
    return;
  }
  if(t=="")
    t=nt;
  else if(t=="?"s)
  { if(is_builtin_type(nt))
      t=nt+"?"s;
    else
      t=nt;
  }
  else if(t!=nt)
  { string t1=t,nt1=nt;
    if(t1.back()=='?') t1.pop_back();
    if(nt1.back()=='?') nt1.pop_back();
    if(t1!=nt1)
      yyerror("Types attributes "s+id+" is different: "s+t+" <- "s+nt);
    if(nt.back()=='?')
      t=nt;
  }
}
static int ref_assigned=0;
void calc_types(List<Code> code, int flg)
{ for(auto c:code)
  { auto &_match1=c;
if(auto _node1=dynamic_cast<lexem_node *>(_match1)) {
  auto &t=_node1->f1_;

	#line 3427 "caio.caio"
                  
      if(t=="$$"s)
        ref_assigned=1;
    }
else if(auto _node1=dynamic_cast<pcode_node *>(_match1)) {
  auto &cc=_node1->f1_;

	#line 3430 "caio.caio"
                   
      calc_types(cc,flg);
    }
else if(auto _node1=dynamic_cast<token_node *>(_match1)) {
  auto &val=_node1->f1_;

	#line 3432 "caio.caio"
                    
      if(flg)
      {
        string idn=normalize_terminal(val);
        string &tip=symbols[idn].tip;
        if(ref_assigned)
        {
          if(empty_type(tip))
            assign_type(tip,default_tip,idn);
        }
        else
        {
          assign_type(tip,"?"s,idn);
        }
      }
  }
}

	#line 3447 "caio.caio"
  
}
void calc_types(List<Lrule> lrules)
{ for(auto r:lrules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<lexrule_node *>(_match1)) {
  auto &st=_node1->f1_;
  auto &re=_node1->f2_;
  auto &act=_node1->f3_;

	#line 3452 "caio.caio"
                              
      { auto &_match2=act;
if(auto _node2=dynamic_cast<lterm_node *>(_match2)) {
  auto &id=_node2->f1_;
  auto &t=_node2->f2_;

	#line 3454 "caio.caio"
                         
          if(id && t)
          { string idn=normalize_terminal(id);
            string &tip=symbols[idn].tip;
            if(empty_type(tip))
              assign_type(tip,default_tip,idn);
            if(is_domain(tip)) 
            {
              { auto &_match3=t;
if(auto _node3=dynamic_cast<tnode_node *>(_match3)) {
  auto &idt=_node3->f1_;
  auto &args=_node3->f2_;

	#line 3463 "caio.caio"
                                   
                if(nodes.find(idt)==nodes.end())
                  nodes[idt]=nodeinfo(args.size()+1);
                auto &n=nodes[idt];
                if(args.size()!=n.types.size()-1)
                  yyerror("Wrong number of node "s+idt+" arguments"s);
                assign_type(n.types[0],tip,idt+"(0)"s);
                domains[tip].nodes.insert(idt);
                int nn=1;
                for(auto a:args)
                { assign_type(n.types[nn],type_arg(a,nullptr,idt,nn),idt+"("s+to_string(nn)+")"s);
                  ++nn;
                }
              }
}

	#line 3476 "caio.caio"
              
            }
            else
            { 
              { auto &_match3=t;
if(auto _node3=dynamic_cast<tnode_node *>(_match3)) {
  auto &idt=_node3->f1_;
  auto &args=_node3->f2_;

	#line 3481 "caio.caio"
                                   
                if(is_builtin_type(idt))
                  assign_type(tip,idt,id);
              }
else if(auto _node3=dynamic_cast<snode_node *>(_match3)) {
  auto &str=_node3->f1_;

	#line 3484 "caio.caio"
                              
                assign_type(tip,type_arg(str,nullptr,id,0),id);
              }
}

	#line 3486 "caio.caio"
              
            }
          }
       }
else if(auto _node2=dynamic_cast<lcode_node *>(_match2)) {
  auto &cc=_node2->f1_;

	#line 3489 "caio.caio"
                      
         ref_assigned=0;
         calc_types(cc,1);
      }
}

	#line 3492 "caio.caio"
      
    }
}

	#line 3493 "caio.caio"
    
  }
}
void calc_types(List<Grule> grules)
{
  set<string> new_syms;
  for(auto r:grules)
  { { auto &_match1=r;
if(auto _node1=dynamic_cast<grmrule_node *>(_match1)) {
  auto &id=_node1->f1_;
  auto &body=_node1->f2_;

	#line 3501 "caio.caio"
                           
      if(symbols[id].defrule!=nullptr)
        yyerror("Redefined symbol "s+id);
      auto &sym=symbols[id];
      sym.defrule=r;
      if(!empty_type(sym.tip))
      { new_syms.insert(id);
      }                 
      for(auto x:body)
      { { auto &_match2=x;
if(auto _node2=dynamic_cast<xrule_node *>(_match2)) {
  auto &els=_node2->f1_;
  auto &act=_node2->f2_;

	#line 3511 "caio.caio"
                             
          { { auto &_match3=act;
if(auto _node3=dynamic_cast<gterm_node *>(_match3)) {
  auto &t=_node3->f1_;

	#line 3513 "caio.caio"
                          
              { auto &_match4=t;
if(auto _node4=dynamic_cast<tnode_node *>(_match4)) {
  auto &idt=_node4->f1_;
  auto &args=_node4->f2_;

	#line 3515 "caio.caio"
                                    
                  string tip;
                  if(idt=="cons"s)
                  { if(args.size()==1)
                    { tip=type_arg(args[0],els,id,-1);
                      if(!empty_type(tip))
                        if(!is_list_type(tip))
                          tip=list_of_type(tip);
                    }
                    else {
                      if(args.size()!=2)
                        yyerror("Number of cons' arguments should be 1 or 2"s);
                      string link1,link2,tip1,tip2;
                      tip1=type_arg(args[0],els,id,-1);
                      link1=linked_symbol;
                      tip2=type_arg(args[1],els,id,-1);
                      link2=linked_symbol;
                      if(!empty_type(tip2) && !empty_type(tip1) && !is_list_type(tip1) && !is_list_type(tip2))
                      { 
                        yyerror("Using cons for "s+tip1+" and "s+tip2);
                      }
                      if(is_list_type(tip1) && is_list_type(tip2))
                      { if(type_of_list(tip1)!=type_of_list(tip2))
                          yyerror("Using cons() for "s+tip1+" and "s+tip2);
                        tip=tip1;
                      }
                      else
                      { if(empty_type(tip1) || is_list_type(tip1))
                        { swap(tip1,tip2);
                          swap(link1,link2);
                        }
                        if(!empty_type(tip1))
                        { 
                          tip=list_of_type(tip1);
                          if(!empty_type(tip2))
                          {
                            if(tip!=tip2)
                              yyerror("Using cons() for "s+tip1+" and "s+tip2);
                          }
                          if(link2!=""s)
                            assign_type(symbols[link2].tip,tip,link2);
                        }
                        else if(!empty_type(tip2))
                        { if(!is_list_type(tip2))
                            yyerror("Using cons() for "s+tip1+" and "s+tip2);
                          tip=tip2;
                        }
                      }
                      if(link1!=""s && link2!=""s && link1!=link2)
                      {
                        symbols[link1].symbol_link.push_back(make_pair(link2,-2));
                        symbols[link2].symbol_link.push_back(make_pair(link1,-2));
                      }
                    }
                    assign_type(sym.tip,tip,id);
                    if(!empty_type(tip))
                      new_syms.insert(id);
                  }
                  else if(is_builtin_type(idt))
                  { assign_type(sym.tip,idt,id);
                    new_syms.insert(id);
                  }
                  else
                  { 
                    if(nodes.find(idt)==nodes.end())
                      nodes[idt]=nodeinfo(args.size()+1);
                    auto &n=nodes[idt];
                    if(args.size()!=n.types.size()-1)
                      yyerror("Wrong number of node "s+idt+" arguments"s);
                    int nn=1;
                    for(auto a:args)
                    {
                      assign_type(n.types[nn],type_arg(a,els,idt,nn),idt+"("s+to_string(nn)+")"s);
                      ++nn;
                    }
                    sym.node_link.push_back(make_pair(idt,0));
                    n.symbol_link.push_back(id);
                  }
              }
else if(auto _node4=dynamic_cast<snode_node *>(_match4)) {
  auto &str=_node4->f1_;

	#line 3593 "caio.caio"
                              
                  string tip=type_arg(str,els,id,0);
                  assign_type(sym.tip,tip,id);
                  if(!empty_type(tip))
                    new_syms.insert(id);
              }
}

	#line 3598 "caio.caio"
              
            }
else if(auto _node3=dynamic_cast<gcode_node *>(_match3)) {
  auto &cc=_node3->f1_;

	#line 3599 "caio.caio"
                           
               if(empty_type(sym.tip)) 
               {
                 ref_assigned=0;
                 calc_types(cc,0);
                 if(ref_assigned)
                 { 
                   assign_type(sym.tip,default_tip,id);
                   new_syms.insert(id);
                 }
                 else
                   sym.tip="?"s;
               }
               else
               { ref_assigned=0;
                 calc_types(cc,0);
                 if(!ref_assigned)
                 { assign_type(sym.tip,"?"s,id);
                 }
               }
            }
else if(auto _node3=dynamic_cast<gempty_node *>(_match3)) {

	#line 3619 "caio.caio"
                          
               { assign_type(sym.tip,"?"s,id);
               }
            }
}

	#line 3622 "caio.caio"
            
          }
        }
}

	#line 3624 "caio.caio"
        
      }
    }
}

	#line 3626 "caio.caio"
    
  }
  set<string> old_syms;
  int step=0;
  while(new_syms.size()>0)
  { 
    if(yydebug_flag==3)
    { ++step;
      cout<<"Step "<<step<<":\n";
      for(auto &s:new_syms)
      { auto &sym=symbols[s];
        cout<<s<<": "<<sym.tip<<"\n";
      }
    }
    old_syms=new_syms;
    new_syms.clear();
    for(auto &s:old_syms)
    { auto &sym=symbols[s];
      string tip=sym.tip;
      if(yydebug_flag==3)
        cout<<"@ "<<s<<" "<<tip<<"\n";
      for(auto &x:sym.node_link)
      { string t=tip;
        int a=x.second;
        if(a<0) {
          a=-a;
          if(!is_list_type(t))
            t=list_of_type(t);
        }
        assign_type(nodes[x.first].types[a],t,x.first+"("s+to_string(a)+")"s);
        if(a==0)
        {
          domains[tip].nodes.insert(x.first);
          for(auto &sn:nodes[x.first].symbol_link)
          { if(empty_type(symbols[sn].tip))
              new_syms.insert(sn);
            assign_type(symbols[sn].tip,tip,sn);
          }
        }
      }
      for(auto &x:sym.symbol_link)
      { bool flg=empty_type(symbols[x.first].tip);
        if(x.second==0)
          assign_type(symbols[x.first].tip,tip,x.first);
        else if(x.second==-1)
        { 
          assign_type(symbols[x.first].tip,is_list_type(tip)?tip:list_of_type(tip),x.first);
        }
        else if(x.second==-2)
        { if(!is_list_type(tip))
            assign_type(symbols[x.first].tip,list_of_type(tip),x.first);
          else
            flg=0;
        }
        else
          flg=0;
        if(flg) 
          new_syms.insert(x.first);
      }
    }
  }
  string bad_node="";
  if(yydebug_flag==3)
    cout<<"Assigned types:\n";
  for(auto &n:nodes)
  { for(auto &t:n.second.types)
      if(empty_type(t))
      { if(bad_node==""s) bad_node=n.first;
      }
      else
      { if(t.back()=='?') usevalue_flag=1;
        if(t=="std::string?"s) usestring_flag=1;
        if(t.substr(0,5)=="List<"s) uselist_flag=1;
      }
      
    if(yydebug_flag==3)
    {
      cout<<n.first<<"(";
      if(n.second.types.size()>1)
      { cout<<n.second.types[1];
        for(int i=2;i<n.second.types.size();++i)
           cout<<", "<<n.second.types[i];
      }  
      cout<<"): "<<n.second.types[0]<<"\n";
    }
  }
  for(auto &s:symbols)
  {
    if(yydebug_flag==3)
    {
      cout<<s.first<<": "<<s.second.tip<<"\n";
    }
    if(!empty_type(s.second.tip))
    { 
      string t=s.second.tip;

      if(t.back()=='?') usevalue_flag=1;
      if(t.substr(0,11)=="std::string"s) usestring_flag=1;
      if(t.substr(0,5)=="List<"s) uselist_flag=1;

      if(union_fields.find(t)==union_fields.end())
      { int k=union_fields.size()+1;
        union_fields[t]=k;
      }
    }
  }
  if(yydebug_flag==3)
  { cout<<"Union:\n";
    for(auto un:union_fields)
      cout<<un.first<<" "<<un.second<<"\n";
  }
  if(bad_node!=""s)
    yyerror("Type of "s+bad_node+" is undefined"s);
}
void yyinterpret(Program prg)
{ { auto &_match1=prg;
if(auto _node1=dynamic_cast<prog_node *>(_match1)) {
  auto &decls=_node1->f1_;
  auto &lrules=_node1->f2_;
  auto &grules=_node1->f3_;
  auto &code=_node1->f4_;

	#line 3742 "caio.caio"
                                        
    {
      collect_defsymbols(grules);
      check_undefsymbols(grules);
      collect_states(lrules);

      collect_decls(decls);

      replace_refs(grules);

      collect_terminals(lrules);
      collect_terminals(grules);
      collect_terminals(code);

      new_rules=nullptr;

      calc_types(lrules);
      setup_default(grules);
      if(opers.size())
      { reorder_rules(grules);
        grules=cons(grules,new_rules);
        new_rules=nullptr;
      }
      split_rules(grules);
      grules=cons(grules,new_rules);
      if(yydebug_flag==4) { astprint(cout,grules); return; }

      calc_types(grules);
      gen_altnames();
      if(yydebug_flag) return;

      
      ofstream fout;
      if(lexdefault_flag==-1)
      {
        if(grules) lexdefault_flag=3;
        else lexdefault_flag=1;
      }
      if(yylex_flag)
      { lexfile_exist=1;
        fout.open(filepath+filename+".lex"s);
        create_lexfile(fout,filename,lrules);
        fout.close();
      }
      if(grules && yyparse_flag)
      { grmfile_exist=1;
        fout.open(filepath+filename+".grm"s);
        create_grmfile(fout,filename,grules);
        fout.close();
      }
      fout.open(filepath+filename+".cpp"s);
      create_cppfile(fout,filename,code);
      fout.close();
      fout.open(filepath+filename+".hpp"s);
      create_hfile(fout,filename);
      fout.close();
    }
  }
}

	#line 3799 "caio.caio"
  
}


#include <map>
static std::map<std::string,int> yyliterals{
	{"%code",1001},
	{"%operator",1002},
	{"%option",1003},
	{"%type",1004},
	{"%using",1005},
	{"%{",1006},
	{"default",1007},
	{"match",1008},
	{"rule",1009},
	{"visit",1010},
	{"visitor",1011}};
static unsigned yyliteral1[8]={1024u,4227874560u,671088640u,939524096u,0u,0u,0u,0u};
int yyliteral(const std::string&s) {
  if(s.length()==0) return 0;
  if(s.length()==1)
  { int c=s[0]&0xFF;
    if(yyliteral1[c>>5]&(1<<(c&31))) return c; else return 1;
  }
  auto it=yyliterals.find(s);
  if(it==yyliterals.end()) return 1;
  return it->second;
}
void yyerror(YYLTYPE *yyloc, void *scanner, const char* msg) {
  std::cerr<<yylex_filename(scanner,yyloc->last.file)<<':'<<yyloc->last.line<<':'<<yyloc->last.column<<": ";
  yyerror(msg);
}
void yyerror(const std::string& msg)
{ std::cerr<<msg<<std::endl;
  YYONERROR;
}
int yydebug_flag=0;
const char* yyinputfile="";
int yylex_loop(void *scanner)
{ int t;
  YYSTYPE yylval;
  YYLTYPE yylloc;
  while(t=yylex(&yylval,&yylloc,scanner))
    if(yydebug_flag==1) {
      std::cout<<yylloc.first.line<<':'<<yylloc.first.column<<' '<<yylloc.last.line<<':'<<yylloc.last.column<<' ';
      lexprint(std::cout,t,yylval); std::cout<<std::endl;
    }
  return 0;
}
int yyparse_file(const char* name)
{ void *scanner=nullptr;
  FILE *f=nullptr;
  yyinputfile=name;
#ifdef YYINIT
  YYINIT(name);
#endif
  if(name[0])
  { f=fopen(name,"r");
    if(!f) yyerror("Can't open file "+std::string(name));
    yylex_init(&scanner,f,name);
  }
  else yylex_init(&scanner);
  int res=(yydebug_flag==1)?yylex_loop(scanner):yyparse(scanner);
  yylex_destroy(scanner);
  return res;
}
int main(int argc, char **argv)
{
#ifdef YYARGINIT
  YYARGINIT(argc,argv);
#endif
  for(int i=1; i<argc; ++i)
    if(argv[i][0]=='-')
    { if(argv[i][1]=='d') yydebug_flag=argv[i][2]-'0';
    }
    else if(yyparse_file(argv[i])) return 1;
  if(!yyinputfile[0]) return yyparse_file(""); 
}
void lexprint(std::ostream &s, int t,YYSTYPE& a) {
  if(t==1) s<<"undef";
  else if(t<256) astprint(s,char(t));
  else switch(t) {
  case 1001: s<<"\"%code\"";
	break;
  case 1002: s<<"\"%operator\"";
	break;
  case 1003: s<<"\"%option\"";
	break;
  case 1004: s<<"\"%type\"";
	break;
  case 1005: s<<"\"%using\"";
	break;
  case 1006: s<<"\"%{\"";
	break;
  case 1007: s<<"\"default\"";
	break;
  case 1008: s<<"\"match\"";
	break;
  case 1009: s<<"\"rule\"";
	break;
  case 1010: s<<"\"visit\"";
	break;
  case 1011: s<<"\"visitor\"";
	break;
  case 1012: s<<"?%%code?";
	break;
  case 1013: s<<"?%%grm?";
	break;
  case 1014: s<<"?%%lex?";
	break;
  case 1015: s<<"?const?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1016: s<<"?id?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1017: s<<"?lexem?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1018: s<<"?number?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1019: s<<"?re?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1020: s<<"?ref?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1021: s<<"?spaces?";
	s<<" : "; astprint(s,a.f1_);
	break;
  case 1022: s<<"?terminal?";
	s<<" : "; astprint(s,a.f1_);
	break;
  }
}
namespace ast {
int astprint(std::ostream& s,Code v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<lexem_node*>(v)) {
    print_indent(s,i);
    s<<"lexem(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<mcode_node*>(v)) {
    print_indent(s,i);
    s<<"mcode(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<pcode_node*>(v)) {
    print_indent(s,i);
    s<<"pcode(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<token_node*>(v)) {
    print_indent(s,i);
    s<<"token(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<vcode_node*>(v)) {
    print_indent(s,i);
    s<<"vcode(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,",");
    r+=astprint(s,_node->f3_,i+1,",");
    r+=astprint(s,_node->f4_,i+1,",");
    r+=astprint(s,_node->f5_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Decl v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<declcode_node*>(v)) {
    print_indent(s,i);
    s<<"declcode(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<decloper_node*>(v)) {
    print_indent(s,i);
    s<<"decloper(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<declre_node*>(v)) {
    print_indent(s,i);
    s<<"declre(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<decltypes_node*>(v)) {
    print_indent(s,i);
    s<<"decltypes(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Gaction v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<gcode_node*>(v)) {
    print_indent(s,i);
    s<<"gcode(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<gempty_node*>(v)) {
    s<<"gempty()";
  }
  else if(auto _node=dynamic_cast<gterm_node*>(v)) {
    print_indent(s,i);
    s<<"gterm(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Gelem v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<optelem_node*>(v)) {
    print_indent(s,i);
    s<<"optelem(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<repelem0_node*>(v)) {
    print_indent(s,i);
    s<<"repelem0(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<repelem1_node*>(v)) {
    print_indent(s,i);
    s<<"repelem1(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<symelem_node*>(v)) {
    print_indent(s,i);
    s<<"symelem(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<trmelem_node*>(v)) {
    print_indent(s,i);
    s<<"trmelem(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<varelem_node*>(v)) {
    print_indent(s,i);
    s<<"varelem(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Grule v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<grmrule_node*>(v)) {
    print_indent(s,i);
    s<<"grmrule(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Laction v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<lcode_node*>(v)) {
    print_indent(s,i);
    s<<"lcode(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<lnext_node*>(v)) {
    s<<"lnext()";
  }
  else if(auto _node=dynamic_cast<lskip_node*>(v)) {
    s<<"lskip()";
  }
  else if(auto _node=dynamic_cast<lterm_node*>(v)) {
    print_indent(s,i);
    s<<"lterm(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Lrule v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<lexinit_node*>(v)) {
    print_indent(s,i);
    s<<"lexinit(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<lexrule_node*>(v)) {
    print_indent(s,i);
    s<<"lexrule(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,",");
    r+=astprint(s,_node->f3_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Mrule v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<mrule_node*>(v)) {
    print_indent(s,i);
    s<<"mrule(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Node v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<node1_node*>(v)) {
    print_indent(s,i);
    s<<"node1(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<node2_node*>(v)) {
    print_indent(s,i);
    s<<"node2(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Program v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<prog_node*>(v)) {
    print_indent(s,i);
    s<<"prog(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,",");
    r+=astprint(s,_node->f3_,i+1,",");
    r+=astprint(s,_node->f4_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Symbol v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<ident_node*>(v)) {
    print_indent(s,i);
    s<<"ident(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<node_node*>(v)) {
    print_indent(s,i);
    s<<"node(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<terminal_node*>(v)) {
    print_indent(s,i);
    s<<"terminal(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Term v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<snode_node*>(v)) {
    print_indent(s,i);
    s<<"snode(";
    r+=astprint(s,_node->f1_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  else if(auto _node=dynamic_cast<tnode_node*>(v)) {
    print_indent(s,i);
    s<<"tnode(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Vrule v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<vrule_node*>(v)) {
    print_indent(s,i);
    s<<"vrule(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
int astprint(std::ostream& s,Xrule v, int i, const char* p) {
  int r=0;
  if(!v) s<<"nullptr";
  else if(auto _node=dynamic_cast<xrule_node*>(v)) {
    print_indent(s,i);
    s<<"xrule(";
    r+=astprint(s,_node->f1_,i+1,",");
    r+=astprint(s,_node->f2_,i+1,nullptr);
    if(r) print_indent(s,i);
    s<<")";
    ++r;
  }
  if(p) s<<p;
  return r;
}
}
