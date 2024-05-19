# Libraries to include (if any)
LIBS=-lm 

# Compiler flags
CFLAGS=-Wall -Wextra -ggdb -std=c11 -pedantic -w

# Indentation flags
# IFLAGS=-br -brs -brf -npsl -ce -cli4 -bli4 -nut
IFLAGS=-linux -brs -brf -br

# Name of the executable
DEBUG_DIR=debug
PROGRAM=$(DEBUG_DIR)/store.exe
# Prefix for the gengetopt file (if gengetopt is used)
PROGRAM_OPT=args

CC=gcc

# Object files required to build the executable
OBJ_DIR=obj
PROGRAM_OBJS= main.o gestaoMenu.o gestaoTestagem.o gestaoConfinamentos.o funcoesGenericas.o $(PROGRAM_OPT).o
PROGRAM_OBJS_WITH_DIR= $(OBJ_DIR)/main.o $(OBJ_DIR)/gestaoMenu.o $(OBJ_DIR)/gestaoTestagem.o $(OBJ_DIR)/gestaoConfinamentos.o $(OBJ_DIR)/funcoesGenericas.o $(OBJ_DIR)/$(PROGRAM_OPT).o

# Clean and all are not files
.PHONY: clean all docs indent debugon

all: $(PROGRAM)

# activate optimization (-O...)
OPTIMIZE_FLAGS=-O2 # possible values (for gcc): -O2 -O3 -Os -Ofast
optimize: CFLAGS += $(OPTIMIZE_FLAGS)
optimize: $(PROGRAM)

$(PROGRAM): $(PROGRAM_OBJS)
	$(CC) -o $@ $(PROGRAM_OBJS_WITH_DIR) $(LIBS) $(LDFLAGS)

# Dependencies
main.o: main.c gestaoTestagem.h gestaoConfinamentos.h funcoesGenericas.h $(PROGRAM_OPT).h
$(PROGRAM_OPT).o: $(PROGRAM_OPT).c $(PROGRAM_OPT).h

debug.o: debug.c debug.h
memory.o: memory.c memory.h
gestaoTestagem.o: gestaoTestagem.c gestaoTestagem.h gestaoConfinamentos.h
gestaoMenu.o: gestaoMenu.c funcoesGenericas.h gestaoTestagem.h
gestaoConfinamentos.o: gestaoTestagem.c funcoesGenericas.h gestaoConfinamentos.h gestaoTestagem.h
funcoesGenericas.o: funcoesGenericas.c funcoesGenericas.h

# disable warnings from gengetopt generated files
$(OBJ_DIR)/$(PROGRAM_OPT).o: $(PROGRAM_OPT).c $(PROGRAM_OPT).h
	$(CC) -ggdb -std=c11 -pedantic -c $< -o $@

#how to create an object file (.o) from C file (.c)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

# Generates command line arguments code from gengetopt configuration file
$(PROGRAM_OPT).c $(PROGRAM_OPT).h: $(PROGRAM_OPT).ggo
	gengetopt < $(PROGRAM_OPT).ggo --file-name=$(PROGRAM_OPT)

clean:
	rm -f core.* *~ *.bak $(PROGRAM_OPT).h $(PROGRAM_OPT).c
	rm -rf $(OBJ_DIR)/* $(DEBUG_DIR)/*

docs: Doxyfile
	doxygen Doxyfile

Doxyfile:
	doxygen -g Doxyfile

# entry to create the list of dependencies
depend:
	$(CC) -MM *.c

# entry 'indent' requires the application indent (sudo apt-get install indent)
indent:
	indent $(IFLAGS) *.c *.h

# entry to run the pmccabe utility (computes the "complexity" of the code)
# Requires the application pmccabe (sudo apt-get install pmccabe)
pmccabe:
	pmccabe -v *.c

# entry to run the cppcheck tool
cppcheck:
	cppcheck --enable=all --verbose *.c *.h
