/* ========================================================================== */
/* File: SinLL.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: query
 * This file contains functions to create, add to, and delete a singly
 * linked list with nodes containing word lists and DocNodes.
 * 
 * Primary Author: Naho Kitade
 * Date Created:   2014 May
 *
 */
/* ========================================================================== */
#ifndef SinLL_H
#define SinLL_H

// ---------------- Prerequisites e.g., Requires "math.h"

// ---------------- Constants

// ---------------- Structures/Types

// linked list that contains a linked list of words, and
// a linked list of DocNodes.
typedef struct WordChainNode {
    struct WordsLL *words;			// head of the linkedlist of words
    struct WordChainNode *nextWords;		// next pointer to the next set of words and DocNodes
    struct DocNode *docs;			// head of the linkedlist of DocNodes
} WordChainNode;

// linked list of words to be stored in WordChainNode. In query, these words
// represent the words to be ANDed. 
typedef struct WordsLL {
    char *word;					// word to be stored
    struct WordsLL *nextWord;			// points to next same structure
} WordsLL;

typedef struct SinLL {
        WordChainNode *head;                    // "beginning" of the list
        WordChainNode *tail;                    // "end" of the list
} SinLL;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/*
 * Allocates memory for the list and returns a pointer to
 * this memory.
 * @result: returns a pointer to a new SinLL.
 */
SinLL *CreateSinLL();

/* 
 * append a word to the current node (tail) of the linked list
 * @word: word to add to the linked list
 * @linkedList: linkedList to append the word
 * Returns 1 on successful append, 0 if fail.
 */
int appendWord(char *word, SinLL *linkedList);

/*
 * creates a new WordChain in the linked list, not just a
 * new WordsLL node like appendWord function.
 * @word: word to add to the new WordChainNode
 * @linkedList: list to add this new WordChainNode
 * @result: returns 1 in success, 0 on fail.
 */
int appendNewWordChain(char *word, SinLL *linkedList);

/* remove from top of SLL and put the DocNode chain that was on that
 * node to tempDocPtr.
 * @linkedList: linkedList to remove from.
 * @tempDocPtr: pointer to a DocNode * to put the results of the function.
 * @result: Saves pointer of the DocNode that was removed at tempDocPtr.
 * Returns 1 if successful, 0 if the given linked list is NULL.
 */
int removeTopDoc(SinLL *linkedList, DocNode **tempDocPtr);

/*
 * Deletes the full node of the linked list.
 * @toFreeNode: Node in the linked list to free/delete
 * @result: returns 1 if successful
 */
int DeleteWordChainNode(WordChainNode *toFreeNode);

/*
 * Deletes the word linked list withing the node of the linked list.
 * @toFreeWord: Head of the word linked list in the node to free/delete
 * @result: returns 1 if successful
 */
int DeleteWordsLLChain(WordsLL *toFreeWords);

/* checks if list is empty
 * @linkedList: linkedList to check if empty
 * Returns 1 if list is empty, 0 if not empty
 */
int IsEmptySinLL(SinLL *linkedList);

/*
 * Adds a given DocNode list to the given WordChainNode.
 * @toAddNode: WordChainNode to add the DocNode list to.
 * @docNodeChain: DocNode list to add.
 * @result: returns 1 on add success
 */
int AddDocNodeChain(WordChainNode *toAddNode, DocNode *docNodeChain);


#endif //SinLL_H
