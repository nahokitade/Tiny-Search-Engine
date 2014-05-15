/*	LLMergeSort.c	merge sorts linked list of DocNodes

	Project name: Tiny Search Engine
	Component name: query

	This file contains all the function necessary (besides the compare functions)
	necessary to perform merge sort recursively on a linked list of DocNodes.
	
	Primary Author:	Naho Kitade
	Date Created:	May 2014
======================================================================*/
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
DocNode *Merge(DocNode *doc1, DocNode *doc2, int(*compareFunc)(DocNode *doc1, DocNode *doc2));
int SplitHalf(DocNode *toSplit, DocNode **firstHalf, DocNode **lastHalf);
void MergeSort(DocNode **docHead, int(*compareFunc)(DocNode *doc1, DocNode *doc2));
void AppendToFromNode(DocNode **docTo, DocNode **docFrom);

/*====================================================================*/


/*
 * Overall sorting function that performs merge sort on a 
 * linked list of DocNodes.
 * @docHead: head of the DocNode list to sort.
 * @compareFunc: function that will define how to compare two 
 * DocNodes, doc1 and doc2.
 * @result: docHead will contain the sorted linked list. 
 */
void MergeSort(DocNode **docHead, int(*compareFunc)(DocNode *doc1, DocNode *doc2)){
	DocNode *firstHalf;
	DocNode *lastHalf;
	DocNode *head = *docHead;

	// base case. No elements, or only one element in the 
	// linked list is already sorted.
	if((head == NULL) || (head->nextDoc == NULL)) return;
	
	// split the linked list into two halfs
	SplitHalf(head, &firstHalf, &lastHalf);

	// merge sort the remaining sub lists.
	MergeSort(&firstHalf, compareFunc);
	MergeSort(&lastHalf, compareFunc);

	// merge the two sorted sub lists into one sorted list.
	*docHead = Merge(firstHalf, lastHalf, compareFunc);
}

/*
 * Splits a given DocNode list in half and store the two halves 
 * at firstHalf and lastHalf.
 * @toSplit: DocNode list to split in half.
 * @firstHalf: empty pointer to store the first half of the split
 * linked list.
 * @lastHalf: empty pointer to store the latter half of the split
 * linked list.
 * @result: returns 1 if successful.
 */
int SplitHalf(DocNode *toSplit, DocNode **firstHalf, DocNode **lastHalf){
	DocNode *first;
	DocNode *second;

	// if there is only one node or no nodes in the list to split
	// just set the first half pointer to the list and leave last half 
	// NULL
	if(!toSplit || toSplit->nextDoc == NULL){
		*firstHalf = toSplit;
		*lastHalf = NULL;
		return 1;
	}
	
	// have two pointers, one moving twice the speed to the next
	// node than the other. We know the middle node when the 
	// faster moving pointer hit the end of the list. 
	// Idea from the "cracking the coding interview" book.
	first = toSplit;
	second = toSplit->nextDoc;
	while(second){
		second = second->nextDoc;
		if(second){            // be careful of the NULL pointer
			second = second->nextDoc;
			first = first->nextDoc;
		}
	}
	
	// split the list at the middle node and store it at the firstHalf and
	// lastHalf pointer. 
	*firstHalf = toSplit;
	*lastHalf = first->nextDoc;
	first->nextDoc = NULL;          // remember to detach the first and last half
	return 1;
}

/* 
 * Merges the DocNode list doc1 and doc2 in correct sorted order 
 * according to compareFunc.
 * @compareFunc: function that defines the comparison between two
 * DocNodes. The specification of the function is such:
 * compareFunc returns 1  if doc1 > doc2
 *                     0  if doc1 == doc2
 *                     -1 if doc1 < doc2
 * @doc1, doc2: DocNode lists to merge.
 * @result: returns a DocNode * that contains the merged result. 
 */
DocNode *Merge(DocNode *doc1, DocNode *doc2, int(*compareFunc)(DocNode *doc1, DocNode *doc2)){
	DocNode mergeHead;
	DocNode *current = &mergeHead;
	int compResult;

	mergeHead.nextDoc = NULL;

	while(1){
		// if either pointers are NULL, just return the other non-NULL pointer.
		if(doc1 == NULL){
			current->nextDoc = doc2;
			break;
		}
		if(doc2 == NULL){
                        current->nextDoc = doc1;
                        break;
                }
		// depending on which DocNode is greater according to the 
		// compare function, move the appropriate DocNode list's first
		// node to the current position of the list storing the returning
		// DocNode list.
		if((compResult = ((*compareFunc)(doc1, doc2))) == 1){
			AppendToFromNode(&current->nextDoc, &doc1);	
        	}
        	else{
			AppendToFromNode(&current->nextDoc, &doc2);
        	}
		// Current now has a Node it is pointing to, so move the 
		// pointer forward. 
		current = current->nextDoc;
	}

	// mergeHead points to NULL, so you want to return the 
	// element after the head. 
	return mergeHead.nextDoc;
}

/*
 * Adds the first element of the docFrom DocNode list
 * to the end of the docTo DocNode list.
 * @docTo: DocNode list to add the element to.
 * @docFrom: DocNode list to add the element from. 
 * @result: docTo and docFrom will be modified according to
 * the above explanation.
 */ 
void AppendToFromNode(DocNode **docTo, DocNode **docFrom){
  DocNode *moveNode = *docFrom; // keep the moving node in a temp pointer

  *docFrom = moveNode->nextDoc; // take off the first element from docFrom

  moveNode->nextDoc = *docTo;   // attach to the front of docTo, the moveNode

  *docTo = moveNode;            // move the pointer of docTo back to moveNode which
				// is its new head. 
}

