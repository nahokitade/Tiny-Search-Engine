/*	queryProcessTest.c	Unit testing for queryProcess.c

	Project name:   Tiny Search Engine
	Component name: query

	This file contains unit testing for queryProcess.c
	
	Primary Author:	Naho Kitade
	Date Created:	May 2014
======================================================================*/
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>
#include <stdio.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

int main(){
DocNode *tempProcessDocNode;
DocNode *processDocNode;
DocNode *processDocNode2;
int missCounter = 0;

HashTable *hashTable;
hashTable = CreateNewHashTab();

// make indes out of a sample .dat file
readFile("testindex2.dat", hashTable);

// only kitty in the file, so look for that to simulate query
char *word = "kitty";

// getting the docs from created index
tempProcessDocNode = DocsFromWordNode(word, hashTable);

// copy the above DocNode
processDocNode = CopyDocs(tempProcessDocNode);

// iterate through the original and copy of the DocNode, and see if
// the copy is identical
DocNode *procDNCur = processDocNode;
DocNode *tempProcDNCur = tempProcessDocNode;
while(procDNCur || tempProcDNCur){
	if(procDNCur->documentID != tempProcDNCur->documentID){
		missCounter++;
	}
	if(procDNCur->occurrences != tempProcDNCur->occurrences){
                missCounter++;
        }
	procDNCur = procDNCur->nextDoc;
	tempProcDNCur = tempProcDNCur->nextDoc;
}

// inform of copy success or failure.
if(missCounter) printf("FAIL: Copy is not identical to the original.\n");
else printf("SUCCESS: Copy is identical to the original.\n");

// sort according to the IDs (MergeSort tested in LLMergeSortTest.c)
MergeSort(&processDocNode, compareIDs);

processDocNode2 = CopyDocs(processDocNode);

// testing OR processing
ProcessOR(&processDocNode);
SortByRank(&processDocNode);

// print the query result. (caller must decide success by eye.)
printf("Printing ORed DocNode Query Result...\n");
PrintQueryResult(processDocNode, "/net/class/cs50/tse/crawler/lvl3/");

ProcessAND(&processDocNode2);
SortByRank(&processDocNode2);

printf("Printing ANDed DocNode Query Result...\n");
PrintQueryResult(processDocNode2, "/net/class/cs50/tse/crawler/lvl3/");

return 1;
}

