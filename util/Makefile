# Makefile for the Util directory. Creates a library on run that contains functions needed to make TSE.

C = gcc
AR = ar
CFLAGS = -Wall -pedantic -std=c11 -g
ARFLAGS = -cvq

LIBNAME = libtseutil.a
OBJS = hashtable.o web.o file.o 
SRCS = hashtable.c web.c file.c
SRCSH = hashtable.h web.h file.h

# creates library
tselib: $(SRCS) $(SRCH) $(OBJS)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJS)

# creates all o files that the library depends on.
$(OBJS): $(SRCS) $(SRCH)
	$(CC) $(CFLAGS) -c $(SRCS)

# cleans all .o and .a files created
clean:
	rm -f *~
	rm -f *.o
	rm -f *.a
