compile:
	bison -d syntax.y
	gcc -Wall syntax.tab.c -o parser.out
edit:
	vim syntax.y
run:
	./parser.out test.txt
