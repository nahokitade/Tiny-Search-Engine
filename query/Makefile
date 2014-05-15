# Makefile for the query in TSE project 

CC=gcc
CFLAGS= -Wall -pedantic -std=c11 -g
CODEDIR = ./src/

# files in the query src directory that query depends on
SOURCES= $(CODEDIR)query.c $(CODEDIR)queryProcess.c $(CODEDIR)queryProcess.h $(CODEDIR)LLMergeSort.c $(CODEDIR)LLMergeSort.h $(CODEDIR)SinLL.c $(CODEDIR)SinLL.h
CFILES=$(CODEDIR)query.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c $(CODEDIR)SinLL.c

UTILDIR=../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a	# library that query depends on

# files in util that query depends on
UTILC=$(UTILDIR)hashtable.c $(UTILDIR)web.c $(UTILDIR)file.c
UTILH=$(UTILC:.c=.h)

# make query depending on the sources in its directory, and the library for TSE.
query:$(SOURCES) $(UTILLIB)
	$(CC) $(CFLAGS) -o query $(CFILES) -I$(UTILDIR) -L$(UTILDIR) $(UTILFLAG)

# make the utility library
$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make;

clean:
	rm -f *~
	rm -f ./query
	rm -f *.o
