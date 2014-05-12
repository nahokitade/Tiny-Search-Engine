CC=gcc
CFLAGS= -Wall -pedantic -std=c11 -g
CODEDIR = ./src/
SOURCES= $(CODEDIR)query.c $(CODEDIR)queryProcess.c $(CODEDIR)query.h $(CODEDIR)queryProcess.h $(CODEDIR)LLMergeSort.c $(CODEDIR)LLMergeSort.h $(CODEDIR)SinLL.c $(CODEDIR)SinLL.h
CFILES=$(CODEDIR)query.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c $(CODEDIR)SinLL.c

UTILDIR=../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a
UTILC=$(UTILDIR)hashtable.c
UTILH=$(UTILC:.c=.h)

#querg:$(SOURCES) $(UTILH) $(UTILLIB)
#	$(CC) $(CFLAGS) -o query $(CFILES) -L$(UTILDIR) $(UTILFLAG)

$(UTILLIB): 
	cd $(UTILDIR); make;

LLMergeSort.o: $(CODEDIR)LLMergeSort.c $(CODEDIR)LLMergeSort.h $(UTILLIB)
	$(CC) $(CFLAGS) -c $(CODEDIR)LLMergeSort.c -L$(UTILDIR) $(UTILFLAG)

queryProcess.o: $(CODEDIR)queryProcess.c $(CODEDIR)queryProcess.h $(UTILLIB)
	$(CC) $(CFLAGS) -c $(CODEDIR)queryProcess.c -L$(UTILDIR) $(UTILFLAG)

SinLL.o: $(CODEDIR)SinLL.c $(CODEDIR)SinLL.h $(UTILLIB)
	$(CC) $(CFLAGS) -c $(CODEDIR)SinLL.c -L$(UTILDIR) $(UTILFLAG)

MergeSortTest: $(CODEDIR)MergeSortTest.c LLMergeSort.o queryProcess.o $(UTILLIB)
	$(CC) $(CFLAGS) -o MergeSortTest $(CODEDIR)MergeSortTest.c LLMergeSort.o queryProcess.o -L$(UTILDIR) $(UTILFLAG)

queryProcessTest: $(CODEDIR)queryProcessTest.c LLMergeSort.o queryProcess.o $(UTILLIB)
	$(CC) $(CFLAGS) -o queryProcessTest $(CODEDIR)queryProcessTest.c LLMergeSort.o queryProcess.o -L$(UTILDIR) $(UTILFLAG)

SinLLTest: $(CODEDIR)SinLLTest.c SinLL.o LLMergeSort.o queryProcess.o $(UTILLIB)
	$(CC) $(CFLAGS) -o SinLLTest $(CODEDIR)SinLLTest.c SinLL.o LLMergeSort.o queryProcess.o -L$(UTILDIR) $(UTILFLAG)

clean:
	rm -f *~
	rm -f ./indexer
	rm -f *.o
