# Makefile for the unit testing of query's functions

CC=gcc
CFLAGS= -Wall -pedantic -std=c11 -g
TESTCODEDIR = ./
CODEDIR=../src/

# Sources to be depended when making MergeSortTest
MSTSOURCES=$(TESTCODEDIR)MergeSortTest.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.h $(CODEDIR)queryProcess.h
MSTCFILES=$(TESTCODEDIR)MergeSortTest.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c

# Sources to be depended when making queryProcessTest
QPTSOURCES=$(TESTCODEDIR)queryProcessTest.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.h $(CODEDIR)queryProcess.h
QPTCFILES=$(TESTCODEDIR)queryProcessTest.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c

# Sources to be depended when making SinLLTest
SLLTFILES=$(TESTCODEDIR)SinLLTest.c $(CODEDIR)SinLL.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.h $(CODEDIR)queryProcess.h
SLLTCFILES=$(TESTCODEDIR)SinLLTest.c $(CODEDIR)SinLL.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c

# Sources and library that the files we are testing depends on
UTILDIR=../../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a
UTILC=$(UTILDIR)hashtable.c $(UTILDIR)web.c $(UTILDIR)file.c
UTILH=$(UTILC:.c=.h)

# updates and makes all the test
test: MergeSortTest queryProcessTest SinLLTest

MergeSortTest: $(MSTSOURCES) $(UTILLIB)
	$(CC) $(CFLAGS) -o MergeSortTest $(MSTCFILES) -I$(UTILDIR) -I$(CODEDIR) -L$(UTILDIR) $(UTILFLAG)

queryProcessTest: $(QPTSOURCES) $(UTILLIB)
	$(CC) $(CFLAGS) -o queryProcessTest $(QPTCFILES) -I$(UTILDIR) -I$(CODEDIR) -L$(UTILDIR) $(UTILFLAG)

SinLLTest: $(SLLTFILES)  $(UTILLIB)
	$(CC) $(CFLAGS) -o SinLLTest $(SLLTCFILES) -I$(UTILDIR) -I$(CODEDIR) -L$(UTILDIR) $(UTILFLAG)

$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make;

clean:
	rm -f *~
	rm -f ./queryProcessTest
	rm -f ./SinLLTest
	rm -f ./MergeSortTest
	rm -f *.o
