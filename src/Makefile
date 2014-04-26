CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -g

# luckily, make has comments too!  

crawler: crawler.c list.o web.o hashtable.o common.o
	$(CC) $(CFLAGS) -o crawler crawler.c list.o web.o hashtable.o common.o -lcurl

crawlerDebug: crawler.c list.o web.o hashtable.o common.o
	$(CC) $(CFLAGS) -o crawlerDebug crawler.c list.o web.o hashtable.o common.o -lcurl -DDEBUGGING

list.o: list.c list.h common.h
	$(CC) $(CFLAGS) -c list.c

web.o: web.c web.h common.h
	$(CC) $(CFLAGS) -c web.c

hashtable.o: hashtable.c hashtable.h common.h
	$(CC) $(CFLAGS) -c hashtable.c

common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c

listTest: listTest.c list.o
	$(CC) $(CFLAGS) -o listTest listTest.c list.o
	listTest;

hashTableTest: hashTableTest.c hashtable.o
	$(CC) $(CFLAGS) -o hashTableTest hashTableTest.c hashtable.o
	hashTableTest

clean:
	rm -f *~
	rm -f *#
	rm -f ./crawler
	rm -f *.o
