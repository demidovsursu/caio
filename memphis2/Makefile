.PHONY : all clean install

all: memphis2.exe

install:
	move /y memphis2.exe ..\..\bin

clean:
	-del memphis2.exe

memphis2.exe: memphis2.lex
	flex memphis2.lex
	gcc -o memphis2 lex.yy.c
	del lex.yy.c
