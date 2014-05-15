#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

#define LARGE_PRIME_ID 2027
#define LARGE_PRIME_OCC 1499

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

	MergeSort(&docNodeHead, compareIDs);

	curDocNode = docNodeHead;

	prevComp = curDocNode->documentID;
	curDocNode = curDocNode->nextDoc;
	while(curDocNode){
		curComp = curDocNode->documentID;
		if(curComp > prevComp) missCounter++;
		prevComp = curComp;
		curDocNode = curDocNode->nextDoc;
	}

	if(missCounter) printf("Merge Sort failed at sorting with Document IDs. For %d elements\n", upTo);
	else printf("Merge Sort succeeded at sorting with Document IDs.For %d elements \n", upTo);

	missCounter = 0;

	MergeSort(&docNodeHead, compareOccurrences);

	curDocNode = docNodeHead;

        prevComp = curDocNode->occurrences;
        curDocNode = curDocNode->nextDoc;
        while(curDocNode){
                curComp = curDocNode->occurrences;
                if(curComp > prevComp) missCounter++;
                prevComp = curComp;
                curDocNode = curDocNode->nextDoc;
        }

	if(missCounter) printf("Merge Sort failed at sorting with occurrences. For %d elements\n", upTo);
        else printf("Merge Sort succeeded at sorting with occurrences. For %d elements\n", upTo);

	if(upTo == 1) break;
		
	upTo = upTo/5;

	missCounter = 0;
}
	return 1;
}

