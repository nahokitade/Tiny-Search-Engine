
/* 
 * Name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Naho Kitade
 * Date: April 2014
 *
 * Functionality: A C file containing all the definitions of the function headers in list.h
 * This is a doubly linked list structure.
 *
 */
/* ========================================================================== */

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "list.h"

// ---------------- Function Definitions

/* creates new DLL
 * Returns a pointer to a new List structure
 * Must free() the memory of the DLL after use
 */
List *CreateDLL(){
	List *newDLL;
	newDLL = calloc(1, sizeof(List));
	if(!newDLL) return 0;		
	return newDLL;
}


/* append to a WebPage to the linked list
 * @webPage: WebPage to add to the linked list
 * @linkedList: linkedList to append the WebPage
 * Returns 1 on successful append, 0 if fail.
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

/* remove from top of DLL
 * @linkedList: linkedList to remove from
 * Returns pointer of the WebPage that was removed, NULL if fail
 */
WebPage *removeTop(List *linkedList){
	if(IsEmptyList(linkedList)) return NULL;
	WebPage *webTemp = linkedList->head->page; 
	ListNode *toFreeNode = linkedList->head; // need to keep this since this node needs to be freed
	linkedList->head = linkedList->head->next; // make the new head the one after current head
	if(linkedList->head) linkedList->head->prev = NULL; // make the new heads previous to NULL

	free(toFreeNode); // free memory of ListNode struct.

	return webTemp;
}

/* checks if list is empty
 * @linkedList: linkedList to check if empty
 * Returns 1 if list is empty, 0 if not empty
 */
int IsEmptyList(List *linkedList){
	return (linkedList->head == NULL || linkedList->tail == NULL)? 1 : 0;
}

