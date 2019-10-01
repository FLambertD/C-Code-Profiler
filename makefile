#KUOCh Maxime

CC=gcc
CFLAGS=-Wall -lMLV -lrt
OBJ=Main.o Arbre.o draw.o Recap.o
BIN=bin/
SRC=src/
INCLUDE=include/

all: $(BIN)myprofiler

$(BIN)myprofiler: $(BIN)Main.o $(BIN)Arbre.o $(BIN)draw.o $(BIN)Recap.o $(BIN)Menu.o
	$(CC) -o $(BIN)myprofiler $(BIN)Main.o $(BIN)Arbre.o $(BIN)draw.o $(BIN)Recap.o $(BIN)Menu.o $(CFLAGS)

$(BIN)Arbre.o: $(SRC)Arbre.c $(INCLUDE)macro_profiler.h $(INCLUDE)Arbre.h
$(BIN)draw.o: $(SRC)draw.c $(INCLUDE)macro_profiler.h $(INCLUDE)draw.h $(INCLUDE)Arbre.h
$(BIN)Recap.o: $(SRC)Recap.c $(INCLUDE)macro_profiler.h $(INCLUDE)Recap.h $(INCLUDE)Arbre.h
$(BIN)Menu.o: $(SRC)Menu.c $(INCLUDE)macro_profiler.h $(INCLUDE)Menu.h
$(BIN)Main.o: $(SRC)Main.c $(INCLUDE)macro_profiler.h $(INCLUDE)Arbre.h $(INCLUDE)draw.h $(INCLUDE)Recap.h $(INCLUDE)Menu.h

$(BIN)%.o: $(SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)	

clean:
	rm -f $(BIN)*.o
	rm -f $(BIN)myprofiler
