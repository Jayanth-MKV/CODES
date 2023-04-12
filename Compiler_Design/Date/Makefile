datecalc: lexical.o parser.o date.o
	g++ -o datecalc lexical.o parser.o date.o -ll -ly
lexical.o: lex.yy.c
	g++ -c lex.yy.c -o lexical.o
lex.yy.c: newcalc.l y.tab.h Date.hh
	lex newcalc.l 
parser.o: y.tab.c 
	g++ -c y.tab.c -o parser.o
y.tab.c y.tab.h: newcalc.y Date.hh
	yacc -d newcalc.y
date.o: Date.cpp
	g++ -c Date.cpp -o date.o
clean: *.o
	rm *.o

