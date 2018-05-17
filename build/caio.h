#ifndef CAIO_H
#define CAIO_H 1
#define AST_LOCATIONS 1

#ifndef ASTTYPES_H
#define ASTTYPES_H 1
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <exception>
#include <initializer_list>

#ifndef YYLTYPE_IS_DECLARED
struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
#ifdef AST_LOCATIONS
void init_yyloc(YYLTYPE &);
#endif
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
#endif

namespace ast {
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
template <>
class Value<std::string> {
  size_t _len;
  char *_str;
  void check() const { if(!_str) throw std::logic_error("value isn't assigned"); }
public:
  Value()=default;
  explicit Value(const char *s) { _len=strlen(s); _str=strdup(s); }
  Value(const char *s, int l) { _len=l; _str=strdup(s); }
  explicit Value(const std::string &s) { _len=s.length(); _str=strdup(s.c_str()); }
  Value(std::nullptr_t) { _len=0; _str=nullptr; }
  operator std::string() const { check(); return _str; }
  operator bool() const{ return _str!=nullptr; }
  bool operator!() const{ return !_str; }
  const char *c_str() const { check(); return _str; }
  size_t size() const { return _len; }
  size_t length() const { return _len; }
  char operator[](size_t i) const { check(); return _str[i]; }
  char at(size_t i) const { check(); if(i>=_len) throw std::out_of_range("index out of range"); return _str[i]; }
  std::string substr(size_t i, size_t n=std::string::npos) const { return ((std::string)_str).substr(i,n); }
  Value<std::string> &operator=(const std::string& s) { _len=s.length(); _str=strdup(s.c_str()); return *this; }
  Value<std::string> &operator=(const char *s) { _len=strlen(s); _str=strdup(s); return *this; }
  Value<std::string> &operator=(std::nullptr_t) { _len=0; _str=nullptr; return *this; }
  Value<std::string> &operator=(const Value<std::string>& v)=default;
  Value<std::string> &operator+=(const std::string& s) { check(); (*this)=(std::string)_str+s; return *this; }
  Value<std::string> &operator+=(const char *s) { check(); (*this)=(std::string)_str+(std::string)s; return *this; }
  Value<std::string> &operator+=(char c) { check(); (*this)=(std::string)_str+std::string(1,c); return *this; }
  friend inline std::istream &operator>>(std::istream&s, Value<std::string> &v) { std::string x; s>>x; v=x; return s; }
  friend inline std::ostream &operator<<(std::ostream&s, const Value<std::string> &v) { v.check(); return s<<v._str; }
};
template <typename T>
inline T operator+(const Value<T>& v1, const Value<T>& v2) { return T(v1)+T(v2); }
template <typename T>
inline T operator+(const T &v1, const Value<T>& v2) { return v1+T(v2); }
template <typename T>
inline T operator+(const Value<T>& v1, const T& v2) { return T(v1)+v2; }

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
bool operator<(const Value<T> &v1, const Value<T>& v2) { 
  if(!v1 && !v2) return 0;
  if(!v1) return 1;
  if(!v2) return 0;
  return T(v1)<T(v2); 
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
inline bool operator!=(const Value<T> &v1, const Value<T>& v2) { return !(v1==v2); }
template <typename T>
inline bool operator!=(const T &v1, const Value<T>& v2) { return !(v1==v2); }
template <typename T>
inline bool operator!=(const Value<T> &v1, const T& v2) { return !(v1==v2); }

template <typename T>
inline bool operator>(const Value<T> &v1, const Value<T>& v2) { return v2<v1; }
template <typename T>
inline bool operator>(const T &v1, const Value<T>& v2) { return v2<v1; }
template <typename T>
inline bool operator>(const Value<T> &v1, const T& v2) { return v2<v1; }

template <typename T>
inline bool operator<=(const Value<T> &v1, const Value<T>& v2) { return !(v2<v1); }
template <typename T>
inline bool operator<=(const T &v1, const Value<T>& v2) { return !(v2<v1); }
template <typename T>
inline bool operator<=(const Value<T> &v1, const T& v2) { return !(v2<v1); }

template <typename T>
inline bool operator>=(const Value<T> &v1, const Value<T>& v2) { return !(v1<v2); }
template <typename T>
inline bool operator>=(const T &v1, const Value<T>& v2) { return !(v1<v2); }
template <typename T>
inline bool operator>=(const Value<T> &v1, const T& v2) { return !(v1<v2); }

template <typename T>
Value<T> &operator++(Value<T> &v, int)
{ Value<T> v2(v);
  ++v;
  return v2;
}
template <typename T>
Value<T> &operator--(Value<T> &v, int)
{ Value<T> v2(v);
  --v;
  return v2;
}

template <typename T> class List;
template <typename T> List<T> cons(const T& p);
template <typename T> List<T> cons(List<T> l, const T& p);
template <typename T> List<T> cons(const T& p, List<T> l);

template <typename T> List<T> cons(const Value<T> &p);
template <typename T> List<T> cons(List<T> l, const Value<T> &p);
template <typename T> List<T> cons(const Value<T> & p, List<T> l);

template <typename T> List<T> cons(List<T> l1, List<T> l2);
template <typename T> List<T> begin(List<T> l);
template <typename T> List<T> end(List<T> l);
template <typename T> bool operator==(const List<T> &l, const List<T> &r);
template <typename T> List<T> &operator++(List<T> &l);
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
public:
  List()=default;
  List(std::nullptr_t) { first=last=nullptr; _size=0; }
  List(std::initializer_list<T> v);
  T &operator*() { return first->head; }
  T *operator->() { return &(first->head); }
  T &operator[](size_t i);
  size_t size() { return _size; }
  List<T>& operator=(std::nullptr_t) { first=nullptr; last=nullptr; return *this; }
  
  friend List<T> cons<T>(const T& p);
  friend List<T> cons<T>(List<T> l, const T& p);
  friend List<T> cons<T>(const T& p, List<T> l);
  
  friend List<T> cons<T>(const Value<T> &p);
  friend List<T> cons<T>(List<T> l, const Value<T> &p);
  friend List<T> cons<T>(const Value<T> & p, List<T> l);
  
  template <typename Z> friend  List<Z*> cons(Z *p);
  template <typename Z> friend List<Z*> cons(List<Z*> l, Z *p);
  template <typename Z> friend List<Z*> cons(Z* p, List<Z*> l);
  
  friend List<T> cons<T>(List<T> l1, List<T> l2);
  friend List<T> begin<T>(List<T> l);
  friend List<T> end<T>(List<T> l);
  friend bool operator==<T>(const List<T> &l, const List<T> &r);
  friend List<T> &operator++ <T>(List<T> &l);
  operator bool() const { return first!=nullptr; }
  bool operator!() const { return first==nullptr; }
};
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
template <typename T>
List<T> cons(const Value<T> & p)
{ List<T> r(nullptr);
  if(!p) return r;
  r.first=r.last=new typename List<T>::Node(p,nullptr);
  r._size=1;
  return r;
}
template <typename T>
List<T> cons(List<T> l, const Value<T> &p)
{ 
  if(!p) return l;
  if(l.first==nullptr) return cons(p);
  List<T> r;
  r.first=l.first;
  r.last=l.last->tail=new typename List<T>::Node(p,nullptr);
  r._size=l._size+1;
  return r;
}
template <typename T>
List<T> cons(const Value<T> &p, List<T> l)
{
  if(!p) return l;
  if(l.first==nullptr) return cons(p);
  List<T> r;
  r.first=new typename List<T>::Node(p,l.first);
  r.last=l.last;
  r._size=l._size+1;
  return r;
}

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

#ifndef AST_BASE_DOMAIN
#define AST_BASE_DOMAIN 1
struct _domain {
#ifdef AST_LOCATIONS
  YYLTYPE yyloc;
  _domain() { init_yyloc(yyloc); }
#endif
  virtual ~_domain(){}
};
#endif
}
#endif
using namespace ast;
namespace ast {
struct Code_visitor;
struct Code_domain : _domain {
	virtual void accept(Code_visitor*, void*)=0;
};
typedef Code_domain *Code;
int astprint(std::ostream&, Code, int=0, const char* =nullptr);
struct Decl_visitor;
struct Decl_domain : _domain {
	virtual void accept(Decl_visitor*, void*)=0;
};
typedef Decl_domain *Decl;
int astprint(std::ostream&, Decl, int=0, const char* =nullptr);
struct Gaction_visitor;
struct Gaction_domain : _domain {
	virtual void accept(Gaction_visitor*, void*)=0;
};
typedef Gaction_domain *Gaction;
int astprint(std::ostream&, Gaction, int=0, const char* =nullptr);
struct Gelem_visitor;
struct Gelem_domain : _domain {
	virtual void accept(Gelem_visitor*, void*)=0;
};
typedef Gelem_domain *Gelem;
int astprint(std::ostream&, Gelem, int=0, const char* =nullptr);
struct Grule_visitor;
struct Grule_domain : _domain {
	virtual void accept(Grule_visitor*, void*)=0;
};
typedef Grule_domain *Grule;
int astprint(std::ostream&, Grule, int=0, const char* =nullptr);
struct Laction_visitor;
struct Laction_domain : _domain {
	virtual void accept(Laction_visitor*, void*)=0;
};
typedef Laction_domain *Laction;
int astprint(std::ostream&, Laction, int=0, const char* =nullptr);
struct Lrule_visitor;
struct Lrule_domain : _domain {
	virtual void accept(Lrule_visitor*, void*)=0;
};
typedef Lrule_domain *Lrule;
int astprint(std::ostream&, Lrule, int=0, const char* =nullptr);
struct Mrule_visitor;
struct Mrule_domain : _domain {
	virtual void accept(Mrule_visitor*, void*)=0;
};
typedef Mrule_domain *Mrule;
int astprint(std::ostream&, Mrule, int=0, const char* =nullptr);
struct Node_visitor;
struct Node_domain : _domain {
	virtual void accept(Node_visitor*, void*)=0;
};
typedef Node_domain *Node;
int astprint(std::ostream&, Node, int=0, const char* =nullptr);
struct Program_visitor;
struct Program_domain : _domain {
	virtual void accept(Program_visitor*, void*)=0;
};
typedef Program_domain *Program;
int astprint(std::ostream&, Program, int=0, const char* =nullptr);
struct Symbol_visitor;
struct Symbol_domain : _domain {
	virtual void accept(Symbol_visitor*, void*)=0;
};
typedef Symbol_domain *Symbol;
int astprint(std::ostream&, Symbol, int=0, const char* =nullptr);
struct Term_visitor;
struct Term_domain : _domain {
	virtual void accept(Term_visitor*, void*)=0;
};
typedef Term_domain *Term;
int astprint(std::ostream&, Term, int=0, const char* =nullptr);
struct Vrule_visitor;
struct Vrule_domain : _domain {
	virtual void accept(Vrule_visitor*, void*)=0;
};
typedef Vrule_domain *Vrule;
int astprint(std::ostream&, Vrule, int=0, const char* =nullptr);
struct Xrule_visitor;
struct Xrule_domain : _domain {
	virtual void accept(Xrule_visitor*, void*)=0;
};
typedef Xrule_domain *Xrule;
int astprint(std::ostream&, Xrule, int=0, const char* =nullptr);
struct declcode_node : Decl_domain {
	ast::Value<std::string> f1_;
	List<Code> f2_;
	declcode_node(ast::Value<std::string> a1, List<Code> a2):f1_(a1), f2_(a2){}
	void accept(Decl_visitor*, void*);
};
struct decloper_node : Decl_domain {
	List<std::string> f1_;
	decloper_node(List<std::string> a1):f1_(a1){}
	void accept(Decl_visitor*, void*);
};
struct declre_node : Decl_domain {
	std::string f1_;
	std::string f2_;
	declre_node(const std::string& a1, const std::string& a2):f1_(a1), f2_(a2){}
	void accept(Decl_visitor*, void*);
};
struct decltypes_node : Decl_domain {
	std::string f1_;
	List<Symbol> f2_;
	decltypes_node(const std::string& a1, List<Symbol> a2):f1_(a1), f2_(a2){}
	void accept(Decl_visitor*, void*);
};
struct gcode_node : Gaction_domain {
	List<Code> f1_;
	gcode_node(List<Code> a1):f1_(a1){}
	void accept(Gaction_visitor*, void*);
};
struct gempty_node : Gaction_domain {
	gempty_node(){}
	void accept(Gaction_visitor*, void*);
};
struct grmrule_node : Grule_domain {
	std::string f1_;
	List<Xrule> f2_;
	grmrule_node(const std::string& a1, List<Xrule> a2):f1_(a1), f2_(a2){}
	void accept(Grule_visitor*, void*);
};
struct gterm_node : Gaction_domain {
	Term f1_;
	gterm_node(Term a1):f1_(a1){}
	void accept(Gaction_visitor*, void*);
};
struct ident_node : Symbol_domain {
	std::string f1_;
	ident_node(const std::string& a1):f1_(a1){}
	void accept(Symbol_visitor*, void*);
};
struct lcode_node : Laction_domain {
	List<Code> f1_;
	lcode_node(List<Code> a1):f1_(a1){}
	void accept(Laction_visitor*, void*);
};
struct lexem_node : Code_domain {
	std::string f1_;
	lexem_node(const std::string& a1):f1_(a1){}
	void accept(Code_visitor*, void*);
};
struct lexrule_node : Lrule_domain {
	List<std::string> f1_;
	std::string f2_;
	Laction f3_;
	lexrule_node(List<std::string> a1, const std::string& a2, Laction a3):f1_(a1), f2_(a2), f3_(a3){}
	void accept(Lrule_visitor*, void*);
};
struct lnext_node : Laction_domain {
	lnext_node(){}
	void accept(Laction_visitor*, void*);
};
struct lskip_node : Laction_domain {
	lskip_node(){}
	void accept(Laction_visitor*, void*);
};
struct lterm_node : Laction_domain {
	ast::Value<std::string> f1_;
	Term f2_;
	lterm_node(ast::Value<std::string> a1, Term a2):f1_(a1), f2_(a2){}
	void accept(Laction_visitor*, void*);
};
struct mcode_node : Code_domain {
	List<std::string> f1_;
	List<Mrule> f2_;
	mcode_node(List<std::string> a1, List<Mrule> a2):f1_(a1), f2_(a2){}
	void accept(Code_visitor*, void*);
};
struct mrule_node : Mrule_domain {
	Node f1_;
	List<Code> f2_;
	mrule_node(Node a1, List<Code> a2):f1_(a1), f2_(a2){}
	void accept(Mrule_visitor*, void*);
};
struct node_node : Symbol_domain {
	std::string f1_;
	List<std::string> f2_;
	node_node(const std::string& a1, List<std::string> a2):f1_(a1), f2_(a2){}
	void accept(Symbol_visitor*, void*);
};
struct node1_node : Node_domain {
	std::string f1_;
	node1_node(const std::string& a1):f1_(a1){}
	void accept(Node_visitor*, void*);
};
struct node2_node : Node_domain {
	std::string f1_;
	List<std::string> f2_;
	node2_node(const std::string& a1, List<std::string> a2):f1_(a1), f2_(a2){}
	void accept(Node_visitor*, void*);
};
struct optelem_node : Gelem_domain {
	List<Xrule> f1_;
	optelem_node(List<Xrule> a1):f1_(a1){}
	void accept(Gelem_visitor*, void*);
};
struct pcode_node : Code_domain {
	List<Code> f1_;
	pcode_node(List<Code> a1):f1_(a1){}
	void accept(Code_visitor*, void*);
};
struct prog_node : Program_domain {
	List<Decl> f1_;
	List<Lrule> f2_;
	List<Grule> f3_;
	List<Code> f4_;
	prog_node(List<Decl> a1, List<Lrule> a2, List<Grule> a3, List<Code> a4):f1_(a1), f2_(a2), f3_(a3), f4_(a4){}
	void accept(Program_visitor*, void*);
};
struct repelem0_node : Gelem_domain {
	List<Xrule> f1_;
	repelem0_node(List<Xrule> a1):f1_(a1){}
	void accept(Gelem_visitor*, void*);
};
struct repelem1_node : Gelem_domain {
	List<Xrule> f1_;
	repelem1_node(List<Xrule> a1):f1_(a1){}
	void accept(Gelem_visitor*, void*);
};
struct snode_node : Term_domain {
	std::string f1_;
	snode_node(const std::string& a1):f1_(a1){}
	void accept(Term_visitor*, void*);
};
struct symelem_node : Gelem_domain {
	std::string f1_;
	symelem_node(const std::string& a1):f1_(a1){}
	void accept(Gelem_visitor*, void*);
};
struct terminal_node : Symbol_domain {
	std::string f1_;
	terminal_node(const std::string& a1):f1_(a1){}
	void accept(Symbol_visitor*, void*);
};
struct tnode_node : Term_domain {
	std::string f1_;
	List<std::string> f2_;
	tnode_node(const std::string& a1, List<std::string> a2):f1_(a1), f2_(a2){}
	void accept(Term_visitor*, void*);
};
struct token_node : Code_domain {
	std::string f1_;
	token_node(const std::string& a1):f1_(a1){}
	void accept(Code_visitor*, void*);
};
struct trmelem_node : Gelem_domain {
	std::string f1_;
	trmelem_node(const std::string& a1):f1_(a1){}
	void accept(Gelem_visitor*, void*);
};
struct varelem_node : Gelem_domain {
	List<Xrule> f1_;
	varelem_node(List<Xrule> a1):f1_(a1){}
	void accept(Gelem_visitor*, void*);
};
struct vcode_node : Code_domain {
	std::string f1_;
	std::string f2_;
	std::string f3_;
	List<Code> f4_;
	List<Vrule> f5_;
	vcode_node(const std::string& a1, const std::string& a2, const std::string& a3, List<Code> a4, List<Vrule> a5):f1_(a1), f2_(a2), f3_(a3), f4_(a4), f5_(a5){}
	void accept(Code_visitor*, void*);
};
struct vrule_node : Vrule_domain {
	Node f1_;
	List<Code> f2_;
	vrule_node(Node a1, List<Code> a2):f1_(a1), f2_(a2){}
	void accept(Vrule_visitor*, void*);
};
struct xrule_node : Xrule_domain {
	List<Gelem> f1_;
	Gaction f2_;
	xrule_node(List<Gelem> a1, Gaction a2):f1_(a1), f2_(a2){}
	void accept(Xrule_visitor*, void*);
};
inline Decl declcode(ast::Value<std::string> a1, List<Code> a2) {
	return new declcode_node(a1, a2);
}
inline Decl decloper(List<std::string> a1) {
	return new decloper_node(a1);
}
inline Decl declre(const std::string& a1, const std::string& a2) {
	return new declre_node(a1, a2);
}
inline Decl decltypes(const std::string& a1, List<Symbol> a2) {
	return new decltypes_node(a1, a2);
}
inline Gaction gcode(List<Code> a1) {
	return new gcode_node(a1);
}
inline Gaction gempty() {
	return new gempty_node();
}
inline Grule grmrule(const std::string& a1, List<Xrule> a2) {
	return new grmrule_node(a1, a2);
}
inline Gaction gterm(Term a1) {
	return new gterm_node(a1);
}
inline Symbol ident(const std::string& a1) {
	return new ident_node(a1);
}
inline Laction lcode(List<Code> a1) {
	return new lcode_node(a1);
}
inline Code lexem(const std::string& a1) {
	return new lexem_node(a1);
}
inline Lrule lexrule(List<std::string> a1, const std::string& a2, Laction a3) {
	return new lexrule_node(a1, a2, a3);
}
inline Laction lnext() {
	return new lnext_node();
}
inline Laction lskip() {
	return new lskip_node();
}
inline Laction lterm(ast::Value<std::string> a1, Term a2) {
	return new lterm_node(a1, a2);
}
inline Code mcode(List<std::string> a1, List<Mrule> a2) {
	return new mcode_node(a1, a2);
}
inline Mrule mrule(Node a1, List<Code> a2) {
	return new mrule_node(a1, a2);
}
inline Symbol node(const std::string& a1, List<std::string> a2) {
	return new node_node(a1, a2);
}
inline Node node1(const std::string& a1) {
	return new node1_node(a1);
}
inline Node node2(const std::string& a1, List<std::string> a2) {
	return new node2_node(a1, a2);
}
inline Gelem optelem(List<Xrule> a1) {
	return new optelem_node(a1);
}
inline Code pcode(List<Code> a1) {
	return new pcode_node(a1);
}
inline Program prog(List<Decl> a1, List<Lrule> a2, List<Grule> a3, List<Code> a4) {
	return new prog_node(a1, a2, a3, a4);
}
inline Gelem repelem0(List<Xrule> a1) {
	return new repelem0_node(a1);
}
inline Gelem repelem1(List<Xrule> a1) {
	return new repelem1_node(a1);
}
inline Term snode(const std::string& a1) {
	return new snode_node(a1);
}
inline Gelem symelem(const std::string& a1) {
	return new symelem_node(a1);
}
inline Symbol terminal(const std::string& a1) {
	return new terminal_node(a1);
}
inline Term tnode(const std::string& a1, List<std::string> a2) {
	return new tnode_node(a1, a2);
}
inline Code token(const std::string& a1) {
	return new token_node(a1);
}
inline Gelem trmelem(const std::string& a1) {
	return new trmelem_node(a1);
}
inline Gelem varelem(List<Xrule> a1) {
	return new varelem_node(a1);
}
inline Code vcode(const std::string& a1, const std::string& a2, const std::string& a3, List<Code> a4, List<Vrule> a5) {
	return new vcode_node(a1, a2, a3, a4, a5);
}
inline Vrule vrule(Node a1, List<Code> a2) {
	return new vrule_node(a1, a2);
}
inline Xrule xrule(List<Gelem> a1, Gaction a2) {
	return new xrule_node(a1, a2);
}
struct Code_visitor {
	virtual ~Code_visitor(){}
	virtual void visit(lexem_node*, void*) {}
	virtual void visit(mcode_node*, void*) {}
	virtual void visit(pcode_node*, void*) {}
	virtual void visit(token_node*, void*) {}
	virtual void visit(vcode_node*, void*) {}
};
template <typename T> struct Code_Tvisitor: Code_visitor {
	T operator()(Code v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(lexem_node*) { return T(); }
	void visit(lexem_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(mcode_node*) { return T(); }
	void visit(mcode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(pcode_node*) { return T(); }
	void visit(pcode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(token_node*) { return T(); }
	void visit(token_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(vcode_node*) { return T(); }
	void visit(vcode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Code_Tvisitor<void>: Code_visitor {
	void operator()(Code v){ if(v) v->accept(this,nullptr); }
	virtual void visit(lexem_node*) {}
	void visit(lexem_node* n,void* r) { visit(n); }
	virtual void visit(mcode_node*) {}
	void visit(mcode_node* n,void* r) { visit(n); }
	virtual void visit(pcode_node*) {}
	void visit(pcode_node* n,void* r) { visit(n); }
	virtual void visit(token_node*) {}
	void visit(token_node* n,void* r) { visit(n); }
	virtual void visit(vcode_node*) {}
	void visit(vcode_node* n,void* r) { visit(n); }
};
struct Decl_visitor {
	virtual ~Decl_visitor(){}
	virtual void visit(declcode_node*, void*) {}
	virtual void visit(decloper_node*, void*) {}
	virtual void visit(declre_node*, void*) {}
	virtual void visit(decltypes_node*, void*) {}
};
template <typename T> struct Decl_Tvisitor: Decl_visitor {
	T operator()(Decl v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(declcode_node*) { return T(); }
	void visit(declcode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(decloper_node*) { return T(); }
	void visit(decloper_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(declre_node*) { return T(); }
	void visit(declre_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(decltypes_node*) { return T(); }
	void visit(decltypes_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Decl_Tvisitor<void>: Decl_visitor {
	void operator()(Decl v){ if(v) v->accept(this,nullptr); }
	virtual void visit(declcode_node*) {}
	void visit(declcode_node* n,void* r) { visit(n); }
	virtual void visit(decloper_node*) {}
	void visit(decloper_node* n,void* r) { visit(n); }
	virtual void visit(declre_node*) {}
	void visit(declre_node* n,void* r) { visit(n); }
	virtual void visit(decltypes_node*) {}
	void visit(decltypes_node* n,void* r) { visit(n); }
};
struct Gaction_visitor {
	virtual ~Gaction_visitor(){}
	virtual void visit(gcode_node*, void*) {}
	virtual void visit(gempty_node*, void*) {}
	virtual void visit(gterm_node*, void*) {}
};
template <typename T> struct Gaction_Tvisitor: Gaction_visitor {
	T operator()(Gaction v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(gcode_node*) { return T(); }
	void visit(gcode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(gempty_node*) { return T(); }
	void visit(gempty_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(gterm_node*) { return T(); }
	void visit(gterm_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Gaction_Tvisitor<void>: Gaction_visitor {
	void operator()(Gaction v){ if(v) v->accept(this,nullptr); }
	virtual void visit(gcode_node*) {}
	void visit(gcode_node* n,void* r) { visit(n); }
	virtual void visit(gempty_node*) {}
	void visit(gempty_node* n,void* r) { visit(n); }
	virtual void visit(gterm_node*) {}
	void visit(gterm_node* n,void* r) { visit(n); }
};
struct Gelem_visitor {
	virtual ~Gelem_visitor(){}
	virtual void visit(optelem_node*, void*) {}
	virtual void visit(repelem0_node*, void*) {}
	virtual void visit(repelem1_node*, void*) {}
	virtual void visit(symelem_node*, void*) {}
	virtual void visit(trmelem_node*, void*) {}
	virtual void visit(varelem_node*, void*) {}
};
template <typename T> struct Gelem_Tvisitor: Gelem_visitor {
	T operator()(Gelem v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(optelem_node*) { return T(); }
	void visit(optelem_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(repelem0_node*) { return T(); }
	void visit(repelem0_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(repelem1_node*) { return T(); }
	void visit(repelem1_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(symelem_node*) { return T(); }
	void visit(symelem_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(trmelem_node*) { return T(); }
	void visit(trmelem_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(varelem_node*) { return T(); }
	void visit(varelem_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Gelem_Tvisitor<void>: Gelem_visitor {
	void operator()(Gelem v){ if(v) v->accept(this,nullptr); }
	virtual void visit(optelem_node*) {}
	void visit(optelem_node* n,void* r) { visit(n); }
	virtual void visit(repelem0_node*) {}
	void visit(repelem0_node* n,void* r) { visit(n); }
	virtual void visit(repelem1_node*) {}
	void visit(repelem1_node* n,void* r) { visit(n); }
	virtual void visit(symelem_node*) {}
	void visit(symelem_node* n,void* r) { visit(n); }
	virtual void visit(trmelem_node*) {}
	void visit(trmelem_node* n,void* r) { visit(n); }
	virtual void visit(varelem_node*) {}
	void visit(varelem_node* n,void* r) { visit(n); }
};
struct Grule_visitor {
	virtual ~Grule_visitor(){}
	virtual void visit(grmrule_node*, void*) {}
};
template <typename T> struct Grule_Tvisitor: Grule_visitor {
	T operator()(Grule v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(grmrule_node*) { return T(); }
	void visit(grmrule_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Grule_Tvisitor<void>: Grule_visitor {
	void operator()(Grule v){ if(v) v->accept(this,nullptr); }
	virtual void visit(grmrule_node*) {}
	void visit(grmrule_node* n,void* r) { visit(n); }
};
struct Laction_visitor {
	virtual ~Laction_visitor(){}
	virtual void visit(lcode_node*, void*) {}
	virtual void visit(lnext_node*, void*) {}
	virtual void visit(lskip_node*, void*) {}
	virtual void visit(lterm_node*, void*) {}
};
template <typename T> struct Laction_Tvisitor: Laction_visitor {
	T operator()(Laction v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(lcode_node*) { return T(); }
	void visit(lcode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(lnext_node*) { return T(); }
	void visit(lnext_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(lskip_node*) { return T(); }
	void visit(lskip_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(lterm_node*) { return T(); }
	void visit(lterm_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Laction_Tvisitor<void>: Laction_visitor {
	void operator()(Laction v){ if(v) v->accept(this,nullptr); }
	virtual void visit(lcode_node*) {}
	void visit(lcode_node* n,void* r) { visit(n); }
	virtual void visit(lnext_node*) {}
	void visit(lnext_node* n,void* r) { visit(n); }
	virtual void visit(lskip_node*) {}
	void visit(lskip_node* n,void* r) { visit(n); }
	virtual void visit(lterm_node*) {}
	void visit(lterm_node* n,void* r) { visit(n); }
};
struct Lrule_visitor {
	virtual ~Lrule_visitor(){}
	virtual void visit(lexrule_node*, void*) {}
};
template <typename T> struct Lrule_Tvisitor: Lrule_visitor {
	T operator()(Lrule v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(lexrule_node*) { return T(); }
	void visit(lexrule_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Lrule_Tvisitor<void>: Lrule_visitor {
	void operator()(Lrule v){ if(v) v->accept(this,nullptr); }
	virtual void visit(lexrule_node*) {}
	void visit(lexrule_node* n,void* r) { visit(n); }
};
struct Mrule_visitor {
	virtual ~Mrule_visitor(){}
	virtual void visit(mrule_node*, void*) {}
};
template <typename T> struct Mrule_Tvisitor: Mrule_visitor {
	T operator()(Mrule v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(mrule_node*) { return T(); }
	void visit(mrule_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Mrule_Tvisitor<void>: Mrule_visitor {
	void operator()(Mrule v){ if(v) v->accept(this,nullptr); }
	virtual void visit(mrule_node*) {}
	void visit(mrule_node* n,void* r) { visit(n); }
};
struct Node_visitor {
	virtual ~Node_visitor(){}
	virtual void visit(node1_node*, void*) {}
	virtual void visit(node2_node*, void*) {}
};
template <typename T> struct Node_Tvisitor: Node_visitor {
	T operator()(Node v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(node1_node*) { return T(); }
	void visit(node1_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(node2_node*) { return T(); }
	void visit(node2_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Node_Tvisitor<void>: Node_visitor {
	void operator()(Node v){ if(v) v->accept(this,nullptr); }
	virtual void visit(node1_node*) {}
	void visit(node1_node* n,void* r) { visit(n); }
	virtual void visit(node2_node*) {}
	void visit(node2_node* n,void* r) { visit(n); }
};
struct Program_visitor {
	virtual ~Program_visitor(){}
	virtual void visit(prog_node*, void*) {}
};
template <typename T> struct Program_Tvisitor: Program_visitor {
	T operator()(Program v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(prog_node*) { return T(); }
	void visit(prog_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Program_Tvisitor<void>: Program_visitor {
	void operator()(Program v){ if(v) v->accept(this,nullptr); }
	virtual void visit(prog_node*) {}
	void visit(prog_node* n,void* r) { visit(n); }
};
struct Symbol_visitor {
	virtual ~Symbol_visitor(){}
	virtual void visit(ident_node*, void*) {}
	virtual void visit(node_node*, void*) {}
	virtual void visit(terminal_node*, void*) {}
};
template <typename T> struct Symbol_Tvisitor: Symbol_visitor {
	T operator()(Symbol v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(ident_node*) { return T(); }
	void visit(ident_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(node_node*) { return T(); }
	void visit(node_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(terminal_node*) { return T(); }
	void visit(terminal_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Symbol_Tvisitor<void>: Symbol_visitor {
	void operator()(Symbol v){ if(v) v->accept(this,nullptr); }
	virtual void visit(ident_node*) {}
	void visit(ident_node* n,void* r) { visit(n); }
	virtual void visit(node_node*) {}
	void visit(node_node* n,void* r) { visit(n); }
	virtual void visit(terminal_node*) {}
	void visit(terminal_node* n,void* r) { visit(n); }
};
struct Term_visitor {
	virtual ~Term_visitor(){}
	virtual void visit(snode_node*, void*) {}
	virtual void visit(tnode_node*, void*) {}
};
template <typename T> struct Term_Tvisitor: Term_visitor {
	T operator()(Term v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(snode_node*) { return T(); }
	void visit(snode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
	virtual T visit(tnode_node*) { return T(); }
	void visit(tnode_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Term_Tvisitor<void>: Term_visitor {
	void operator()(Term v){ if(v) v->accept(this,nullptr); }
	virtual void visit(snode_node*) {}
	void visit(snode_node* n,void* r) { visit(n); }
	virtual void visit(tnode_node*) {}
	void visit(tnode_node* n,void* r) { visit(n); }
};
struct Vrule_visitor {
	virtual ~Vrule_visitor(){}
	virtual void visit(vrule_node*, void*) {}
};
template <typename T> struct Vrule_Tvisitor: Vrule_visitor {
	T operator()(Vrule v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(vrule_node*) { return T(); }
	void visit(vrule_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Vrule_Tvisitor<void>: Vrule_visitor {
	void operator()(Vrule v){ if(v) v->accept(this,nullptr); }
	virtual void visit(vrule_node*) {}
	void visit(vrule_node* n,void* r) { visit(n); }
};
struct Xrule_visitor {
	virtual ~Xrule_visitor(){}
	virtual void visit(xrule_node*, void*) {}
};
template <typename T> struct Xrule_Tvisitor: Xrule_visitor {
	T operator()(Xrule v){ T r; if(v) v->accept(this,&r); return r; }
	virtual T visit(xrule_node*) { return T(); }
	void visit(xrule_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }
};
template <> struct Xrule_Tvisitor<void>: Xrule_visitor {
	void operator()(Xrule v){ if(v) v->accept(this,nullptr); }
	virtual void visit(xrule_node*) {}
	void visit(xrule_node* n,void* r) { visit(n); }
};
inline void declcode_node::accept(Decl_visitor* v, void* r) {
	v->visit(this, r);
}
inline void decloper_node::accept(Decl_visitor* v, void* r) {
	v->visit(this, r);
}
inline void declre_node::accept(Decl_visitor* v, void* r) {
	v->visit(this, r);
}
inline void decltypes_node::accept(Decl_visitor* v, void* r) {
	v->visit(this, r);
}
inline void gcode_node::accept(Gaction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void gempty_node::accept(Gaction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void grmrule_node::accept(Grule_visitor* v, void* r) {
	v->visit(this, r);
}
inline void gterm_node::accept(Gaction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void ident_node::accept(Symbol_visitor* v, void* r) {
	v->visit(this, r);
}
inline void lcode_node::accept(Laction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void lexem_node::accept(Code_visitor* v, void* r) {
	v->visit(this, r);
}
inline void lexrule_node::accept(Lrule_visitor* v, void* r) {
	v->visit(this, r);
}
inline void lnext_node::accept(Laction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void lskip_node::accept(Laction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void lterm_node::accept(Laction_visitor* v, void* r) {
	v->visit(this, r);
}
inline void mcode_node::accept(Code_visitor* v, void* r) {
	v->visit(this, r);
}
inline void mrule_node::accept(Mrule_visitor* v, void* r) {
	v->visit(this, r);
}
inline void node_node::accept(Symbol_visitor* v, void* r) {
	v->visit(this, r);
}
inline void node1_node::accept(Node_visitor* v, void* r) {
	v->visit(this, r);
}
inline void node2_node::accept(Node_visitor* v, void* r) {
	v->visit(this, r);
}
inline void optelem_node::accept(Gelem_visitor* v, void* r) {
	v->visit(this, r);
}
inline void pcode_node::accept(Code_visitor* v, void* r) {
	v->visit(this, r);
}
inline void prog_node::accept(Program_visitor* v, void* r) {
	v->visit(this, r);
}
inline void repelem0_node::accept(Gelem_visitor* v, void* r) {
	v->visit(this, r);
}
inline void repelem1_node::accept(Gelem_visitor* v, void* r) {
	v->visit(this, r);
}
inline void snode_node::accept(Term_visitor* v, void* r) {
	v->visit(this, r);
}
inline void symelem_node::accept(Gelem_visitor* v, void* r) {
	v->visit(this, r);
}
inline void terminal_node::accept(Symbol_visitor* v, void* r) {
	v->visit(this, r);
}
inline void tnode_node::accept(Term_visitor* v, void* r) {
	v->visit(this, r);
}
inline void token_node::accept(Code_visitor* v, void* r) {
	v->visit(this, r);
}
inline void trmelem_node::accept(Gelem_visitor* v, void* r) {
	v->visit(this, r);
}
inline void varelem_node::accept(Gelem_visitor* v, void* r) {
	v->visit(this, r);
}
inline void vcode_node::accept(Code_visitor* v, void* r) {
	v->visit(this, r);
}
inline void vrule_node::accept(Vrule_visitor* v, void* r) {
	v->visit(this, r);
}
inline void xrule_node::accept(Xrule_visitor* v, void* r) {
	v->visit(this, r);
}
}
int yyliteral(const std::string&);
extern int yydebug_flag;
void yystart(FILE *);
void yystart(std::istream&);
int yywrap();
int yyparse();
extern const char* yyinputfile;
extern char** yyargv;
extern int yyargc;
union YYSTYPE {
  Code f15_;
  Decl f2_;
  Gaction f26_;
  Gelem f3_;
  Grule f22_;
  Laction f23_;
  List<Code> f6_;
  List<Decl> f10_;
  List<Gelem> f14_;
  List<Grule> f5_;
  List<Lrule> f21_;
  List<Mrule> f17_;
  List<Symbol> f7_;
  List<Vrule> f19_;
  List<Xrule> f4_;
  List<std::string> f9_;
  Lrule f16_;
  Mrule f18_;
  Node f24_;
  Program f25_;
  Symbol f8_;
  Term f12_;
  Vrule f20_;
  Xrule f13_;
  ast::Value<std::string> f1_;
  ast::Value<std::string> f11_;
};
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
extern Program yyastroot;
void clear_attr(YYSTYPE&);
void yyerror(const std::string &);
void yyerror(int, int, const std::string&);
int yylex(YYSTYPE*, YYLTYPE*);
void yyerror(YYLTYPE*, const char*);
void set_yyloc(const YYLTYPE&);
void set_yyloc(int, int);

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <regex>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
using namespace std;

extern int bnf_flag;
extern int yyparse_flag;
extern int yylex_flag;
void generate(const string &fn, const string &fp, Program);
void switch_option(const string &o);
extern string filename,filepath;
void get_args();

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
inline int astprint(std::ostream &s, T v, int=0, const char *p=nullptr)
{ s<<v; 
  if(p) s<<p;
  return 0;
}
#endif
template <typename T>
int astprint(std::ostream &s, Value<T> v, int=0, const char *p=nullptr)
{ if(!v) s<<"nullptr";
  else astprint(s,T(v));
  if(p) s<<p;
  return 0;
}
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
}
#endif
#endif
