CC=gcc
CFLAGS= -Wall -pedantic -std=c11 -g
CODEDIR = ./src/
SOURCES= $(CODEDIR)query.c $(CODEDIR)queryProcess.c $(CODEDIR)queryProcess.h $(CODEDIR)LLMergeSort.c $(CODEDIR)LLMergeSort.h $(CODEDIR)SinLL.c $(CODEDIR)SinLL.h
CFILES=$(CODEDIR)query.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c $(CODEDIR)SinLL.c

UTILDIR=../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a
UTILC=$(UTILDIR)hashtable.c $(UTILDIR)web.c $(UTILDIR)file.c
UTILH=$(UTILC:.c=.h)

query:$(SOURCES) $(UTILLIB)
	$(CC) $(CFLAGS) -o query $(CFILES) -I$(UTILDIR) -L$(UTILDIR) $(UTILFLAG)

$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make;

clean:
	rm -f *~
	rm -f ./query
	rm -f *.o
