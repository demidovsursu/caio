%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
int nline=1;
char next_filename[100],curr_filename[100],out_filename[100],
   domain_name[100],struct_name[100],type_name[100],arg_name[100],match_name[100],value_name[100],
   visitor_name[100],return_name[100];
char output_buf[1000000];
int output_len=0;
int output_flg=0;
int match_rules[100];
int match_else[100];
int match_type[100];
int match_opens[100];
int match_level=0;
int matcherr_exists=0;
int with_exists=0;
struct fileinfo { char *name; int nline; } openfiles[10];
char *fields[100];
int nfields;
int nopenfiles=0;
struct domaininfo { char *name; int from,to; } domains[100];
int ndomains=0;
struct structinfo { char *name; char *domain; int nfields; char *types[100]; char *fields[100]; } structs[1000];
int nstructs=0;
int ndomains_open=0,nstructs_open=0;
int genhflg=0;
int genpflg=0;
int merrflg=1;
int invisit=0;
void error(const char *msg)
{ fprintf(stderr,"%s:%d:%s\n",curr_filename,nline,msg);
  exit(1);
}
void close_ast()
{ int i,j,k;
  if(!nopenfiles && ndomains>ndomains_open)
  { 
    if(genpflg) {
      printf("#include <iostream>\n");
      printf("#include <string>\n");
    }
    printf("namespace ast {\n");
    if(!with_exists)
    {
      printf("#ifndef AST_BASE_DOMAIN\n"
             "#define AST_BASE_DOMAIN 1\n");
      printf("struct _domain {\n\tvirtual ~_domain(){}\n");
      printf("};\n#endif\n");
      with_exists=1;
    }
    for(i=ndomains_open;i<ndomains;++i)
    { 
      printf("struct %s_visitor;\n",domains[i].name);
      printf("struct %s_domain : _domain {\n"
      "\tvirtual void accept(%s_visitor*, void*)=0;\n"
      "};\n",domains[i].name,domains[i].name);
      printf("typedef %s_domain *%s;\n",domains[i].name,domains[i].name);
      if(genpflg) printf("int astprint(std::ostream& s, %s v, int=0, const char* =nullptr);\n",domains[i].name);
    }
    for(i=nstructs_open;i<nstructs;++i)
    { 
      printf("struct %s_node : %s_domain {\n",structs[i].name,structs[i].domain);
      for(j=0;j<structs[i].nfields;++j)
        printf("\t%s %s;\n",structs[i].types[j],structs[i].fields[j]);
      printf("\t%s_node(",structs[i].name);
      for(j=0;j<structs[i].nfields;++j)
        printf("%s %s%s",structs[i].types[j],structs[i].fields[j],(j<structs[i].nfields-1?", ":""));
      if(structs[i].nfields>0)
      {
        printf("):");
        for(j=0;j<structs[i].nfields;++j)
          printf("%s(%s)%s",structs[i].fields[j],structs[i].fields[j],(j<structs[i].nfields-1?", ":""));
      }
      else
        printf(")");
      printf("{}\n");
      printf("\tvoid accept(%s_visitor*, void*);\n",structs[i].domain);
      printf("};\n");
    }
    for(i=nstructs_open;i<nstructs;++i)
    { printf("inline %s %s(",structs[i].domain,structs[i].name);
      for(j=0;j<structs[i].nfields;++j)
        printf("%s %s%s",structs[i].types[j],structs[i].fields[j],(j<structs[i].nfields-1?", ":""));
      printf(") {\n");
      printf("\treturn new %s_node(",structs[i].name);
      for(j=0;j<structs[i].nfields;++j)
        printf("%s%s",structs[i].fields[j],(j<structs[i].nfields-1?", ":""));
      printf(");\n");
      printf("}\n");
    }
    for(i=ndomains_open;i<ndomains;++i)
    { 
      printf("struct %s_visitor {\n\tvirtual ~%s_visitor(){}\n",domains[i].name,domains[i].name);
      for(k=domains[i].from;k<domains[i].to;++k)
      { printf("\tvirtual void visit(%s_node*, void*) {}\n",structs[k].name);
      }
      printf("};\n");
      printf("template <typename T> struct %s_Tvisitor: %s_visitor {\n",domains[i].name,domains[i].name);
      printf("\tT operator()(%s v){ T r; if(v) v->accept(this,&r); return r; }\n",domains[i].name);
      for(k=domains[i].from;k<domains[i].to;++k)
      { printf("\tvirtual T visit(%s_node*) { return T(); }\n",structs[k].name);
        printf("\tvoid visit(%s_node* n,void* r) { *reinterpret_cast<T*>(r)=visit(n); }\n",structs[k].name);
      }
      printf("};\n");
      printf("template <> struct %s_Tvisitor<void>: %s_visitor {\n",domains[i].name,domains[i].name);
      printf("\tvoid operator()(%s v){ if(v) v->accept(this,nullptr); }\n",domains[i].name);
      for(k=domains[i].from;k<domains[i].to;++k)
      { printf("\tvirtual void visit(%s_node*) { }\n",structs[k].name);
        printf("\tvoid visit(%s_node* n, void* r) { visit(n); }\n",structs[k].name);
      }
      printf("};\n");
    }
    for(i=nstructs_open;i<nstructs;++i)
    {
      printf("inline void %s_node::accept(%s_visitor* v, void* r) {\n",structs[i].name,structs[i].domain);
      printf("\tv->visit(this, r);\n}\n");
    }
    printf("}\nusing namespace ast;\n");
  }
  ndomains_open=ndomains;
  nstructs_open=nstructs;
}
#define ECHO { if(output_flg) { strcpy(output_buf+output_len,yytext); output_len+=yyleng; } else printf("%s",yytext); }
void printbuf(const char *fmt, ...)
{ va_list args1;
  va_start(args1, fmt);
  if(output_flg)
    output_len+=vsprintf(output_buf+output_len, fmt, args1);
  else
    vprintf(fmt, args1);
  va_end(args1);
}
%}
%option stack
%option nounistd
%option noyywrap
%x COMMENT RULE DOMAIN MATCH0 WITH DOMAIN1 DOMAIN2 DOMAIN3 MATCH1 RULE1 RULE2 
%x VISITOR VISITOR1 VISITOR2 VISITOR3 VISITOR0
%%
"//".* if(!nopenfiles) ECHO;
"/*" { if(!nopenfiles) ECHO; BEGIN(COMMENT); }
<COMMENT>\n  { if(!nopenfiles) ECHO; nline++; }
<COMMENT>"*/" { if(!nopenfiles) ECHO; BEGIN(INITIAL); }
<COMMENT>. if(!nopenfiles) ECHO;
[ \t] if(!nopenfiles) ECHO;
domain { domain_name[0]=0; 
         BEGIN(DOMAIN); 
       }
