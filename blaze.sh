bison -d syntax.y
flex lexical.l
gcc tree.h tree.c syntax.tab.c -lfl -ly -o parser