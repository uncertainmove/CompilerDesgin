parser.out : main.o
	gcc -Wall main.o -o parser.out
main.o : main.c main.h syntax.tab.c lex.yy.c
	gcc -Wall -c main.c
lex.yy.c : scanner.l syntax.tab.h
	flex scanner.l
syntax.tab.c : syntax.y
	bison -d syntax.y
run:
	./parser.out test.c
clear:
	rm main.o
	rm lex.yy.c
	rm syntax.tab.h
	rm syntax.tab.c
	rm parser.out
edit:
	vim main.c
