scanner.exe : scanner.o
	gcc -g -Wall -std=c99 -o scanner.exe
scanner.o : lex.yy.c tokens.h
	gcc -g -Wall -std=c99 -c lex.yy.c
