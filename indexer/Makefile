CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g

OBJS = hashtable.o web.o file.o
CODEDIR = ./src/
SRCS = $(CODEDIR)hashtable.c $(CODEDIR)web.c $(CODEDIR)file.c 
SRCSH = $(CODEDIR)hashtable.h $(CODEDIR)web.h $(CODEDIR)file.h
MAINPROGC = $(CODEDIR)indexer.c
MAINPROGEX = indexer

UTILDIR=../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a

# makes indexer executables
$(MAINPROGEX): $(MAINPROGC) $(OBJS)
	$(CC) $(CFLAGS) -o $(MAINPROGEX) $(MAINPROGC) $(OBJS) 

# makes the hash table structure
$(OBJS): $(SRCS) $(SRCH) $(UTILLIB)
	$(CC) $(CFLAGS) -c $(SRCS) -L$(UTILDIR) $(UTILFLAG)

$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make;

# makes a hashTableTest executable that will test the hash table structure
hashTableTest: $(CODEDIR)hashTableTest.c hashtable.o
	$(CC) $(CFLAGS) -o hashTableTest $(CODEDIR)hashTableTest.c hashtable.o
	hashTableTest

# cleans the directory to make a fresh crawler executable.
clean:
	rm -f *~
	rm -f ./indexer
	rm -f *.o
