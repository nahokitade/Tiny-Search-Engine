#include <stdlib.h>
#include "hashtable.h"

DocNode *Merge(DocNode *doc1, DocNode *doc2, int(*compareFunc)(DocNode *doc1, DocNode *doc2));
int SplitHalf(DocNode *toSplit, DocNode **firstHalf, DocNode **lastHalf);
void MergeSort(DocNode **docHead, int(*compareFunc)(DocNode *doc1, DocNode *doc2));
void AppendToFromNode(DocNode **docTo, DocNode **docFrom);

void MergeSort(DocNode **docHead, int(*compareFunc)(DocNode *doc1, DocNode *doc2)){
	DocNode *firstHalf;
	DocNode *lastHalf;
	DocNode *head = *docHead;

	if((head == NULL) || (head->nextDoc == NULL)) return;
	
	SplitHalf(head, &firstHalf, &lastHalf);

	MergeSort(&firstHalf, compareFunc);
	MergeSort(&lastHalf, compareFunc);
	*docHead = Merge(firstHalf, lastHalf, compareFunc);
}

int SplitHalf(DocNode *toSplit, DocNode **firstHalf, DocNode **lastHalf){
	DocNode *first;
	DocNode *second;

	if(!toSplit || toSplit->nextDoc == NULL){
		*firstHalf = toSplit;
		*lastHalf = NULL;
		return 1;
	}
	
	first = toSplit;
	second = toSplit->nextDoc;
	
	while(second){
		second = second->nextDoc;
		if(second){
			second = second->nextDoc;
			first = first->nextDoc;
		}
	}
	
	*firstHalf = toSplit;
	*lastHalf = first->nextDoc;
	first->nextDoc = NULL;
	return 1;
}

/* compareFunc returns 1  if doc1 > doc2
 *                     0  if doc1 == doc2
 *                     -1 if doc1 < doc2
 */
DocNode *Merge(DocNode *doc1, DocNode *doc2, int(*compareFunc)(DocNode *doc1, DocNode *doc2)){
	DocNode mergeHead;
	DocNode *current = &mergeHead;
	int compResult;

	mergeHead.nextDoc = NULL;

	if(doc1 == NULL) return doc2;
	if(doc2 == NULL) return doc1;
	
	while(1){
		if(doc1 == NULL){
			current->nextDoc = doc2;
			break;
		}
		if(doc2 == NULL){
                        current->nextDoc = doc1;
                        break;
                }
		if((compResult = ((*compareFunc)(doc1, doc2))) == 1){
			AppendToFromNode(&current->nextDoc, &doc1);	
        	}
        	else{
			AppendToFromNode(&current->nextDoc, &doc2);
        	}
		current = current->nextDoc;
	}

	return mergeHead.nextDoc;
}




void AppendToFromNode(DocNode **docTo, DocNode **docFrom){
  /* the front source node  */
  DocNode *moveNode = *docFrom;
 
  /* Advance the source pointer */
  *docFrom = moveNode->nextDoc;
 
  /* Link the old dest off the new node */
  moveNode->nextDoc = *docTo; 
 
  /* Move dest to point to the new node */
  *docTo = moveNode;
}





