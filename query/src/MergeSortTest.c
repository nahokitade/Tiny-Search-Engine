#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

int main(){
	int i;
	DocNode *curDocNode;
	DocNode *docNodeHead;
	DocNode *newDocNode;

	curDocNode = calloc(1, sizeof(DocNode));
	curDocNode->documentID = 1;
	curDocNode->occurrences = 10;
	docNodeHead = curDocNode;

	for(i = 2; i < 10; i++){
		newDocNode = calloc(1, sizeof(DocNode));
		newDocNode->documentID = i;
		newDocNode->occurrences = (i+3);
		curDocNode->nextDoc = newDocNode;
		curDocNode = curDocNode->nextDoc;
	}
	
	for(i = 10; i > 0; i--){
		newDocNode = calloc(1, sizeof(DocNode));
	        newDocNode->documentID = i;
	        newDocNode->occurrences = (i+7);
	        curDocNode->nextDoc = newDocNode;
	        curDocNode = curDocNode->nextDoc;
	}
	
	curDocNode = docNodeHead;
	
	PrintDocChain(docNodeHead);	
	
	//MergeSort(&docNodeHead, compareIDs);
	MergeSort(&docNodeHead, compareOccurrences);
	
	printf("Start of sort results.\n");
	
	PrintDocChain(docNodeHead);

	return 1;
}

