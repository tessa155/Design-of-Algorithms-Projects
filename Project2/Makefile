## Student Name : Tessa(Hyeri) Song
## Login id : songt
## Wed 13 Apr 2016
##
## Makefile 
##


OBJ     = main.o set.o graph.o heap.o 
CC      = gcc
EXE     = ./simulation
CFLAGS  = -Wall

assn1:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE) 

main.o: graph.h heap.h set.h Makefile
set.o: set.h graph.h heap.h
graph.o: graph.h 
heap.o: heap.h