<DOMAIN>[a-zA-Z_][a-zA-Z_0-9]* {
          if(domain_name[0]!=0)
            error("Wrong domain operator 1");
          strcpy(domain_name,yytext);
    }
<DOMAIN>[ \t] ;
<DOMAIN>\n nline++;
<DOMAIN>"{" {
          if(domain_name[0]==0)
            error("Wrong domain operator 2");
          domains[ndomains].name=strdup(domain_name);
          domains[ndomains].from=nstructs;
          ndomains++;
          struct_name[0]=0;
          BEGIN(DOMAIN1);
         }
<DOMAIN>. error("Wrong domain operator 3");
<DOMAIN1>[ \t] ;
<DOMAIN1>\n nline++;
<DOMAIN1>"}" {
      if(!nopenfiles && !genhflg) printf("#line %d \"%s\"\n",nline,curr_filename);
      domains[ndomains-1].to=nstructs;
      BEGIN(INITIAL);
    }
<DOMAIN1>[a-zA-Z_][a-zA-Z_0-9]* { 
      if(struct_name[0]!=0)
        error("Wrong domain operator 4");
      strcpy(struct_name,yytext);
    }
<DOMAIN1>"(" {
      if(struct_name[0]==0)
        error("Wrong domain operator 5");
      type_name[0]=0;
      structs[nstructs].name=strdup(struct_name);
      structs[nstructs].domain=strdup(domain_name);
      BEGIN(DOMAIN2);
   }
