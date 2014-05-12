#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

int main(){
//	int i;
	DocNode *curDocNode;
	DocNode *docNodeHead;
	DocNode *newDocNode;

	curDocNode = calloc(1, sizeof(DocNode));
	curDocNode->documentID =38;
	curDocNode->occurrences = 75893;
	docNodeHead = curDocNode;
	
	//for(i = 2; i < 4; i++){
	/*	newDocNode = calloc(1, sizeof(DocNode));
		newDocNode->documentID = 38;
		newDocNode->occurrences = 75893;
		curDocNode->nextDoc = newDocNode;
		curDocNode = curDocNode->nextDoc;
	//}*/
	newDocNode = calloc(1, sizeof(DocNode));
                newDocNode->documentID = 23;
                newDocNode->occurrences = 4698375;
                curDocNode->nextDoc = newDocNode;
                curDocNode = curDocNode->nextDoc;
	
	newDocNode = calloc(1, sizeof(DocNode));
                newDocNode->documentID = 18;
                newDocNode->occurrences = 324;
                curDocNode->nextDoc = newDocNode;
                curDocNode = curDocNode->nextDoc;

	newDocNode = calloc(1, sizeof(DocNode));
                newDocNode->documentID = 14;
                newDocNode->occurrences = 43536;
                curDocNode->nextDoc = newDocNode;
                curDocNode = curDocNode->nextDoc;

	newDocNode = calloc(1, sizeof(DocNode));
                newDocNode->documentID = 13;
                newDocNode->occurrences = 24324;
                curDocNode->nextDoc = newDocNode;
                curDocNode = curDocNode->nextDoc;

	/*for(i = 10; i > 0; i--){
		newDocNode = calloc(1, sizeof(DocNode));
	        newDocNode->documentID = i;
	        newDocNode->occurrences = (i+7);
	        curDocNode->nextDoc = newDocNode;
	        curDocNode = curDocNode->nextDoc;
	}*/
	
	curDocNode = docNodeHead;
	
	PrintDocChain(docNodeHead);	
	
	//MergeSort(&docNodeHead, compareIDs);
	MergeSort(&docNodeHead, compareOccurrences);
	
	printf("Start of sort results.\n");
	
	PrintDocChain(docNodeHead);

	return 1;
}

