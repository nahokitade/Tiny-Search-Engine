CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g
UTILDIR=../../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a

# makes crawler executables
crawler: crawler.c list.o web.o hashtable.o common.o
	$(CC) $(CFLAGS) -o crawler crawler.c list.o web.o hashtable.o common.o -lcurl 

# makes crawlerDebug executable that is crawler but with debugging information
crawlerDebug: crawler.c list.o web.o hashtable.o common.o
	$(CC) $(CFLAGS) -o crawlerDebug crawler.c list.o web.o hashtable.o common.o -lcurl -DDEBUGGING

# makes the Doubly Linked List structure
list.o: $(UTILLIB) list.h common.h
	$(CC) $(CFLAGS) -c list.c -L$(UTILDIR) $(UTILFLAG)

# makes the curl handling .o file
web.o: web.c web.h common.h
	$(CC) $(CFLAGS) -c web.c

# makes the hash table structure
hashtable.o: hashtable.c hashtable.h common.h
	$(CC) $(CFLAGS) -c hashtable.c

# makes the header common to all files in crawler
common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c

# makes a listTest executable that will test the list structure
listTest: listTest.c list.o
	$(CC) $(CFLAGS) -o listTest listTest.c list.o
	listTest;

# makes a hashTableTest executable that will test the hash table structure
hashTableTest: hashTableTest.c hashtable.o
	$(CC) $(CFLAGS) -o hashTableTest hashTableTest.c hashtable.o
	hashTableTest

# executest the crawlerTest.sh script to test the crawler.
crawlerTest: crawler
	crawlerTest.sh &

$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make;

# cleans the directory to make a fresh crawler executable.
clean:
	rm -f *~
	rm -f *#
	rm -f ./crawler
	rm -f *.o
