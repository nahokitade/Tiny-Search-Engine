C = gcc
AR = ar
CFLAGS = -Wall -pedantic -std=c11 -g
ARFLAGS = -cvq

LIBNAME = libtseutil.a
OBJS = hashtable.o web.o file.o list.o
CODEDIRIND = ../indexer/src/
CODEDIRCRAWL = ../crawler/src/
SRCS = $(CODEDIRIND)hashtable.c $(CODEDIRIND)web.c $(CODEDIRIND)file.c $(CODEDIRCRAWL)list.c
SRCSH = $(CODEDIRIND)hashtable.h $(CODEDIRIND)web.h $(CODEDIRIND)file.h $(CODEDIRCRAWL)list.h


tselib: $(OBJS)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJS)

$(OBJS): $(SRCS) $(SRCH)
	$(CC) $(CFLAGS) -c $(SRCS)

