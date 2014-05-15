/*	SinLL.c		Singly linked list with nodes containing word lists and 
 *			DocNodeLists.
 *
	Project name: Naho Kitade
	Component name: query

	This file contains functions to create, add to, and delete a singly 
	linked list with nodes containing word lists and DocNodes.
	
	Primary Author:	Naho Kitade
	Date Created:	2014 May
======================================================================*/
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "SinLL.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/


/*
 * Allocates memory for the list and returns a pointer to 
 * this memory.
 * @result: returns a pointer to a new SinLL.
 */
SinLL *CreateSinLL(){
        SinLL *newSinLL;
        newSinLL = calloc(1, sizeof(SinLL));
        if(!newSinLL) return 0;
        return newSinLL;
}


/* append a word to the current node (tail) of the linked list
 * @word: word to add to the linked list
 * @linkedList: linkedList to append the word
 * Returns 1 on successful append, 0 if fail.
 */
int appendWord(char *word, SinLL *linkedList){
	// allocate memory for the node to append.
	WordsLL *addNode;
	addNode = calloc(1, sizeof(WordsLL));
	if(!addNode) return 0;

	// link up the word to the new node
	addNode->word = word; 
	
	// get the word list to append to, and go to the end of this list
	// to link the new node to the end of the list
	WordsLL *curWord = linkedList->tail->words;
	for( ; curWord->nextWord != NULL; curWord = curWord->nextWord);
	
	curWord->nextWord = addNode;

	return 1;
}

/*
 * creates a new WordChain in the linked list, not just a
 * new WordsLL node like appendWord function.
 * @word: word to add to the new WordChainNode
 * @linkedList: list to add this new WordChainNode
 * @result: returns 1 in success, 0 on fail.
 */
int appendNewWordChain(char *word, SinLL *linkedList){
	// allocate memory for the WordChainNode that wraps the 
	// wordsLLs. 
	WordChainNode *newWCN;
	newWCN = calloc(1, sizeof(WordChainNode));
	if(!newWCN) return 0;

	// allocate memory for the actual WordsLL that has as it's head
	// the word passed to the function.
	WordsLL *addNode;
        addNode = calloc(1, sizeof(WordsLL));
        if(!addNode) return 0;
        addNode->word = word;

	// link the WordChainNode and WordsLL together. 
	newWCN->words = addNode;	

	// if the linkedList is empty, update the head and tail to the new
	// WordChainNode that we just created.
	if(IsEmptySinLL(linkedList)){
		linkedList->head = newWCN;
		linkedList->tail = newWCN;
		return 1;
	}
	else{
		// not empty, so to append to the end of the list, append
		// the new node to the list's tail, and update the tail position
		linkedList->tail->nextWords = newWCN;
		linkedList->tail = linkedList->tail->nextWords;
		return 1;
	}
}

/* 
 * Adds a given DocNode list to the given WordChainNode. 
 * @toAddNode: WordChainNode to add the DocNode list to.
 * @docNodeChain: DocNode list to add.
 * @result: returns 1 on add success
 */
int AddDocNodeChain(WordChainNode *toAddNode, DocNode *docNodeChain){
	toAddNode->docs = docNodeChain;
	return 1;
}

/* remove from top of SLL and put the DocNode chain that was on that
 * node to tempDocPtr.
 * @linkedList: linkedList to remove from.
 * @tempDocPtr: pointer to a DocNode * to put the results of the function.
 * @result: Saves pointer of the DocNode that was removed at tempDocPtr. 
 * Returns 1 if successful, 0 if the given linked list is NULL.
 */
int removeTopDoc(SinLL *linkedList, DocNode **tempDocPtr){
	if(IsEmptySinLL(linkedList)) return 0;
	*tempDocPtr = linkedList->head->docs; 
	WordChainNode *toFreeNode = linkedList->head; // need to keep this since this node needs to be freed
	linkedList->head = linkedList->head->nextWords; // make the new head the one after current head

	DeleteWordChainNode(toFreeNode); // free memory of WordChainNode struct.

	return 1;
}

/* 
 * Deletes the full node of the linked list.
 * @toFreeNode: Node in the linked list to free/delete
 * @result: returns 1 if successful
 */
int DeleteWordChainNode(WordChainNode *toFreeNode){
	DeleteWordsLLChain(toFreeNode->words);	
	free(toFreeNode);
	return 1;
}

/*
 * Deletes the word linked list withing the node of the linked list.
 * @toFreeWord: Head of the word linked list in the node to free/delete
 * @result: returns 1 if successful
 */
int DeleteWordsLLChain(WordsLL *toFreeWords){
	WordsLL *tempFreeWords;
	while(toFreeWords){
		// keep the current WordsLL in a temp to free later.
		tempFreeWords = toFreeWords;
		toFreeWords = toFreeWords->nextWord;	// go through the list
		free(tempFreeWords);
	}
	return 1;
}

/* checks if list is empty
 * @linkedList: linkedList to check if empty
 * Returns 1 if list is empty, 0 if not empty
 */
int IsEmptySinLL(SinLL *linkedList){
	return (linkedList->head == NULL || linkedList->tail == NULL)? 1 : 0;
}