<DOMAIN1>. error("Wrong domain operator 6");
<DOMAIN2>[a-zA-Z_][a-zA-Z_0-9]*("::"[a-zA-Z_][a-zA-Z_0-9]*)*("<"[^>\n]*">")?([ ]*"*")? { 
      if(type_name[0]!=0)
        error("Wrong domain operator 7");
      strcpy(type_name,yytext);
      arg_name[0]=0;
      BEGIN(DOMAIN3);
    }
<DOMAIN2>[ \t] ;
<DOMAIN2>\n nline++;
<DOMAIN2>")" { nstructs++;
               struct_name[0]=0;
               BEGIN(DOMAIN1);
             }
<DOMAIN2>. error("Wrong domain operator 8");
<DOMAIN3>[a-zA-Z_][a-zA-Z_0-9]* { 
      if(arg_name[0]!=0)
        error("Wrong domain operator 9");
      strcpy(arg_name,yytext);
    }
<DOMAIN3>"," { 
     if(arg_name[0]==0)
       sprintf(arg_name,"f%d_",structs[nstructs].nfields);
     structs[nstructs].types[structs[nstructs].nfields]=strdup(type_name);
     structs[nstructs].fields[structs[nstructs].nfields]=strdup(arg_name);
     ++structs[nstructs].nfields;
     type_name[0]=0;
     BEGIN(DOMAIN2);
    }
<DOMAIN3>")" { 
     if(arg_name[0]==0)
       sprintf(arg_name,"_%d",structs[nstructs].nfields);
     structs[nstructs].types[structs[nstructs].nfields]=strdup(type_name);
     structs[nstructs].fields[structs[nstructs].nfields]=strdup(arg_name);
     ++structs[nstructs].nfields;
     nstructs++;
     struct_name[0]=0;
     BEGIN(DOMAIN1);
    }
<DOMAIN3>[ \t] ;
<DOMAIN3>\n nline++;
<DOMAIN3>. error("Wrong domain operator 10");

visitor {
          ++match_level; 
          match_rules[match_level]=0; 
          match_else[match_level]=0; 
          match_opens[match_level]=0;
          match_type[match_level]=1;
          visitor_name[0]=0;
          domain_name[0]=0; 
          return_name[0]=0; 
          yy_push_state(VISITOR);
          output_len=0;
          output_flg=0;
        }
<VISITOR>[a-zA-Z_][a-zA-Z_0-9]* {
          if(visitor_name[0]!=0)
            error("Wrong visitor operator 1");
          strcpy(visitor_name,yytext);
    }
<VISITOR1>[a-zA-Z_][a-zA-Z_0-9]* {
          if(domain_name[0]!=0)
            error("Wrong visitor operator 3");
          strcpy(domain_name,yytext);
    }
<VISITOR2>[a-zA-Z_][a-zA-Z_0-9]*("::"[a-zA-Z_][a-zA-Z_0-9]*)*("<"[^>\n]*">")?([ ]*"*")? {
          if(return_name[0]!=0)
            error("Wrong visitor operator 3");
          strcpy(return_name,yytext);
    }
<VISITOR,VISITOR1,VISITOR2,VISITOR3>[ \t] ;
<VISITOR,VISITOR1,VISITOR2,VISITOR3>\n nline++;
<VISITOR>"<" {
            if(visitor_name[0]==0)
              error("Wrong visitor operator 2");
            BEGIN(VISITOR1); 
           }
<VISITOR1>"," { 
            if(domain_name[0]==0)
              error("Wrong visitor operator 5");
            BEGIN(VISITOR2); 
           }
<VISITOR2>">" { 
            if(return_name[0]==0)
              error("Wrong visitor operator 6");
            BEGIN(VISITOR3); 
           }
<VISITOR3>"{" {
            printf("struct %s_visitor:%s_Tvisitor<%s> {",visitor_name,domain_name,return_name);
            BEGIN(MATCH1);
           }
<VISITOR,VISITOR1,VISITOR2>. {  error("Wrong visitor operator 4");  }

<VISITOR0>visit {
        struct_name[0]=0;
        value_name[0]=0;
        BEGIN(RULE);
      }
<VISITOR0>. ECHO;
<VISITOR0>\n ++nline; ECHO;

<INITIAL,MATCH1>match {
        match_name[0]=0; 
        ++match_level; 
        match_rules[match_level]=0; 
        match_else[match_level]=0; 
        match_opens[match_level]=0;
        match_type[match_level]=0;
        yy_push_state(MATCH0); 
      }
