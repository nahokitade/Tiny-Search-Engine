CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g

# makes crawler executables
indexer: indexer.c web.o hashtable.o file.o
	$(CC) $(CFLAGS) -o indexer indexer.c web.o hashtable.o file.o

# makes the curl handling .o file
web.o: web.c web.h
	$(CC) $(CFLAGS) -c web.c

# makes the hash table structure
hashtable.o: hashtable.c hashtable.h file.o
	$(CC) $(CFLAGS) -c hashtable.c file.o

file.o: file.c file.h
	$(CC) $(CFLAGS) -c file.c

# makes a hashTableTest executable that will test the hash table structure
hashTableTest: hashTableTest.c hashtable.o
	$(CC) $(CFLAGS) -o hashTableTest hashTableTest.c hashtable.o
	hashTableTest

# cleans the directory to make a fresh crawler executable.
clean:
	rm -f *~
	rm -f ./indexer
	rm -f *.o
