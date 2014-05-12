/* ========================================================================== */
/* File: SinLL.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: query
 *
 * This file contains utility functions for dealing with files and directories.
 * These functions are not likely to be very portable, if at all. They are
 * known to run properly on Linux and BSD systems.
 *
 */
/* ========================================================================== */
#ifndef SinLL_H
#define SinLL_H

typedef struct WordChainNode {
    struct WordsLL *words;
    struct WordChainNode *nextWords;
    struct DocNode *docs;
} WordChainNode;

typedef struct WordsLL {
    char *word;
    struct WordsLL *nextWord;
} WordsLL;

typedef struct SinLL {
        WordChainNode *head;                          // "beginning" of the list
        WordChainNode *tail;                          // "end" of the list
} SinLL;


SinLL *CreateSinLL();

int appendWord(char *word, SinLL *linkedList);

int appendNewWordChain(char *word, SinLL *linkedList);

int removeTopDoc(SinLL *linkedList, DocNode **tempDocPtr);

int DeleteWordChainNode(WordChainNode *toFreeNode);

int DeleteWordsLLChain(WordsLL *toFreeWords);

int IsEmptySinLL(SinLL *linkedList);

int AddDocNodeChain(WordChainNode *toAddNode, DocNode *docNodeChain);


#endif //SinLL_H
