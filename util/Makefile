C = gcc
AR = ar
CFLAGS = -Wall -pedantic -std=c11 -g
ARFLAGS = -cvq

LIBNAME = libtseutil.a
OBJS = hashtable.o web.o file.o 
SRCS = hashtable.c web.c file.c
SRCSH = hashtable.h web.h file.h


tselib: $(OBJS)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJS)

$(OBJS): $(SRCS) $(SRCH)
	$(CC) $(CFLAGS) -c $(SRCS)
clean:
	rm -f *~
	rm -f *.o
	rm -f *.a
