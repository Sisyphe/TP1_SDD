#Makefile pour les programmes

# Commandes
CC = cc
GCC = gcc
CFLAGS = -g -Wall -ansi -pedantic -Wextra
LFLAGS =

EXE = tp1

all: $(EXE)

# Liste des programmes
tp1: main.o calendar.o handler.o tools.o
calendar.o: calendar.c calendar.h tools.h struct.h
handler.o: handler.c handler.h calendar.h
tools.o: tools.c tools.h

#Compilation Exe
$(EXE) :
	$(GCC) $^ -o $@ $(LFLAGS)

#Compilation Modules
.o : .c
	$(GCC) -o $@ -c $< $(CFLAGS)

#Pour faire le ménage
clean:
	rm -f *.o *~ $(EXE)

