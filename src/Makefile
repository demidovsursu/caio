ifndef TARGET
TARGET = ../release
endif

.PHONY : all clean install test

all: $(TARGET)/caio.exe

$(TARGET)/caio.exe $(TARGET)/y.tab.cpp $(TARGET)/y.tab.h $(TARGET)/domains.h $(TARGET)/gener.cpp $(TARGET)/lex.yy.cpp: | $(TARGET)

$(TARGET)/lex.yy.o: | $(TARGET)/lex.yy.cpp

$(TARGET)/y.tab.o: | $(TARGET)/y.tab.cpp

$(TARGET):
	mkdir $(TARGET)

$(TARGET)/caio.exe: $(TARGET)/lex.yy.o $(TARGET)/y.tab.o $(TARGET)/gener.o
	g++ -std=c++17 -Wl,--stack,83886080 -o $(TARGET)/caio $(TARGET)/gener.o $(TARGET)/y.tab.o $(TARGET)/lex.yy.o ../../lib/initansicp.o -lreflex 

$(TARGET)/lex.yy.cpp: caio.lex Makefile
	reflex --flex --bison -o$(TARGET)/lex.yy.cpp $<

$(TARGET)/y.tab.cpp $(TARGET)/y.tab.h: caio.grm Makefile
	bison -o$(TARGET)/y.tab.cpp -d $<
	$(if $(wildcard $(TARGET)/y.tab.h),del $(TARGET)\y.tab.h)
	ren $(TARGET)\y.tab.hpp y.tab.h

$(TARGET)/domains.h: domains.m Makefile
	memphis2 -h -p -o$@ $<

$(TARGET)/gener.cpp: gener.m Makefile
	memphis2 -p -o$@ $<

$(TARGET)/%.o: $(TARGET)/%.cpp $(TARGET)/y.tab.h $(TARGET)/domains.h caio/asttypes.h caio/astprint.h
	g++ -std=c++17 -O1 -o $@ -I. -I$(TARGET) -c $<
