/*	MergeSortTest.c		Unit testing for MergeSort.c

	Project name:   Tiny Search Engine
	Component name: query

	This file contains unit testing for MergeSort.c
	
	Primary Author:	Naho Kitade
	Date Created:	May 2014
======================================================================*/
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

// ---------------- Constant definitions 
#define LARGE_PRIME_ID 2027
#define LARGE_PRIME_OCC 1499

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

int main(){
	int i;
	int r;
	int prevComp;
	int curComp;
	int missCounter = 0;
	int upTo = 50;

	DocNode *curDocNode;
	DocNode *docNodeHead;
	DocNode *newDocNode;

	srand(time(NULL));

	while(1){
	
	// making random numbers and inserting into the DocNodes
	// to be sorted

	r = rand() % LARGE_PRIME_ID;

	curDocNode = calloc(1, sizeof(DocNode));
	curDocNode->documentID = r;
	r = rand() % LARGE_PRIME_OCC;
	curDocNode->occurrences = r;
	docNodeHead = curDocNode;

	if(upTo == 0) upTo++;

	for(i = 2; i < upTo; i++){
		r = rand() % LARGE_PRIME_ID;
		newDocNode = calloc(1, sizeof(DocNode));
		newDocNode->documentID = r;
		r = rand() % LARGE_PRIME_OCC;
		newDocNode->occurrences = r;
		curDocNode->nextDoc = newDocNode;
		curDocNode = curDocNode->nextDoc;
	}

	// sort accoring to IDs.
	MergeSort(&docNodeHead, compareIDs);

	curDocNode = docNodeHead;

	// comparing the results with expected results to see
	// if the sort was successful.
	prevComp = curDocNode->documentID;
	curDocNode = curDocNode->nextDoc;
	while(curDocNode){
		curComp = curDocNode->documentID;
		if(curComp > prevComp) missCounter++;
		prevComp = curComp;
		curDocNode = curDocNode->nextDoc;
	}

	// notify caller of fail or success or sort
	if(missCounter) printf("Merge Sort failed at sorting with Document IDs. For %d elements\n", upTo);
	else printf("Merge Sort succeeded at sorting with Document IDs.For %d elements \n", upTo);

	missCounter = 0;

	// sort according to occurrences
	MergeSort(&docNodeHead, compareOccurrences);

	curDocNode = docNodeHead;

	// do the same as obove to find out if sort was successful
        prevComp = curDocNode->occurrences;
        curDocNode = curDocNode->nextDoc;
        while(curDocNode){
                curComp = curDocNode->occurrences;
                if(curComp > prevComp) missCounter++;
                prevComp = curComp;
                curDocNode = curDocNode->nextDoc;
        }

	// notify caller of fail or success or sort
	if(missCounter) printf("Merge Sort failed at sorting with occurrences. For %d elements\n", upTo);
        else printf("Merge Sort succeeded at sorting with occurrences. For %d elements\n", upTo);

	// reached the end of the test
	if(upTo == 1) break;
		
	// keep testing for a list of size /5 the original
	upTo = upTo/5;

	// reset counter
	missCounter = 0;
}
	return 1;
}

