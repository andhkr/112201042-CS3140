# Define variables for the yacc and lex files
YACC = yacc
LEX = flex
CC = gcc
YFLAGS = -d
LFLAGS =
CFLAGS = -Wall -g
LIBS = -lfl

# Target executable
TARGET = calculator

# Intermediate files
YACC_SRCS = calculator.y
LEX_SRCS = calculatorlex.l
YACC_OBJS = y.tab.c y.tab.h
LEX_OBJS = lex.yy.c

# Final object files
OBJS = y.tab.o lex.yy.o

# Default target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Generate yacc source files
y.tab.c y.tab.h: $(YACC_SRCS)
	$(YACC) $(YFLAGS) $(YACC_SRCS)

# Generate lex source file
lex.yy.c: $(LEX_SRCS) y.tab.h
	$(LEX) $(LEX_SRCS)

# Compile yacc object file
y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c

# Compile lex object file
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS) y.tab.* lex.yy.c
