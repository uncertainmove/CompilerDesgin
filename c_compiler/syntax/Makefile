compile:
	gcc -Wall syntax.tab.c -o parser
edit:
	vim syntax.y
run:
	./parser test.c
debug:
	bison -d -t syntax.y
nodebug:
	bison -d -v syntax.y
