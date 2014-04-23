
/* Name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Naho Kitade
 * Date: April 2014
 *
 * You should include in this file your functionality for the hashtable as
 * described in the assignment and lecture.
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

List *CreateDLL(){
	if((List *newDLL = calloc(1, sizeof(List))) == NULL) return 0;		
	return newDLL;
}


/* add to linked list
 */
int appendDLL(WebPage *webPage, List *linkedList){
	// allocate memory for the node to append.
	if((ListNode *addNode = calloc(1, sizeof(ListNode))) == NULL) return 0;
	addNode->page = *webPage; 
	
	// if both head and tail is NULL then this is an empty list, so set head and tail to the
	// added node, and set the previous and next of the added node to NULL as it points to nothing
	// yet.
	if(IsEmptyList(linkedList)){
		linkedList->head = &addNode;
		linkedList->tail = &addNode;
		return 1; // return 1 on success
	}
	else{ // if not the above case, the list is not empty
		addNode->previous = linkedList->tail; // the previous of the adding node is the tail node
		addNode->previous->next = &addNode;   // link the tail element with the adding node 
		linkedList->tail = &addNode;		    // the adding node is the new tail
		return 1;
	}
}

WebPage *removeTop(List *linkedList){
	if(linkedList->head == NULL || linkedlist->tail == NULL) return NULL;
	char *webTemp = linkedList->head->page; // DOES THIS WORK????
	ListNode *toFreeNode = linkedList->head; // need to keep this since this node needs to be freed
	linkedList->head = linkedList->head->next; // make the new head the one after current head
	linkedList->head->prev = NULL; // make the new heads previous to NULL

	// MOVE SOMEWHERE ELSE deleteWebPage(toFreeNode->page); // function in common.c frees memory of WebPage struct
	free(toFreeNode); // free memory of ListNode struct.

	return webTemp;
}

int IsEmptyList(List *linkedList){
	return (linkedList->head == NULL || linkedList->tail == NULL)? 1 : 0;
}

