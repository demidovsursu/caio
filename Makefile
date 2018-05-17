EXE =

.PHONY : all samples rebuild

all: bin/caio$(EXE)

samples : bin/basic$(EXE) bin/calc$(EXE)

bin/caio$(EXE) : build/caio.lex build/caio.grm build/caio.h build/caio.cpp
	reflex --flex -obuild/caio.lex.cpp build/caio.lex
	bison -obuild/caio.grm.cpp build/caio.grm
	g++ -std=c++17 -I. -Ibuild -o bin/caio build/caio.cpp build/caio.grm.cpp build/caio.lex.cpp -lreflex

rebuild : bin/caio$(EXE)
	bin/caio -obuild/ src/caio.caio

bin/basic$(EXE) : example/basic.caio bin/caio$(EXE)
	bin/caio -obuild/ example/basic.caio
	reflex --flex -obuild/basic.lex.cpp build/basic.lex
	bison -obuild/basic.grm.cpp build/basic.grm
	g++ -std=c++17 -I. -Ibuild -o bin/basic build/basic.cpp build/basic.grm.cpp build/basic.lex.cpp -lreflex

bin/calc$(EXE) : example/calc.caio bin/caio$(EXE)
	bin/caio -obuild/ example/calc.caio
	reflex --flex -obuild/calc.lex.cpp build/calc.lex
	bison -obuild/calc.grm.cpp build/calc.grm
	g++ -std=c++17 -I. -Ibuild -o bin/calc build/calc.cpp build/calc.grm.cpp build/calc.lex.cpp -lreflex

% : %.cpp

%.o : %.cpp
