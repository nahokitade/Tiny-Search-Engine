
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
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "list.h"

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

List *CreateDLL(){
	List *newDLL;
	newDLL = calloc(1, sizeof(List));
	if(!newDLL) return 0;		
	return newDLL;
}


/* add to linked list
 */
int appendDLL(WebPage *webPage, List *linkedList){
	// allocate memory for the node to append.
	ListNode *addNode;
	addNode = calloc(1, sizeof(ListNode));
	if(!addNode) return 0;
	addNode->page = webPage; 
	
	// if both head and tail is NULL then this is an empty list, so set head and tail to the
	// added node, and set the previous and next of the added node to NULL as it points to nothing
	// yet.
	if(IsEmptyList(linkedList)){
		linkedList->head = addNode;
		linkedList->tail = addNode;
		return 1; // return 1 on success
	}
	else{ // if not the above case, the list is not empty
		addNode->prev = linkedList->tail; // the previous of the adding node is the tail node
		addNode->prev->next = addNode;   // link the tail element with the adding node 
		linkedList->tail = addNode;		    // the adding node is the new tail
		return 1;
	}
}

WebPage *removeTop(List *linkedList){
	if(IsEmptyList(linkedList)) return NULL;
	WebPage *webTemp = linkedList->head->page; 
	ListNode *toFreeNode = linkedList->head; // need to keep this since this node needs to be freed
	linkedList->head = linkedList->head->next; // make the new head the one after current head
	if(linkedList->head) linkedList->head->prev = NULL; // make the new heads previous to NULL

	free(toFreeNode); // free memory of ListNode struct.

	return webTemp;
}

int IsEmptyList(List *linkedList){
	return (linkedList->head == NULL || linkedList->tail == NULL)? 1 : 0;
}

