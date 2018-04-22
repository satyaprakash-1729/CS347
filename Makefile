#
# makefile for ccalc
#
all: parser

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h ccalc.h type_all.h
	gcc -g -o parser parser.tab.c lex.yy.c ccalc.c

clean:
	rm -f parser parser.tab.c parser.tab.h lex.yy.c
