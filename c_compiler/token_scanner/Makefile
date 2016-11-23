compile:
	flex token_scanner.l
link:
	g++ -Wall lex.yy.c -o token_scanner.out
edit:
	vim token_scanner.l
clear:
	rm lex.yy.c
run:
	./token_scanner.out test.c
