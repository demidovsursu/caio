#ifndef CAIO_H
#define CAIO_H 1

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

namespace ast {

template <typename T> inline void destroy(T& p) { }
template <typename T> inline void destroy(T*& p) { if(p) delete p; p=nullptr; }

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
inline T operator+(const Value<T>& v1, const Value<T>& v2) { return T(v1)+T(v2); }
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

  friend List<T> cons<T>(const Value<T> &p);
  friend List<T> cons<T>(List<T> l, const Value<T> &p);
  friend List<T> cons<T>(const Value<T> & p, List<T> l);

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

  YYLTYPE yyloc;
  _domain(const YYLTYPE *_loc) { if(_loc) yyloc=*_loc; else memset(&yyloc,0,sizeof(yyloc)); }

  virtual ~_domain(){}
};
#endif
}
#endif
namespace ast {
struct Code_domain : _domain {
	Code_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Code_domain *Code;
int astprint(std::ostream&, Code, int=0, const char* =nullptr);
struct Decl_domain : _domain {
	Decl_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Decl_domain *Decl;
int astprint(std::ostream&, Decl, int=0, const char* =nullptr);
struct Gaction_domain : _domain {
	Gaction_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Gaction_domain *Gaction;
int astprint(std::ostream&, Gaction, int=0, const char* =nullptr);
struct Gelem_domain : _domain {
	Gelem_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Gelem_domain *Gelem;
int astprint(std::ostream&, Gelem, int=0, const char* =nullptr);
struct Grule_domain : _domain {
	Grule_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Grule_domain *Grule;
int astprint(std::ostream&, Grule, int=0, const char* =nullptr);
struct Laction_domain : _domain {
	Laction_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Laction_domain *Laction;
int astprint(std::ostream&, Laction, int=0, const char* =nullptr);
struct Lrule_domain : _domain {
	Lrule_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Lrule_domain *Lrule;
int astprint(std::ostream&, Lrule, int=0, const char* =nullptr);
struct Mrule_domain : _domain {
	Mrule_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Mrule_domain *Mrule;
int astprint(std::ostream&, Mrule, int=0, const char* =nullptr);
struct Node_domain : _domain {
	Node_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Node_domain *Node;
int astprint(std::ostream&, Node, int=0, const char* =nullptr);
struct Program_domain : _domain {
	Program_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Program_domain *Program;
int astprint(std::ostream&, Program, int=0, const char* =nullptr);
struct Symbol_domain : _domain {
	Symbol_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Symbol_domain *Symbol;
int astprint(std::ostream&, Symbol, int=0, const char* =nullptr);
struct Term_domain : _domain {
	Term_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Term_domain *Term;
int astprint(std::ostream&, Term, int=0, const char* =nullptr);
struct Vrule_domain : _domain {
	Vrule_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Vrule_domain *Vrule;
int astprint(std::ostream&, Vrule, int=0, const char* =nullptr);
struct Xrule_domain : _domain {
	Xrule_domain(const YYLTYPE *_loc):_domain(_loc) {}
};
typedef Xrule_domain *Xrule;
int astprint(std::ostream&, Xrule, int=0, const char* =nullptr);
struct declcode_node : Decl_domain {
	ast::Value<std::string> f1_;
	List<Code> f2_;
	declcode_node(ast::Value<std::string> a1, List<Code> a2, const YYLTYPE *_loc=nullptr):Decl_domain(_loc), f1_(a1), f2_(a2){}
	~declcode_node() {
	  destroy(f1_);
	  destroy(f2_);
	}
};
struct decloper_node : Decl_domain {
	List<std::string> f1_;
	decloper_node(List<std::string> a1, const YYLTYPE *_loc=nullptr):Decl_domain(_loc), f1_(a1){}
	~decloper_node() {
	  destroy(f1_);
	}
};
struct declre_node : Decl_domain {
	std::string f1_;
	std::string f2_;
	declre_node(const std::string& a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Decl_domain(_loc), f1_(a1), f2_(a2){}
};
struct decltypes_node : Decl_domain {
	std::string f1_;
	List<Symbol> f2_;
	decltypes_node(const std::string& a1, List<Symbol> a2, const YYLTYPE *_loc=nullptr):Decl_domain(_loc), f1_(a1), f2_(a2){}
	~decltypes_node() {
	  destroy(f2_);
	}
};
struct gcode_node : Gaction_domain {
	List<Code> f1_;
	gcode_node(List<Code> a1, const YYLTYPE *_loc=nullptr):Gaction_domain(_loc), f1_(a1){}
	~gcode_node() {
	  destroy(f1_);
	}
};
struct gempty_node : Gaction_domain {
	gempty_node(const YYLTYPE *_loc=nullptr):Gaction_domain(_loc) {}
};
struct grmrule_node : Grule_domain {
	std::string f1_;
	List<Xrule> f2_;
	grmrule_node(const std::string& a1, List<Xrule> a2, const YYLTYPE *_loc=nullptr):Grule_domain(_loc), f1_(a1), f2_(a2){}
	~grmrule_node() {
	  destroy(f2_);
	}
};
struct gterm_node : Gaction_domain {
	Term f1_;
	gterm_node(Term a1, const YYLTYPE *_loc=nullptr):Gaction_domain(_loc), f1_(a1){}
	~gterm_node() {
	  destroy(f1_);
	}
};
struct ident_node : Symbol_domain {
	std::string f1_;
	ident_node(const std::string& a1, const YYLTYPE *_loc=nullptr):Symbol_domain(_loc), f1_(a1){}
};
struct lcode_node : Laction_domain {
	List<Code> f1_;
	lcode_node(List<Code> a1, const YYLTYPE *_loc=nullptr):Laction_domain(_loc), f1_(a1){}
	~lcode_node() {
	  destroy(f1_);
	}
};
struct lexem_node : Code_domain {
	std::string f1_;
	lexem_node(const std::string& a1, const YYLTYPE *_loc=nullptr):Code_domain(_loc), f1_(a1){}
};
struct lexrule_node : Lrule_domain {
	List<std::string> f1_;
	std::string f2_;
	Laction f3_;
	lexrule_node(List<std::string> a1, const std::string& a2, Laction a3, const YYLTYPE *_loc=nullptr):Lrule_domain(_loc), f1_(a1), f2_(a2), f3_(a3){}
	~lexrule_node() {
	  destroy(f1_);
	  destroy(f3_);
	}
};
struct lnext_node : Laction_domain {
	lnext_node(const YYLTYPE *_loc=nullptr):Laction_domain(_loc) {}
};
struct lskip_node : Laction_domain {
	lskip_node(const YYLTYPE *_loc=nullptr):Laction_domain(_loc) {}
};
struct lterm_node : Laction_domain {
	ast::Value<std::string> f1_;
	Term f2_;
	lterm_node(ast::Value<std::string> a1, Term a2, const YYLTYPE *_loc=nullptr):Laction_domain(_loc), f1_(a1), f2_(a2){}
	~lterm_node() {
	  destroy(f1_);
	  destroy(f2_);
	}
};
struct mcode_node : Code_domain {
	List<std::string> f1_;
	List<Mrule> f2_;
	mcode_node(List<std::string> a1, List<Mrule> a2, const YYLTYPE *_loc=nullptr):Code_domain(_loc), f1_(a1), f2_(a2){}
	~mcode_node() {
	  destroy(f1_);
	  destroy(f2_);
	}
};
struct mrule_node : Mrule_domain {
	Node f1_;
	List<Code> f2_;
	mrule_node(Node a1, List<Code> a2, const YYLTYPE *_loc=nullptr):Mrule_domain(_loc), f1_(a1), f2_(a2){}
	~mrule_node() {
	  destroy(f1_);
	  destroy(f2_);
	}
};
struct node_node : Symbol_domain {
	std::string f1_;
	List<std::string> f2_;
	node_node(const std::string& a1, List<std::string> a2, const YYLTYPE *_loc=nullptr):Symbol_domain(_loc), f1_(a1), f2_(a2){}
	~node_node() {
	  destroy(f2_);
	}
};
struct node1_node : Node_domain {
	std::string f1_;
	node1_node(const std::string& a1, const YYLTYPE *_loc=nullptr):Node_domain(_loc), f1_(a1){}
};
struct node2_node : Node_domain {
	std::string f1_;
	List<std::string> f2_;
	node2_node(const std::string& a1, List<std::string> a2, const YYLTYPE *_loc=nullptr):Node_domain(_loc), f1_(a1), f2_(a2){}
	~node2_node() {
	  destroy(f2_);
	}
};
struct optelem_node : Gelem_domain {
	List<Xrule> f1_;
	std::string f2_;
	optelem_node(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Gelem_domain(_loc), f1_(a1), f2_(a2){}
	~optelem_node() {
	  destroy(f1_);
	}
};
struct pcode_node : Code_domain {
	List<Code> f1_;
	pcode_node(List<Code> a1, const YYLTYPE *_loc=nullptr):Code_domain(_loc), f1_(a1){}
	~pcode_node() {
	  destroy(f1_);
	}
};
struct prog_node : Program_domain {
	List<Decl> f1_;
	List<Lrule> f2_;
	List<Grule> f3_;
	List<Code> f4_;
	prog_node(List<Decl> a1, List<Lrule> a2, List<Grule> a3, List<Code> a4, const YYLTYPE *_loc=nullptr):Program_domain(_loc), f1_(a1), f2_(a2), f3_(a3), f4_(a4){}
	~prog_node() {
	  destroy(f1_);
	  destroy(f2_);
	  destroy(f3_);
	  destroy(f4_);
	}
};
struct repelem0_node : Gelem_domain {
	List<Xrule> f1_;
	std::string f2_;
	repelem0_node(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Gelem_domain(_loc), f1_(a1), f2_(a2){}
	~repelem0_node() {
	  destroy(f1_);
	}
};
struct repelem1_node : Gelem_domain {
	List<Xrule> f1_;
	std::string f2_;
	repelem1_node(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Gelem_domain(_loc), f1_(a1), f2_(a2){}
	~repelem1_node() {
	  destroy(f1_);
	}
};
struct snode_node : Term_domain {
	std::string f1_;
	snode_node(const std::string& a1, const YYLTYPE *_loc=nullptr):Term_domain(_loc), f1_(a1){}
};
struct symelem_node : Gelem_domain {
	std::string f1_;
	std::string f2_;
	symelem_node(const std::string& a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Gelem_domain(_loc), f1_(a1), f2_(a2){}
};
struct terminal_node : Symbol_domain {
	std::string f1_;
	terminal_node(const std::string& a1, const YYLTYPE *_loc=nullptr):Symbol_domain(_loc), f1_(a1){}
};
struct tnode_node : Term_domain {
	std::string f1_;
	List<std::string> f2_;
	tnode_node(const std::string& a1, List<std::string> a2, const YYLTYPE *_loc=nullptr):Term_domain(_loc), f1_(a1), f2_(a2){}
	~tnode_node() {
	  destroy(f2_);
	}
};
struct token_node : Code_domain {
	std::string f1_;
	token_node(const std::string& a1, const YYLTYPE *_loc=nullptr):Code_domain(_loc), f1_(a1){}
};
struct trmelem_node : Gelem_domain {
	std::string f1_;
	std::string f2_;
	trmelem_node(const std::string& a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Gelem_domain(_loc), f1_(a1), f2_(a2){}
};
struct varelem_node : Gelem_domain {
	List<Xrule> f1_;
	std::string f2_;
	varelem_node(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr):Gelem_domain(_loc), f1_(a1), f2_(a2){}
	~varelem_node() {
	  destroy(f1_);
	}
};
struct vcode_node : Code_domain {
	std::string f1_;
	std::string f2_;
	std::string f3_;
	List<Code> f4_;
	List<Vrule> f5_;
	vcode_node(const std::string& a1, const std::string& a2, const std::string& a3, List<Code> a4, List<Vrule> a5, const YYLTYPE *_loc=nullptr):Code_domain(_loc), f1_(a1), f2_(a2), f3_(a3), f4_(a4), f5_(a5){}
	~vcode_node() {
	  destroy(f4_);
	  destroy(f5_);
	}
};
struct vrule_node : Vrule_domain {
	Node f1_;
	List<Code> f2_;
	vrule_node(Node a1, List<Code> a2, const YYLTYPE *_loc=nullptr):Vrule_domain(_loc), f1_(a1), f2_(a2){}
	~vrule_node() {
	  destroy(f1_);
	  destroy(f2_);
	}
};
struct xrule_node : Xrule_domain {
	List<Gelem> f1_;
	Gaction f2_;
	xrule_node(List<Gelem> a1, Gaction a2, const YYLTYPE *_loc=nullptr):Xrule_domain(_loc), f1_(a1), f2_(a2){}
	~xrule_node() {
	  destroy(f1_);
	  destroy(f2_);
	}
};
inline Decl declcode(ast::Value<std::string> a1, List<Code> a2, const YYLTYPE *_loc=nullptr) {
	return new declcode_node(a1, a2, _loc);
}
inline Decl decloper(List<std::string> a1, const YYLTYPE *_loc=nullptr) {
	return new decloper_node(a1, _loc);
}
inline Decl declre(const std::string& a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new declre_node(a1, a2, _loc);
}
inline Decl decltypes(const std::string& a1, List<Symbol> a2, const YYLTYPE *_loc=nullptr) {
	return new decltypes_node(a1, a2, _loc);
}
inline Gaction gcode(List<Code> a1, const YYLTYPE *_loc=nullptr) {
	return new gcode_node(a1, _loc);
}
inline Gaction gempty(const YYLTYPE *_loc=nullptr) {
	return new gempty_node(_loc);
}
inline Grule grmrule(const std::string& a1, List<Xrule> a2, const YYLTYPE *_loc=nullptr) {
	return new grmrule_node(a1, a2, _loc);
}
inline Gaction gterm(Term a1, const YYLTYPE *_loc=nullptr) {
	return new gterm_node(a1, _loc);
}
inline Symbol ident(const std::string& a1, const YYLTYPE *_loc=nullptr) {
	return new ident_node(a1, _loc);
}
inline Laction lcode(List<Code> a1, const YYLTYPE *_loc=nullptr) {
	return new lcode_node(a1, _loc);
}
inline Code lexem(const std::string& a1, const YYLTYPE *_loc=nullptr) {
	return new lexem_node(a1, _loc);
}
inline Lrule lexrule(List<std::string> a1, const std::string& a2, Laction a3, const YYLTYPE *_loc=nullptr) {
	return new lexrule_node(a1, a2, a3, _loc);
}
inline Laction lnext(const YYLTYPE *_loc=nullptr) {
	return new lnext_node(_loc);
}
inline Laction lskip(const YYLTYPE *_loc=nullptr) {
	return new lskip_node(_loc);
}
inline Laction lterm(ast::Value<std::string> a1, Term a2, const YYLTYPE *_loc=nullptr) {
	return new lterm_node(a1, a2, _loc);
}
inline Code mcode(List<std::string> a1, List<Mrule> a2, const YYLTYPE *_loc=nullptr) {
	return new mcode_node(a1, a2, _loc);
}
inline Mrule mrule(Node a1, List<Code> a2, const YYLTYPE *_loc=nullptr) {
	return new mrule_node(a1, a2, _loc);
}
inline Symbol node(const std::string& a1, List<std::string> a2, const YYLTYPE *_loc=nullptr) {
	return new node_node(a1, a2, _loc);
}
inline Node node1(const std::string& a1, const YYLTYPE *_loc=nullptr) {
	return new node1_node(a1, _loc);
}
inline Node node2(const std::string& a1, List<std::string> a2, const YYLTYPE *_loc=nullptr) {
	return new node2_node(a1, a2, _loc);
}
inline Gelem optelem(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new optelem_node(a1, a2, _loc);
}
inline Code pcode(List<Code> a1, const YYLTYPE *_loc=nullptr) {
	return new pcode_node(a1, _loc);
}
inline Program prog(List<Decl> a1, List<Lrule> a2, List<Grule> a3, List<Code> a4, const YYLTYPE *_loc=nullptr) {
	return new prog_node(a1, a2, a3, a4, _loc);
}
inline Gelem repelem0(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new repelem0_node(a1, a2, _loc);
}
inline Gelem repelem1(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new repelem1_node(a1, a2, _loc);
}
inline Term snode(const std::string& a1, const YYLTYPE *_loc=nullptr) {
	return new snode_node(a1, _loc);
}
inline Gelem symelem(const std::string& a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new symelem_node(a1, a2, _loc);
}
inline Symbol terminal(const std::string& a1, const YYLTYPE *_loc=nullptr) {
	return new terminal_node(a1, _loc);
}
inline Term tnode(const std::string& a1, List<std::string> a2, const YYLTYPE *_loc=nullptr) {
	return new tnode_node(a1, a2, _loc);
}
inline Code token(const std::string& a1, const YYLTYPE *_loc=nullptr) {
	return new token_node(a1, _loc);
}
inline Gelem trmelem(const std::string& a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new trmelem_node(a1, a2, _loc);
}
inline Gelem varelem(List<Xrule> a1, const std::string& a2, const YYLTYPE *_loc=nullptr) {
	return new varelem_node(a1, a2, _loc);
}
inline Code vcode(const std::string& a1, const std::string& a2, const std::string& a3, List<Code> a4, List<Vrule> a5, const YYLTYPE *_loc=nullptr) {
	return new vcode_node(a1, a2, a3, a4, a5, _loc);
}
inline Vrule vrule(Node a1, List<Code> a2, const YYLTYPE *_loc=nullptr) {
	return new vrule_node(a1, a2, _loc);
}
inline Xrule xrule(List<Gelem> a1, Gaction a2, const YYLTYPE *_loc=nullptr) {
	return new xrule_node(a1, a2, _loc);
}
}
using namespace ast;
int yyliteral(const std::string&);
int yywrap();
int yyparse(void*);
extern const char* yyinputfile;
extern int yydebug_flag;
union YYSTYPE {
  Code f16_;
  Decl f2_;
  Gaction f26_;
  Gelem f3_;
  Grule f22_;
  Laction f23_;
  List<Code> f6_;
  List<Decl> f10_;
  List<Gelem> f14_;
  List<Grule> f5_;
  List<Lrule> f19_;
  List<Mrule> f17_;
  List<Symbol> f7_;
  List<Vrule> f20_;
  List<Xrule> f4_;
  List<std::string> f9_;
  Lrule f15_;
  Mrule f18_;
  Node f24_;
  Program f25_;
  Symbol f8_;
  Term f12_;
  Vrule f21_;
  Xrule f13_;
  ast::Value<std::string> f1_;
  ast::Value<std::string> f11_;
};
inline void yyclear_attr(YYSTYPE&v) { memset(&v,0,sizeof(v)); }
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
void yylex_destroy(void*);
const char* yylex_filename(void*, int=-1);
void yylex_init(void**);
void yylex_init(void**, FILE*, const std::string&);
void yylex_init(void**, std::istream &, const std::string&);
int yylex(YYSTYPE*, YYLTYPE*, void*);
void lexprint(std::ostream&, int, YYSTYPE&);
void yyerror(const std::string &);
void yyerror(YYLTYPE*, void*, const char*);
void yyinterpret(Program);
#define YYINTERPRET(ast,scanner) yyinterpret(ast)

	#line 2 "caio.caio"
  
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
enum Caio_mode { M_DECL, M_LEX, M_GRM, M_CODE };
extern int caio_mode;

extern int bnf_flag;
extern int yyparse_flag;
extern int yylex_flag;
void generate(const string &fn, const string &fp, Program);
void switch_option(const string &o);
void add_using(const string &o);
extern string filename,filepath;
void get_args(int &, char **&);
void set_input(const char*);
Gelem replace_altid(Gelem&, const string &);
#define YYARGINIT(argc,argv) get_args(argc,argv)
#define YYINIT(name) set_input(name)

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
