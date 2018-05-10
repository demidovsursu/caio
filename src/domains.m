domain Node {
   node2(sVal id, List<std::string> args)
   node1(sVal id)
}
domain Symbol {
   terminal(sVal id)
   ident(sVal id)
   node(sVal id, List<std::string> args)
}
domain Mrule {
   mrule(Node m, List<Code> code)
}
domain Vrule {
   vrule(Node m, List<Code> code)
}
domain Lrule {
   lexrule(List<std::string> states, sVal re, Laction action)
}
domain Term {
   tnode(sVal id, List<std::string> args)
   snode(sVal str)
}  
domain Laction
{ lterm(sVal id, Term t)
  lskip()
  lnext()
  lcode(List<Code> code)
}
domain Code {
  lexem(sVal text)
  pcode(List<Code> code)
  mcode(List<std::string> code, List<Mrule> rules)
  vcode(sVal id, sVal tip, sVal ret, List<Code> code, List<Vrule> rules)
  rterm(sVal val)
}
domain Decl {
  option(List<std::string> opts)
  decloper(List<std::string> ops)
  decltypes(sVal tip, List<Symbol> syms)
  declcode(sVal dest, List<Code> code)
}
domain Grule {
  grmrule(sVal id, List<Xrule> r)
}
domain Gaction {
  gempty()
  gterm(Term t)
  gcode(List<Code> code)
}
domain Gelem {
  trmelem(sVal s)
  symelem(sVal s)
  varelem(List<Xrule> r)
  optelem(List<Xrule> r)
  repelem1(List<Xrule> r)
  repelem0(List<Xrule> r)
}
domain Xrule {
  xrule(List<Gelem> e, Gaction a)
}
domain Program {
  prog(List<Decl> d, List<Lrule> lr, List<Grule> gr, List<Code> code)
}
