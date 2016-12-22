parser.out : main.o absyn.o semant.o frame.o target.o
	gcc -Wall main.o absyn.o semant.o frame.o target.o -o parser.out
main.o : main.c main.h syntax.tab.c lex.yy.c 
	gcc -Wall -c main.c
absyn.o : absyn.c absyn.h
	gcc -Wall -c absyn.c
semant.o : semant.c semant.h
	gcc -Wall -c semant.c
frame.o : frame.c frame.h
	gcc -Wall -c frame.c
target.o : target.c target.h
	gcc -Wall -c target.c
lex.yy.c : scanner.l syntax.tab.h
	flex scanner.l
syntax.tab.c : syntax.y
	bison -d syntax.y
run:
	./parser.out test1.c
	gcc test.s -o test.out
clear:
	rm main.o
	rm absyn.o
	rm semant.o 
	rm frame.o
	rm target.o 
	rm lex.yy.c
	rm syntax.tab.h
	rm syntax.tab.c
	rm parser.out
edit:
	vim target.c 
