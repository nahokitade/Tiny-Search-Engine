CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g

CODEDIR = ./src/
MAINPROGC = $(CODEDIR)indexer.c
MAINPROGEX = indexer

UTILDIR=../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a
UTILC=$(UTILDIR)file.c $(UTILDIR)hashtable.c $(UTILDIR)web.c
UTILH=$(UTILC:.c=.h)

# makes indexer executables
$(MAINPROGEX): $(MAINPROGC) $(UTILLIB)
	$(CC) $(CFLAGS) -o $(MAINPROGEX) $(MAINPROGC) -I$(UTILDIR) -L$(UTILDIR) $(UTILFLAG) 

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
