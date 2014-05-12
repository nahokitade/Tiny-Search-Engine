/* ========================================================================== */
/* File: queryProcess.h
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
#ifndef QUERYPROC_H
#define QUERYPROC_H

typedef struct WordChainNode {
    struct WordsLL *words;                      
    struct WordChainNode *nextWords
    struct DocNode *docs;
} WordChainNode;

typedef struct WordsLL {
    struct WordsLL *nextWord;
} WordsLL;

typedef struct SLL {
	WordChainNode *head;                          // "beginning" of the list
	WordChainNode *tail;                          // "end" of the list
} SLL;
 
DocNode *DocsFromWordNode(char *word, HashTable *hashTab);

DocNode *CopyDocs(DocNode *docHead);

void DocMergedID(DocNode *doc1, DocNode *doc2);

int compareIDs(DocNode *doc1, DocNode *doc2);

int ProcessAND(DocNode **doc1);

int ProcessOR(DocNode **doc1);

void SortByRank(DocNode **docToSort);

int compareOccurrences(DocNode *doc1, DocNode *doc2);

void PrintQueryResult(DocNode *printHead, char *webPageDir);

char *addPathToFile(char *path, char *fileName);

char *GetURL(char *fileName);

void PrintDocChain(DocNode *docNodeHead);

#endif //QUERYPROC_H

