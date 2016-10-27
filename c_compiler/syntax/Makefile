compile:
	gcc syntax.tab.c -lfl -o parser
edit:
	vim syntax.y
run:
	./parser test.txt
debug:
	bison -d -t syntax.y
nodebug:
	bison -d syntax.y
