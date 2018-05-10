#ifndef ASTPRINT_H
#define ASTPRINT_H 1
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
{ s<<"\"";
  for(auto x:v) print_char(s,x);
  s<<"\"";
  if(p) s<<p;
  return 0;
}
template <typename T> 
inline int astprint(std::ostream &s, T v, int, const char *p)
{ s<<v; 
  if(p) s<<p;
  return 0;
}
#endif
template <typename T>
int astprint(std::ostream &s, Value<T> v, int i)
{ if(!v) s<<"nullptr";
  else astprint(s,T(v));
  return 0;
}
template <typename T>
int astprint(std::ostream &s, List<T> v, int i)
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
  return r;
}
}
using namespace ast;
#endif
