CFLAGS = -g -Wall -I.

SRC=src
INCLUDE=include
BIN=bin

yaccfile = $(SRC)/compiler.y
lexfile  = $(SRC)/compiler.l 
cfiles = $(wildcard $(SRC)/*.c)
cfiles += $(SRC)/y.tab.c $(SRC)/lex.yy.c
objs  = $(cfiles:.c=.o)

all : $(BIN)/compiler

$(SRC)/y.tab.c $(SRC)/y.tab.h : $(yaccfile)
	yacc -v -d -o $(SRC)/y.tab.c $<

$(SRC)/lex.yy.c : $(lexfile) $(SRC)/y.tab.h
	lex -o $@ $<

$(SRC)/%.o : $(SRC)/%.c 
	gcc $(CFLAGS) -c $< -o $@

$(BIN)/compiler:$(objs)
	mkdir -p ./$(BIN)
	gcc -g -o $@ $^ -lm

clean:
	rm -f $(SRC)/*.o $(SRC)/y.tab.c $(SRC)/y.tab.h $(SRC)/lex.yy.c $(BIN)/compiler