<MATCH0>[^\n{]+ {
        strcat(match_name,yytext);
     }
<MATCH0>"{" {
        printbuf("{ auto _match%d=%s;\n",match_level,match_name);
        printbuf("#line %d \"%s\"\n",nline,curr_filename);
        BEGIN(MATCH1);
     }
<MATCH0>\n nline++;
<MATCH1>rule|visit {
        if(yytext[0]=='r' && match_type[match_level]==1 ||
           yytext[0]=='v' && match_type[match_level]==0 || 
           match_else[match_level]>0)
           error("Wrong rule/visit operator 0");
        if(match_rules[match_level]>0)
        {
          printbuf("}\n");
        }
        ++match_rules[match_level];
        struct_name[0]=0;
        value_name[0]=0;
        BEGIN(RULE); 
      }
<MATCH1>"{" { match_opens[match_level]++; if(!nopenfiles) ECHO; }
<MATCH1>"}" {
           --match_opens[match_level];
           if(match_opens[match_level]<0)
           { 
             if(match_type[match_level]==1) {
               if(match_rules[match_level]>0) 
                 printbuf("}\n");
               printf("} %s;\n",visitor_name);
               printf("%s",output_buf);
               output_flg=0;
             }
             else {
               if(match_rules[match_level]>0) {
                 printbuf("}\n");
               }
               if(merrflg) {
                  if(match_else[match_level]==0)
                  { printbuf("else MatchError(\"%s\",%d);\n",curr_filename,nline);
                  }
               }
               printbuf("}\n");
             }
             printbuf("#line %d \"%s\"\n",nline,curr_filename);
             --match_level;
             yy_pop_state();
           }
           else
           { if(!nopenfiles) ECHO;
           }
         }
<RULE>[ \t] ;
<RULE>[a-zA-Z_][a-zA-Z_0-9]* { 
        if(struct_name[0]!=0)
        {
          if(value_name[0]!=0)
            error("Wrong rule/visit operator 1");
          strcpy(value_name,yytext);
        }
        else
        {
          strcpy(struct_name,yytext);
        }
      }
<RULE>"(" { if(strcmp(struct_name,"nullptr")==0 || strcmp(struct_name,"default")==0)
              error("Syntax error rule nullptr/default");
            nfields=0; arg_name[0]=0; BEGIN(RULE1); 
          }
<RULE>":" { int i,j,flg=1;
          if(value_name[0]==0)
          {
            sprintf(value_name,"_node%d",match_level);
          }
          if(match_type[match_level]==0) {
            if(match_rules[match_level]>1) printbuf("else ");
            if(strcmp(struct_name,"nullptr")==0) {
              if(match_rules[match_level]!=1)
                error("Wrong order for rule nullptr");
              printbuf("if(_match%d==nullptr) {\n",match_level);
              flg=0;
            }
            else if(strcmp(struct_name,"default")==0) {
              flg=0; 
              printbuf("{\n");
              ++match_else[match_level];
            }
            else 
              printbuf("if(auto %s=dynamic_cast<%s_node*>(_match%d)) {\n",value_name,struct_name,match_level);
          }
          else {
            printf("%s visit(%s_node* %s);\n",return_name,struct_name,value_name);
            output_flg=1;
            printbuf("%s %s_visitor::visit(%s_node* %s) {\n",return_name,visitor_name,struct_name,value_name);
          }
          if(flg) {
            for(i=0;i<nstructs;++i)
              if(strcmp(structs[i].name,struct_name)==0) break;
            if(i==nstructs)
              error("Struct isn't found");
            for(j=0;j<structs[i].nfields && j<nfields;++j)
            { printbuf("auto &%s=%s->%s;\n",fields[j],value_name,structs[i].fields[j]);
            }
          }
          for(j=0;j<nfields;++j)
            free(fields[j]);
          printbuf("#line %d \"%s\"\n",nline,curr_filename);
          BEGIN(MATCH1);
         }
<RULE>\n nline++;
<RULE>. error("Wrong rule/visit operator 2");
<RULE1>")" { BEGIN(RULE); }
<RULE1>[ \t] ;
<RULE1>\n nline++;
<RULE1>[a-zA-Z_][a-zA-Z_0-9]* { 
        if(arg_name[0]!=0)
          error("Wrong rule/visit operator 3");
        strcpy(arg_name,yytext);
        BEGIN(RULE2);
      }
<RULE1>. error("Wrong rule/visit operator 4");
<RULE2>[ \t] ;
<RULE2>\n nline++;
<RULE2>"," { 
        if(arg_name[0]==0)
          error("Wrong rule/visit operator 5");
        fields[nfields++]=strdup(arg_name);
        arg_name[0]=0;
        BEGIN(RULE1);
      }
<RULE2>")" { 
        if(arg_name[0]==0)
          error("Wrong rule/visit operator 6");
        fields[nfields++]=strdup(arg_name);
        BEGIN(RULE);
      }
<RULE2>. error("Wrong rule/visit operator 7");

with { next_filename[0]=0; 
       with_exists=1;
       close_ast();
       BEGIN(WITH); 
     }
<WITH>[a-zA-Z_][a-zA-Z_0-9]* { 
           if(next_filename[0]!=0)
             error("Wrong with operator 1");
           strcpy(next_filename,yytext); 
           strcat(next_filename,".m"); 
      }
<WITH>; { 
          if(next_filename[0]==0)
            error("Wrong with operator 2");
          FILE *in=fopen(next_filename,"r");
          if(in==NULL)
            error("File isn't found");
          if(nopenfiles>=9) 
            error("Too many with operators");
          openfiles[nopenfiles].name=strdup(curr_filename);
          openfiles[nopenfiles].nline=nline;
          strcpy(curr_filename,next_filename);
          if(!nopenfiles)
          {
            next_filename[strlen(next_filename)-2]=0;
            printbuf("#include \"%s.h\"\n",next_filename);
          }
          ++nopenfiles;
          nline=1;
          yypush_buffer_state(yy_create_buffer( in, YY_BUF_SIZE ));
          BEGIN(INITIAL); }
<WITH>[ \t] ;
<WITH>(.|\n) { error("Wrong with operator 3"); }
<INITIAL,MATCH1>[a-zA-Z_][a-zA-Z_0-9]* { 
          close_ast();
          if(!nopenfiles) ECHO; 
          if(strcmp(yytext,"MatchError")==0) matcherr_exists=1;
         }
<INITIAL,MATCH1>[0-9A-Za-z]+ { close_ast();if(!nopenfiles) ECHO;}
<INITIAL,MATCH1>'([^\n'\\]|\\[xX][0-9A-Fa-f]+|\\[0-7]+|\\[a-z'\\\"])' { close_ast(); if(!nopenfiles) ECHO;}
<INITIAL,MATCH1>\"([^\n"\\]|\\[xX][0-9A-Fa-f]+|\\[0-7]+|\\[a-z'\\\"])*\" {close_ast();if(!nopenfiles) ECHO;}
<INITIAL,MATCH1>. if(!nopenfiles) ECHO;
<INITIAL,MATCH1>\n { nline++; if(!nopenfiles) ECHO; }
<<EOF>> { 
          close_ast();
          yypop_buffer_state(); 
          if (nopenfiles==0 || !YY_CURRENT_BUFFER ) 
            yyterminate(); 
          else
          { --nopenfiles; 
            nline=openfiles[nopenfiles].nline;
            strcpy(curr_filename,openfiles[nopenfiles].name);
            free(openfiles[nopenfiles].name);
          }
        }
%%
void usageerror()
{ fprintf(stderr,"Memphis v2.2: Tree Builder & Tree Walker Tool\n"
                 "Usage:\n\tmemphis2 [options] filename.m\n"
                 "Options:\n"
                 "\t-h - generate header file\n"
                 "\t-p - generate function astprint for domains\n"
                 "\t-ofullname - output to file with fullname;\n"
		 "\t\tdefault is filename.h with -h option and filename.cpp without it\n"
		 "\t-m - no generate match error if rule skipped\n");
  exit(1);
}
int main(int argc, char *argv[])
{ int i,j,k;
  curr_filename[0]=0;
  FILE *in;
  for(i=1;i<argc;++i)
  { if(strcmp(argv[i],"-h")==0)
      genhflg=1;
    else if(strcmp(argv[i],"-p")==0)
      genpflg=1;
    else if(strcmp(argv[i],"-m")==0)
      merrflg=0;
    else if(argv[i][0]=='-' && argv[i][1]=='o')
      strcpy(out_filename,argv[i]+2);
    else
      strcpy(curr_filename,argv[i]);
  }
  if(curr_filename[0]==0 || (in=fopen(curr_filename,"r"))==NULL)
    usageerror();
  else
  { int len;
    yyrestart(in);
    strcpy(next_filename,curr_filename);
    len=strlen(next_filename);
    if(len<=2 || next_filename[len-2]!='.')
      usageerror();
    strcpy(next_filename+len-2,genhflg?".h":".cpp");
    if(out_filename[0])
      strcpy(next_filename,out_filename);
    freopen(next_filename,"w",stdout);
    if(genhflg)
    { 
      strcpy(next_filename+len-2,"");
      printf("#ifndef %s_H\n",next_filename);
      printf("#define %s_H\n",next_filename);
    }
    else
      printf("void MatchError(const char *,int);\n");
    printf("#line %d \"%s\"\n",nline,curr_filename);
    yylex();
    if(genhflg)
    { 
      printf("#endif\n");
    }
    else
    { 
      if(genpflg && ndomains>0)
      {
      printf("namespace ast {\n");
      printf("#ifndef ASTPRINT_BUILTIN\n"
             "#define ASTPRINT_BUILTIN 1\n"
             "static void print_char(std::ostream &s, char v)\n"
             "{ if(v=='\\n') s<<\"\\\\n\";\n"
             "  else if(v=='\\'' || v=='\\\\' || v=='\\\"') s<<'\\\\'<<v;\n"
             "  else s<<v;\n"
             "}\n"
             "static void print_indent(std::ostream &s, int i)\n"
             "{ s<<\'\\n\';\n"
             "  if(i) { s.width(i); s<<' '; }\n"
             "}\n"
             "static int astprint(std::ostream &s, char v, int, const char* p)\n"
             "{ s<<\"'\";\n"
             "  print_char(s,v);\n"
             "  s<<\"'\";\n"
             "  if(p) s<<p;\n"
             "  return 0;\n"
             "}\n"
             "static int astprint(std::ostream &s, const std::string &v, int, const char* p)\n"
             "{ s<<\"\\\"\";\n"
             "  for(auto x:v) print_char(s,x);\n"
             "  s<<\"\\\"\";\n"
             "  if(p) s<<p;\n"
             "  return 0;\n"
             "}\n"
             "template <typename T> int astprint(std::ostream &s, T v, int, const char* p){ s<<v; if(p) s<<p; return 0; }\n"
             "#endif\n"
             );
      for(i=0;i<ndomains;++i)
      { 
          printf("int astprint(std::ostream& s, %s v, int i, const char* p) {\n",domains[i].name);
          printf("  int r=0;\n"
                 "  if(!v) s<<\"nullptr\";\n");
          for(k=domains[i].from;k<domains[i].to;++k)
          {  
              printf("  else if(auto _v=dynamic_cast<%s_node*>(v)) {\n",structs[k].name);
              if(structs[k].nfields>0)
              {  printf("    print_indent(s,i);\n"
                        "    s<<\"%s(\";\n",structs[k].name);
                 for(j=0;j<structs[k].nfields;++j)
                 printf("    r+=astprint(s,_v->%s,i+2,%s);\n",structs[k].fields[j],(j<structs[k].nfields-1)?"\",\"":"nullptr");
                 printf("    if(r) print_indent(s,i);\n"
  		        "    s<<\")\";\n"
  		        "    ++r;\n");
              }
              else printf("    s<<\"%s()\";\n",structs[k].name);
              printf("  }\n");
          }
          printf("  if(p) s<<p;\n"
                 "  return r;\n"
                 "}\n");
      }
      printf("}\n");
      }
      if(!matcherr_exists && merrflg)
      { if(!genpflg) printf("#include <iostream>\n");
        printf("#include <cstdlib>\nvoid MatchError(const char *s,int n){\n  std::cerr<<\"Match error at \"<<s<<\" line \"<<n<<\"\\n\";\n  std::exit(1);\n}\n");
      }
    }
  }
  return 0;
}
