CC=gcc
CFLAGS= -Wall -pedantic -std=c11 -g
TESTCODEDIR = ./
CODEDIR=../src/

MSTSOURCES=$(TESTCODEDIR)MergeSortTest.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.h $(CODEDIR)queryProcess.h
MSTCFILES=$(TESTCODEDIR)MergeSortTest.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c

QPTSOURCES=$(TESTCODEDIR)queryProcessTest.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.h $(CODEDIR)queryProcess.h
QPTCFILES=$(TESTCODEDIR)queryProcessTest.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.c

SLLTFILES=$(TESTCODEDIR)SinLLTest.c $(CODEDIR)SinLL.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c $(CODEDIR)LLMergeSort.h $(CODEDIR)queryProcess.h
SLLTCFILES=$(TESTCODEDIR)SinLLTest.c $(CODEDIR)SinLL.c $(CODEDIR)LLMergeSort.c $(CODEDIR)queryProcess.c

UTILDIR=../../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a
UTILC=$(UTILDIR)hashtable.c $(UTILDIR)web.c $(UTILDIR)file.c
UTILH=$(UTILC:.c=.h)


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
