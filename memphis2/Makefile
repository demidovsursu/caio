.PHONY : all clean install

memphis2.exe: memphis2.lex
	flex memphis2.lex
	gcc -o memphis2 lex.yy.c
	del lex.yy.c
