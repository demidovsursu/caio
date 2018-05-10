#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <cctype>
#include "caio/asttypes.h"
using namespace ast;
using namespace std;
typedef Value<std::string> sVal;
with domains;
#include "caio/astprint.h"

int bnf_flag=1;
int case_flag=0;
int inter_flag=0;
int main_flag=1;
int locations_flag=0;
int literal_flag=1;
int yywrap_flag=1;
int matcherr_flag=1;
int astprint_flag=1;
int lexprint_flag=0;
int yyerror_flag=1;
int expect_flag=-1;

int gen_mode=0;
int return_field=0;

int symbol_uid=0;
int terminal_uid=1000;

struct symbolinfo {
  string altname;
  int generated;
  int terminalnumber;
  string tip;
  Grule defrule;
  vector<pair<string,int>> node_link;
  vector<pair<string,int>> symbol_link;
  symbolinfo():altname(""s),generated(0),terminalnumber(0),tip(""),defrule(nullptr){}
};
struct constinfo {
  string tip;
  constinfo():tip(""){}
};
struct nodeinfo {
  vector<string> types;
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
map<string,symbolinfo> symbols;
map<string,constinfo> consts;
map<string,domaininfo> domains;
map<string,nodeinfo> nodes;
vector<operinfo> opers;
set<string> defined_symbols;
set<string> symbol_names;
set<string> lex_states;
map<string,int> union_fields;
ostringstream vout;
void MatchError(const char *fn,int line)
{ 
}
extern void yyerror(const char *msg);
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
   else if(o=="yywrap"s)
     yywrap_flag=0;
   else if(o=="noyywrap"s)
     yywrap_flag=1;
   else if(o=="matcherr"s)
     matcherr_flag=1;
   else if(o=="nomatcherr"s)
     matcherr_flag=0;
   else if(o=="astprint"s)
     astprint_flag=1;
   else if(o=="noastprint"s)
     astprint_flag=0;
   else if(o=="yyerror"s)
     yyerror_flag=0;
   else if(o=="noyyerror"s)
     yyerror_flag=1;
   else if(o.substr(0,6)=="expect"s)
     expect_flag=stoi(o.substr(6));
}
set<string> builtin_types={"int"s,"string"s,"long"s,"double"s,"int64_t"s,"char"s};
set<string> big_builtin_types={"string"s};
bool is_pointer_type(const string &t)
{
  if(t[t.size()-1]=='*') return 1;
  return 0;
}
bool is_builtin_type(const string &t)
{ 
  if(builtin_types.find(t)!=builtin_types.end()) return 1;
  return 0;
}
bool is_big_builtin_type(const string &t)
{ 
  if(big_builtin_types.find(t)!=big_builtin_types.end()) return 1;
  return 0;
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
map<char,string> cyr_lat{
{'а',"a"},{'б',"b"},{'в',"v"},{'г',"g"},{'д',"d"},{'е',"e"},{'ё',"yo"},{'ж',"zh"},
{'з',"z"},{'и',"i"},{'й',"y"},{'к',"k"},{'л',"l"},{'м',"m"},{'н',"n"},{'о',"o"},
{'п',"p"},{'р',"r"},{'с',"s"},{'т',"t"},{'у',"u"},{'ф',"f"},{'х',"kh"},{'ц',"ts"},
{'ч',"ch"},{'ш',"sh"},{'щ',"tsh"},{'ь',"j"},{'ы',"iq"},{'ъ',"q"},{'э',"eq"},{'ю',"yu"},{'я',"ya"},
{'А',"A"},{'Б',"B"},{'В',"V"},{'Г',"G"},{'Д',"D"},{'Е',"E"},{'Ё',"Yo"},{'Ж',"Zh"},
{'З',"Z"},{'И',"I"},{'Й',"Y"},{'К',"K"},{'Л',"L"},{'М',"M"},{'Н',"N"},{'О',"O"},
{'П',"P"},{'Р',"R"},{'С',"S"},{'Т',"T"},{'У',"U"},{'Ф',"F"},{'Х',"Kh"},{'Ц',"Ts"},
{'Ч',"Ch"},{'Ш',"Sh"},{'Щ',"Tsh"},{'Ь',"J"},{'Ы',"Iq"},{'Ъ',"Q"},{'Э',"Eq"},{'Ю',"Yu"},{'Я',"Ya"},
{'-',"_"}
};

string encode_symbol(const string &s)
{ string r;
  for(auto c:s)
  { auto it=cyr_lat.find(c);
    if(it==cyr_lat.end())
       r+=c;
     else
       r+=it->second;
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
    return "Value<"s+t.substr(0,t.size()-1)+">"s;
  if(is_big_builtin_type(t) && cf==1) 
    return "const "s+t+"&";
  return t;
}
void gen_coderef(ostream& fout, const string &t, int mlevel, int limit)
{ if(t=="$$"s)
  {
    if(gen_mode==0 && mlevel==0)
      yyerror("Can't use $$ without rule");
    else if(gen_mode==0)
      fout<<"(*_node"<<mlevel<<")";
    else if(gen_mode==1)
      fout<<"yylval.f"<<return_field<<"_";
    else
      fout<<t;
  }
  else if(t.size()>=2 && t[0]=='$' && t[1]>='1' && t[1]<='9')
  { int n=stoi(t.substr(1));
    if(n<1 || n>limit)
      yyerror((t+" don't exist"s).c_str());
    if(gen_mode==0)
      fout<<"_node"<<mlevel<<"->f"<<t.substr(1)<<"_";
    else
      fout<<t;
  }
  else
    fout<<t;
}
void gen_code(ostream& fout, List<Code> code, int mlevel,int limit)
{ for(auto c:code)
  match c 
  { rule lexem(t): 
      gen_coderef(fout,t,mlevel,limit);
    rule pcode(cc):
      fout<<"{";
      gen_code(fout,cc,mlevel,limit);
      fout<<"}";
    rule mcode(cc,rules):
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
          match r {
            rule mrule(m, co):
            { int nlimit=0,mtip=0;
              List<string> a(nullptr);
              string idn;
              match m {
                rule node2(id,args):
                  { idn=string(id);
                    a=args;
                  }
                rule node1(id):
                  { mtip=1;
                    idn=string(id);
                  }
              }
              if(idn=="nullptr"s)
              { if(flg) yyerror("rule nullptr should be first in match");
                nlimit=0;
              }
              else if(idn=="default"s)
              { dflt=1;
                nlimit=0;
              }
              else if(dflt)
                yyerror("No rule allowed after rule default");
              else
              {
                auto it=nodes.find(idn);
                if(it==nodes.end())
                  yyerror(("Node "s+idn+" don't exist"s).c_str());
                if(mtip==0) 
                { int n=0;
                  for(auto x:a) ++n;
                  if(n!=it->second.types.size()-1)
                    yyerror(("Node "s+idn+"' args can't matched"s).c_str());
                  nlimit=0;
                }
                else
                  nlimit=it->second.types.size()-1;
              }
              if(flg) fout<<"else ";
              if(idn=="nullptr"s)
                fout<<"if(_match==nullptr) {\n";
              else if(idn=="default"s)
                fout<<" {\n";
              else 
                fout<<"if(auto _node"<<(mlevel+1)<<"=dynamic_cast<"<<idn<<"_node *>(_match"<<(mlevel+1)<<")) {\n";
              int n=0;
              for(auto f:a)
              { ++n;
                fout<<"  auto &"<<f<<"=_node"<<(mlevel+1)<<"->f"<<n<<"_;\n";
              }
              gen_code(fout,co,mlevel+1,nlimit);
              fout<<"}\n";
              flg=1;
            }
          }
        }
        fout<<"}\n";
        gen_mode=old_mode;
      }
    rule vcode(id,tip,ret,cc,rules):
      { if(gen_mode!=0 || mlevel>0)
          yyerror("Can't define visitor at this point");
        int old_mode=gen_mode;
        gen_mode=0;
        fout<<"struct "<<id<<"_visitor:"<<tip<<"_Tvisitor<"<<ret<<"> {\n";
        gen_code(fout,cc,mlevel+1,0);
        fout<<"\n";
        for(auto r:rules)
        {          
          match r {
            rule vrule(m, co):
            { int nlimit=0,mtip=0;
              List<string> a(nullptr);
              string idn;
              match m {
                rule node2(idt,args):
                  { idn=string(idt);
                    a=args;
                  }
                rule node1(idt):
                  { mtip=1;
                    idn=string(idt);
                  }
              }
              auto it=nodes.find(idn);
              if(it==nodes.end())
                yyerror(("Node "s+idn+" don't exist"s).c_str());
              if(mtip==0) 
              { int n=0;
                for(auto x:a) ++n;
                if(n!=it->second.types.size()-1)
                  yyerror(("Node "s+idn+"' args can't matched"s).c_str());
                nlimit=0;
              }
              else
                nlimit=it->second.types.size()-1;
              fout<<ret<<" visit("<<idn<<"_node*);\n";
              vout<<ret<<" "<<id<<"_visitor::visit("<<idn<<"_node* _node"<<(mlevel+1)<<") {\n";
              int n=0;
              for(auto f:a)
              { ++n;
                vout<<"  auto &"<<f<<"=_node"<<(mlevel+1)<<"->f"<<n<<"_;\n";
              }
              gen_code(vout,co,mlevel+1,nlimit);
              vout<<"}\n";
            }
          }
        }
        fout<<"} "<<id<<";\n";
        gen_mode=old_mode;
      }
    rule rterm(val):
      { string id=normalize_terminal(val);
        fout<<"return ";
        auto it=symbols.find(id);
        if(it==symbols.end())
          yyerror((id+" isn't used in rules").c_str());
        if(it->second.terminalnumber>0)
          fout<<it->second.terminalnumber<<";\n";
        else 
          fout<<it->second.altname<<";\n";
      }
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
void collect_decls(List<Decl> decls)
{ int prior=0;
  string tip="";
  for(auto d:decls)
  { match d {
    rule decloper(ops):
      prior++; 
      for(auto o:ops)
      { if(isterminal(o))
          opers.push_back(operinfo(normalize_terminal(o),tip,prior));
        else
          tip=o;
      }
    rule decltypes(tip, syms):
      if(is_domain_name(tip)) {
        if(!is_domain(tip))
          domains[tip]=domaininfo();
      }
      for(auto sym:syms)
      { match sym {
        rule terminal(id):
          add_symbol(normalize_terminal(id),tip);
        rule ident(id):
        {
          if(defined_symbols.find(id)!=defined_symbols.end())
            add_symbol(id,tip);
          else
            add_constant(id,tip);
        }
        rule node(id, args):
          if(!is_domain_name(tip))
            yyerror(("Type of node can't assign to "s+tip).c_str());
          if(nodes.find(id)!=nodes.end())
            yyerror(("Node "s+id+" is assigned to domain "s+nodes[id].types[0]).c_str());
          auto &v=nodes[id];
          v.types.push_back(tip);
          for(auto &t:args)
          { if(t.back()=='?')
              if(!is_builtin_type(t.substr(0,t.size()-1)))
                yyerror(("Wrong type "s+t).c_str());
            v.types.push_back(t);
          }
          domains[tip].nodes.insert(id);
        }
      }
    rule declcode(dest,cc):
      if(!dest || dest=="h"s)
        hcode=cons(hcode,cc);
      else if(dest=="grm"s)
        grmcode=cons(grmcode,cc);
      else if(dest=="lex"s)
        lexcode=cons(lexcode,cc);
    }
  }
}
void collect_terminals(List<Lrule> rules)
{ for(auto r:rules)
  {
    match r {
    rule lexrule(sts, re, act):
       match act {
       rule lterm(id,t):
          if(id)
            add_symbol(normalize_terminal(id),"");
       }
    }
  }
}
void collect_states(List<Lrule> rules)
{ for(auto r:rules)
  {
    match r {
    rule lexrule(sts, re, act):
      for(auto s:sts)
      { if(s!="*"s && s!="INITIAL")
        { lex_states.insert(s);
        }
      }
    }
  }
}
void collect_terminals(List<Xrule> rules)
{ for(auto r:rules)
  { match r {
    rule xrule(elist, a):
      for(auto e:elist)
      { match e {
        rule trmelem(id): 
          add_symbol(normalize_terminal(id),"");
        rule symelem(id): ;
        rule varelem(xl):
          collect_terminals(xl);
        rule optelem(xl):
          collect_terminals(xl);
        rule repelem1(xl):
          collect_terminals(xl);
        rule repelem0(xl):
          collect_terminals(xl);
        }
      }
    }
  }
}
void collect_terminals(List<Grule> rules)
{ for(auto r:rules)
  { match r {
    rule grmrule(id, body):
      collect_terminals(body);
    }
  } 
}
void collect_defsymbols(List<Grule> rules)
{ for(auto r:rules)
  { match r {
    rule grmrule(id, body):
       if(defined_symbols.find(id)!=defined_symbols.end())
         yyerror(("Redefined symbol "s+id).c_str());
       defined_symbols.insert(id);
    }
  }
}
void check_undefsymbols(List<Xrule> rules)
{ for(auto r:rules)
  { match r {
    rule xrule(elist, a):
      for(auto e:elist)
      { match e {
        rule trmelem(id): ;
        rule symelem(id): 
        { if(defined_symbols.find(id)==defined_symbols.end())
            yyerror(("Undefined symbol "s+id).c_str());
        }
        rule varelem(xl):
          check_undefsymbols(xl);
        rule optelem(xl):
          check_undefsymbols(xl);
        rule repelem1(xl):
          check_undefsymbols(xl);
        rule repelem0(xl):
          check_undefsymbols(xl);
        }
      }
    }
  }
}
void check_undefsymbols(List<Grule> rules)
{ for(auto r:rules)
  { match r {
    rule grmrule(id, body):
      check_undefsymbols(body);
    }
  }
}
List<Grule> new_rules=nullptr;
string new_symbol()
{ string id;
  do {
    id="g_"s+to_string(++symbol_uid);
  } while(symbol_names.find(id)!=symbol_names.end());
  add_symbol(id,"");
  return id;
}
bool is_symelem(Gelem e, const string &id)
{ bool res=false;
  match e {
    rule symelem(s): if(s==id) res=true;
  }
  return res;
}
int prior_elem(Gelem e, int n)
{
  int res=0;
  match e {
    rule trmelem(s): res=oper_prior(s,n);
  }
  return res;
}
string type_elem(Gelem e, int n)
{
  string res=""s;
  match e {
    rule trmelem(s): res=oper_type(s,n);
  }
  return res;
}
void reorder_body(const string &gid, const string &id, List<Xrule> &rules)
{ int min_prior=100;
  for(auto r:rules)
  { match r {
    rule xrule(elist, a):
      if(elist.size()==3 && is_symelem(elist[0],id) && is_symelem(elist[2],id))
      { int p=prior_elem(elist[1],2);
        if(p==0) yyerror(("Wrong rule for "s+gid).c_str());
        if(min_prior>p) min_prior=p;
      }
      else if(elist.size()==2 && is_symelem(elist[1],id))
      { int p=prior_elem(elist[0],1);
        if(p>0 && min_prior>p) min_prior=p;
        if(p==0 && is_symelem(elist[0],id)) yyerror(("Wrong rule for "s+gid).c_str());
      }
      else if(elist.size()==2 && is_symelem(elist[0],id))
      { int p=prior_elem(elist[1],0);
        if(p>0 && min_prior>p) min_prior=p;
      }
    }
  }
  if(min_prior==100) return;
  // разделить по приоритету
  List<Xrule> rules1=nullptr;
  List<Xrule> rules2=nullptr;
  sVal id1(new_symbol());
  for(auto r:rules)
  { match r {
    rule xrule(elist, a):
      if(elist.size()==3 && is_symelem(elist[0],id) && is_symelem(elist[2],id))
      { int p=prior_elem(elist[1],2);
        if(p>min_prior)
        { elist[0]=symelem(id1); 
          elist[2]=symelem(id1);
          rules2=cons(rules2,r);
        }
        else
        { string t=type_elem(elist[1],2);
          if(t[0]=='x') elist[0]=symelem(id1); 
          if(t[2]=='x') elist[2]=symelem(id1); 
          rules1=cons(rules1,r);
        }
      }
      else if(elist.size()==2 && is_symelem(elist[1],id))
      { int p=prior_elem(elist[0],1);
        if(p==0)
        { rules2=cons(rules2,r);
        }
        else if(p>min_prior)
        { rules2=cons(rules2,r);
          elist[1]=symelem(id1);
        }
        else
        { string t=type_elem(elist[0],1);
          if(t[1]=='x') elist[1]=symelem(id1);
          rules1=cons(rules1,r);
        }
      }
      else if(elist.size()==2 && is_symelem(elist[0],id))
      { int p=prior_elem(elist[1],0);
        if(p==0)
        { rules2=cons(rules2,r);
        }
        else if(p>min_prior)
        { rules2=cons(rules2,r);
          elist[0]=symelem(id1);
        }
        else
        { string t=type_elem(elist[1],0);
          if(t[0]=='x') elist[0]=symelem(id1);
          rules1=cons(rules1,r);
        }
      }
      else
      { rules2=cons(rules2,r);
      }
    }
  }
  if(rules2.size()==0) yyerror(("Wrong rule for "s+gid).c_str());
  rules1=cons(rules1,xrule(cons(symelem(id1)),gterm(snode(sVal("$1")))));
  rules=rules1;
  reorder_body(gid,id1,rules2);
  new_rules=cons(new_rules,grmrule(id1,rules2));
}
void reorder_rules(List<Grule> grules)
{ for(auto r:grules)
  { match r {
    rule grmrule(id, body):
      reorder_body(id,id, body);
    } 
  }
}
bool check_all_gempty(List<Xrule> rules) 
{ bool res=true;
  for(auto r:rules)
  { match r {
    rule xrule(elist, a):
      match a {
      rule gterm(t): res=false;
      rule gcode(cc): res=false;
      }
    }
  }  
  return res;
}
void split_rules(List<Xrule> rules);
void make_rep(int one, List<Xrule> xl, Gelem &e)
{ 
  split_rules(xl);
  sVal id1(new_symbol());
  sVal id2(new_symbol());
  Gaction g1;
  Gaction g2;
  if(check_all_gempty(xl))
  { g1=gempty();
    g2=gempty();
  }
  else
  { if(one) g1=gterm(tnode(sVal("cons"),cons("$1"s)));
    else g1=gempty();
    g2=gterm(tnode(sVal("cons"),List<string>({"$1"s,"$2"s})));
  }
  new_rules=cons(new_rules,grmrule(id2,xl));
  new_rules=cons(new_rules,grmrule(id1,
           cons(cons(xrule(one?cons(symelem(id2)):nullptr,g1)),
           xrule(cons(cons(symelem(id1)),symelem(id2)),g2))));
  e=symelem(id1);
}
void split_rules(List<Xrule> rules)
{ for(auto r:rules)
  { match r {
    rule xrule(elist, a):
      for(auto &e:elist)
      { match e {
        rule varelem(xl):
          split_rules(xl);
          sVal id(new_symbol());
          e=symelem(id);
          new_rules=cons(new_rules,grmrule(id,xl));
        rule optelem(xl):
          split_rules(xl);
          sVal id(new_symbol());
          e=symelem(id);
          new_rules=cons(new_rules,grmrule(id,cons(xrule(nullptr,gempty()),xl)));
        rule repelem1(xl): 
          make_rep(1,xl,e);
        rule repelem0(xl): 
          make_rep(0,xl,e);
        }
      }
    }
  }
}
void split_rules(List<Grule> rules)
{ for(auto r:rules)
  { match r {
    rule grmrule(id, body):
      split_rules(body);
    } 
  }
}
string literal_to_re(const string &s)
{ string t=decode_string(s.substr(1,s.size()-2));
  string r="";
  static string meta="\\\'\"<>{}()*+.?[]/|$^ ";
  for(auto c:t)
  { if(c=='\n') r+="\\n";
    else if(c=='\t') r+="\\t";
    else if(meta.find(c)!=string::npos) { r+='\\'; r+=c; }
    else if((c&0xFF)>=0x7F) { 
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
      if(s.second.tip!=""s)
      { s.second.altname="\""s+encode_string(decode_string(s.first.substr(1,s.first.size()-2)))+"\""s;
        s.second.terminalnumber=++terminal_uid;
      }
    }
    else if(s.first[0]=='?')
    { s.second.altname="\""s+encode_string(s.first,0)+"\""s;
      s.second.terminalnumber=++terminal_uid;
    }
    else if(s.first[0]=='\"')
    { s.second.altname="\""s+encode_string(decode_string(s.first.substr(1,s.first.size()-2)))+"\""s;
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
  match c 
  { rule pcode(cc):
      find_return_field(cc);
    rule rterm(val):
      { string id=normalize_terminal(val);
        auto it=symbols.find(id);
        if(it==symbols.end())
          yyerror((id+" isn't used in rules").c_str());
        int rf=0;
        if(it->second.tip!="")
          rf=union_fields[it->second.tip];
        if(return_field!=0 && rf!=0 && return_field!=rf)
          yyerror("Return terminals with different types");
        if(rf!=0) return_field=rf;
      }
  }
}
void gen_code(ostream& fout,Term t, int limit)
{ match t {
    rule tnode(id, args):
    { int flg=0;
      if(nodes.find(id)!=nodes.end() || id=="cons"s)
        fout<<"ast::";
      fout<<id<<"(";
      for(auto a:args)
      { if(flg) fout<<",";
        gen_coderef(fout,a,0,limit);
        flg=1;
      }
      fout<<")";
    }
    rule snode(str): 
      gen_coderef(fout,str,0,limit);
  }
}
void gen_lexrules(ostream& fout, List<Lrule> rules)
{ for(auto r:rules)
  {
    match r {
    rule lexrule(sts, re, act):
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
      string s=string(re);
      if(s.substr(0,2)=="R\""s)
      { 
        size_t p1=s.find('(');
        size_t p2=s.rfind(')');
        if(p1>=2 && s.size()-p2-1==p1-2 && 
           string(p1-2,s[2])==s.substr(2,p1-2) && string(p1-2,s[2])==s.substr(p2+1,p1-2))
        { s=s.substr(p1,p2-p1);
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
      fout<<"\t";
      match act {
      rule lterm(id,t):
         {
           fout<<"{ ";
           if(id)
           { string nid=normalize_terminal(id);
             if(t)
             { auto it=symbols.find(nid);
               int rf=0;
               if(it->second.tip!=""s)
                 rf=union_fields[it->second.tip];
               if(rf!=0)
               {
                 fout<<"yylval.f"<<to_string(rf)<<"_=";
                 gen_mode=1;
                 gen_code(fout,t,0);
                 fout<<"; ";
               }
               else
                 yyerror(("Type of "s+nid+" is undefined").c_str());
             }
             fout<<"return ";
             auto it=symbols.find(nid);
             if(it->second.terminalnumber>0)
               fout<<it->second.terminalnumber;
             else 
               fout<<it->second.altname;
           }
           else
             fout<<"clear_attr(yylval); return yyliteral(yytext)";
           fout<<"; }\n";
         }
      rule lskip(): fout<<";\n";
      rule lnext(): fout<<"|\n";
      rule lcode(code):
         return_field=0;
         find_return_field(code);
         gen_mode=1;
         gen_code(fout,code,0,0);
      }
    }
  }
}
void create_lexfile(ostream& fout,const string &fn,List<Lrule> lrules)
{
  if(case_flag)
    fout<<"%option case-insensitive\n";
  if(inter_flag)
    fout<<"%option interactive\n";
  if(yywrap_flag)
    fout<<"%option noyywrap\n";
  fout<<"%{\n";
  fout<<"#include \""<<fn<<".h\"\n";
  fout<<"%}\n";
  gen_code(fout,lexcode,0,0);
  if(lex_states.size()>0)
  {
    fout<<"%x";
    for(auto s:lex_states)
      fout<<" "<<s;
    fout<<"\n";
  }
  fout<<"%%\n";
  if(literal_flag)
  { 
    for(auto s:symbols)
    { if(s.first[0]=='\"')
      {
        fout<<literal_to_re(s.first)<<"\t{ clear_attr(yylval); return ";
        if(s.second.terminalnumber>0)
          fout<<s.second.terminalnumber;
        else 
          fout<<s.second.altname;
        fout<<"; }\n";
      }
    }
  }
  gen_lexrules(fout,lrules);
  fout<<"%%\n"
        "void yystart(FILE *f)\n"
        "{ yyrestart(f);\n"
        "}\n";
}
void create_grmfile(ostream& fout,const string &fn, List<Grule> rules)
{
  fout<<"%define parse.error verbose\n";
  if(expect_flag>=0)
    fout<<"%expect"<<expect_flag<<"\n";
  fout<<"%{\n";
  fout<<"#include \""<<fn<<".h\"\n";
  fout<<"%}\n";
  gen_code(fout,grmcode,0,0);
  for(auto s:symbols)
  { if(isterminal(s.first))
    {
      if(s.second.terminalnumber)
      { fout<<"%token ";
        if(s.second.tip!=""s)
          fout<<"<f"<<union_fields[s.second.tip]<<"_> ";
        fout<<"T_"<<s.second.terminalnumber<<" "<<s.second.terminalnumber<<" "<<s.second.altname<<"\n";
      }
    }
    else if(s.second.tip!=""s)
    { fout<<"%type <f"<<union_fields[s.second.tip]<<"_> "<<s.second.altname<<"\n";
    }
  }
  fout<<"%%\n";
  for(auto r:rules)
  {
    match r {
    rule grmrule(id, body):
      fout<<symbols[id].altname<<"\t:";
      int flg=0;
      for(auto x : body)
      { if(flg) fout<<"\t|";
        match x {
        rule xrule(elist, act):
          {
            for(auto &e:elist)
            { match e {
              rule trmelem(str): 
                auto &sym=symbols[normalize_terminal(str)];
                if(sym.terminalnumber>0)
                  fout<<" T_"<<sym.terminalnumber<<" ";
                else
                  fout<<" "<<sym.altname;
              rule symelem(str): 
                fout<<" "<<symbols[str].altname;
              }
            }
            match act {
              rule gempty(): 
                fout<<" { clear_attr(yyval); }\n";
              rule gcode(cc):
                { fout<<"\t{ clear_attr(yyval); ";
                  gen_mode=2;
                  gen_code(fout,cc,0,elist.size());
                  fout<<" }\n";
                }
              rule gterm(t):
                { fout<<"\t{ $$=";
                  gen_mode=2;
                  gen_code(fout,t,elist.size());
                  fout<<"; }\n";
                }
            }
          }
        }
        flg=1;
      }
      fout<<"\t;\n";
    }
  }
  fout<<"%%\n";
}
void create_hfile(ostream& fout,const string &fn)
{ 
  string ufn=fn;
  for(auto &c:ufn)
    c=toupper(c);
  fout<<"#ifndef "<<ufn<<"_H\n";
  fout<<"#define "<<ufn<<"_H 1\n";
  fout<<"#include \"caio/asttypes.h\"\n";
  fout<<"namespace ast {\n";
  for(auto &d:domains)
  { 
    fout<<"struct "<<d.first<<"_visitor;\n";
    fout<<"struct "<<d.first<<"_domain : _domain {\n"
      "\tvirtual void accept("<<d.first<<"_visitor*, void*)=0;\n"
      "};\n";
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
    for(int j=1;j<n.second.types.size();++j) 
    {
      fout<<type_mark(n.second.types[j],1)<<" a"<<j;
      if(j<n.second.types.size()-1)
        fout<<", ";
    }
    if(n.second.types.size()>1)
    {
      fout<<"):";
      for(int j=1;j<n.second.types.size();++j)
      {
        fout<<"f"<<j<<"_(a"<<j<<")";
        if(j<n.second.types.size()-1)
          fout<<", ";
      }
    }
    else
      fout<<")";
    fout<<"{}\n";
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
    fout<<") {\n";
    fout<<"\treturn new "<<n.first<<"_node(";
    for(int j=1;j<n.second.types.size();++j) 
    {
      fout<<"a"<<j;
      if(j<n.second.types.size()-1)
        fout<<", ";
    }
    fout<<");\n"
        <<"}\n";
  }
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
      fout<<"\tvoid visit("<<n<<"_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }\n";
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
  fout<<"}\nusing namespace ast;\n"
        "int yyliteral(const std::string&);\n"
        "int yylex();\n"
        "int yyparse();\n";
  if(locations_flag==1)
    fout<<"extern int yylineno;\n";
  fout<<"void yystart(FILE *);\n"
        "void yyerror(const char*);\n"
        "union YYSTYPE {\n";
  for(auto &f:union_fields)
  { fout<<"  ";
    if(is_builtin_type(f.first))
      fout<<"Value<"<<f.first<<">";
    else
      fout<<f.first;
    fout<<" f"<<f.second<<"_;\n";
  }
  fout<<"};\n";
  fout<<"extern YYSTYPE yylval;\n";
  fout<<"#define YYSTYPE_IS_TRIVIAL 1\n";
  fout<<"#define YYSTYPE_IS_DECLARED 1\n";
  fout<<"void clear_attr(YYSTYPE&);\n";
  gen_mode=0;
  gen_code(fout,hcode,0,0);
  if(astprint_flag)
    fout<<"#include \"caio/astprint.h\"\n";
  fout<<"#endif\n";
}
void create_cppfile(ostream& fout,const string &fn, List<Code> code)
{
  fout<<"#include \""<<fn<<".h\"\n";
  gen_mode=0;
  gen_code(fout,code,0,0);
  fout<<vout.str();
  vout.clear();
  unsigned cset[8]={0};
  fout<<"#include <map>\nstatic std::map<std::string,int> yyliterals{\n";
  int flg=0;
  for(auto &s:symbols)
  { if(isliteral(s.first))
    { string t=decode_string(s.first.substr(1,s.first.size()-2));
      if(s.second.terminalnumber>0)
      { if(flg) fout<<",\n";
        fout<<"\t{\""<<encode_string(t,0)<<"\"s,"<<s.second.terminalnumber<<"}";
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
  if(yyerror_flag)
  {
    fout<<"void yyerror(const char* msg)\n"
          "{\n";
    if(locations_flag==1)
      fout<<"  std::cerr<<\"Line \"<<yylineno<<\": \";\n";
    fout<<"  std::cerr<<msg<<\"\\n\";\n"
          "  exit(1);\n"
          "}\n";
  }
  if(main_flag)
    fout<<"int main(int argc, char **argv)\n"
          "{ if(argc>1)\n"
          "  { FILE *f=fopen(argv[1],\"r\");\n"
          "    if(f) yystart(f);\n"
          "    else yyerror((\"Can't open file \"s+argv[1]).c_str());\n"
          "  }\n"
          "  return yyparse();\n"
          "}\n";
  fout<<
    "void clear_attr(YYSTYPE&v) { memset(&v,0,sizeof(YYSTYPE)); }\n";
  if(astprint_flag)
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
string type_arg(const string &a, List<Gelem> gl, const string &nd, int nn)
{ string s;
  int i=0;
  if(a.size()==0) return ""s;
  if(a[0]=='\'') return "char"s;
  if(a[0]=='\"') return "string"s;
  if(isdigit(a[0]))
  { if(a.find('.')!=string::npos) return "double"s;
    if(a[a.size()-1]=='l')
    { if(a[a.size()-2]) return "int64_t"s;
      return "long"s;
    }
    return "int"s;
  }
  if(a.size()>1 && a[0]=='$' && isdigit(a[1])) 
  { int na=0;
    i=1;
    while(i<a.size() && isdigit(a[i]))
      na=na*10+(a[i++]-'0');
    if(i!=a.size()) return ""s;
    if(na<1 || na>gl.size())
      yyerror(("Reference "s+a+" to unknown element").c_str());
    Gelem e=gl[na-1];
    match e {
    rule trmelem(s):
         string idn=normalize_terminal(s);
         if(symbols[idn].tip==""s)
            yyerror(("Terminal "s+string(s)+" don't have a type"s).c_str());
         return symbols[idn].tip;
    rule symelem(s):
         auto &sym=symbols[s];
         if(nn>0)
           sym.node_link.push_back(make_pair(nd,nn));
         else if(s!=nd)
         {
           symbols[nd].symbol_link.push_back(make_pair<string,int>(s,-nn));
           sym.symbol_link.push_back(make_pair(nd,nn));
         }
    }
    return ""s;
    
  }
  while(i<a.size() && (isalnum(a[i]) || a[i]=='_'))
    s+=a[i++];
  if(is_builtin_type(s)) return s;
  if(s=="yytext"s || s=="text"s || s=="YYText"s) return "string"s;
  if(s=="nullptr"s) return ""s;
  auto it=consts.find(s);
  if(it!=consts.end()) return it->second.tip;
  return ""s;  
}
void assign_type(string &t, const string &nt, const string &id)
{ if(nt==""s) return;
  if(t!=""s)
  { if(!(t.back()=='?' && t.substr(0,t.size()-1)==nt || t==nt))
      yyerror(("Types attributes "s+id+" is different"s).c_str());
  }
  else
  { if(is_builtin_type(nt))
      t=nt+"?"s;
    else
      t=nt;
  }
}
void calc_types(List<Lrule> lrules, List<Grule> grules)
{ for(auto r:lrules)
  { match r {
    rule lexrule(st, re, act):
      match act {
        rule lterm(id,t):
          if(id && t)
          { string idn=normalize_terminal(id);
            string tip=symbols[idn].tip;
            if(tip==""s)
              yyerror(("Type of "s+string(id)+" is undefined, but you set value to attribute"s).c_str());
            if(is_domain(tip)) {
              match t {
                rule tnode(idt,args):
                  if(nodes.find(idt)==nodes.end())
                    nodes[idt]=nodeinfo(args.size()+1);
                  auto &n=nodes[idt];
                  if(args.size()!=n.types.size()-1)
                    yyerror(("Wrong number of node "s+idt+" arguments"s).c_str());
                  assign_type(n.types[0],tip,idt);
                  domains[tip].nodes.insert(idt);
                  int nn=1;
                  for(auto a:args)
                  { assign_type(n.types[nn],type_arg(a,nullptr,idt,nn),idt);
                    ++nn;
                  }
              }
            }
          }
      }
    }
  }
  vector<string> new_syms;
  for(auto r:grules)
  { match r {
    rule grmrule(id, body):
      if(symbols[id].defrule!=nullptr)
        yyerror(("Redefined symbol "s+id).c_str());
      auto &sym=symbols[id];
      sym.defrule=r;
      if(sym.tip==""s || is_domain(sym.tip))
      { if(sym.tip!=""s) 
        { new_syms.push_back(id);
        }                 
        for(auto x:body)
        { match x {
          rule xrule(els, act):
            { match act {
              rule gterm(t):
                match t {
                rule tnode(idt,args): 
                    string tip;
                    if(idt=="cons"s) {
                      if(args.size()==1)
                      { tip=type_arg(args[0],els,id,-1);
                        if(tip!=""s)
                          tip="List<"s+tip+">"s;
                      }
                      else {
                        if(args.size()!=2)
                          yyerror("Number of cons' arguments should be 1 or 2");
                        tip=type_arg(args[0],els,id,-1);
                        string tip2=type_arg(args[1],els,id,-1);
                        if(tip2!=""s)
                        { if(tip!="")
                            yyerror("Wrong using of cons");
                          tip=tip2;
                        }
                        if(tip!=""s)
                          tip="List<"s+tip+">"s;
                      }
                    }
                    else if(is_builtin_type(idt))
                    { if(sym.tip!=""s)
                        yyerror(("Types of "s+id+" and attribute is different").c_str());
                    }
                    else
                    { 
                      if(nodes.find(idt)==nodes.end())
                        nodes[idt]=nodeinfo(args.size()+1);
                      auto &n=nodes[idt];
                      if(args.size()!=n.types.size()-1)
                        yyerror(("Wrong number of node "s+idt+" arguments"s).c_str());
                      int nn=1;
                      for(auto a:args)
                      { assign_type(n.types[nn],type_arg(a,els,idt,nn),idt);
                        ++nn;
                      }
                      sym.node_link.push_back(make_pair<string,int>(idt,0));
                    }
                rule snode(str): 
                    string tip=type_arg(str,els,id,0);
                    if(sym.tip!=""s && tip!=""s && tip!=sym.tip)
                      yyerror(("Types of "s+id+" and attribute is different").c_str());
                    
                }
              }
            }
          }
        }
      }
    }
  }
  vector<string> old_syms;
  while(new_syms.size()>0)
  { old_syms=new_syms;
    new_syms.clear();
    for(auto &s:old_syms)
    { auto &sym=symbols[s];
      string tip=sym.tip;
      for(auto &x:sym.node_link)
      { 
        assign_type(nodes[x.first].types[x.second],tip,x.first);
        if(x.second==0)
          domains[tip].nodes.insert(x.first);
      }
      for(auto &x:sym.symbol_link)
      { 
        if(symbols[x.first].tip==""s) 
          new_syms.push_back(x.first);
        if(x.second==0)
          assign_type(symbols[x.first].tip,tip,x.first);
        else if(x.second==-1)
          assign_type(symbols[x.first].tip,"List<"s+tip+">"s,x.first);
        else if(x.second==1)
        {
          if(tip.substr(0,5)!="List<"s)
            yyerror(("Type of "s+s+" is "+tip+" not List<>"s).c_str());
          assign_type(symbols[x.first].tip,tip.substr(5,tip.size()-6),x.first);
        }
      }
    }
  }
  for(auto &n:nodes)
  { for(auto &t:n.second.types)
      if(t==""s)
        yyerror(("Type of "s+n.first+" is undefined"s).c_str());
/*    cout<<n.first<<"(";
    if(n.second.types.size()>1)
    { cout<<n.second.types[1];
      for(int i=2;i<n.second.types.size();++i)
         cout<<", "<<n.second.types[i];
    }  
    cout<<"): "<<n.second.types[0]<<"\n";
*/
  }
  for(auto &s:symbols)
  {
    // cout<<s.first<<": "<<s.second.tip<<"\n";
    if(s.second.tip!=""s)
    {
      if(union_fields.find(s.second.tip)==union_fields.end())
      { int k=union_fields.size()+1;
        union_fields[s.second.tip]=k;
      }
    }
  }
}
void generate(const string &fn, const string &fp, Program prg)
{ match prg {
    rule prog(decls,lrules,grules,code):
    {
      collect_defsymbols(grules);
      check_undefsymbols(grules);
      collect_states(lrules);

      collect_decls(decls);

      collect_terminals(lrules);
      collect_terminals(grules);

      reorder_rules(grules);
      grules=cons(grules,new_rules);
      new_rules=nullptr;
      split_rules(grules);
      grules=cons(grules,new_rules);

//      print_ast(cout,grules);
      calc_types(lrules,grules);
      gen_altnames();

      
      ofstream fout;
      fout.open(fp+fn+".lex"s);
      create_lexfile(fout,fn,lrules);
      fout.close();
      fout.open(fp+fn+".grm"s);
      create_grmfile(fout,fn,grules);
      fout.close();
      fout.open(fp+fn+".h"s);
      create_hfile(fout,fn);
      fout.close();
      fout.open(fp+fn+".cpp"s);
      create_cppfile(fout,fn,code);
      fout.close();
    }
  }
}
