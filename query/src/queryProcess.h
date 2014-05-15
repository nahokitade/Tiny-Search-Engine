/* ========================================================================== */
/* File: queryProcess.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: query
 *
 * This file contains all functions needed to process the AND and OR
 * of a specific query input.
 * 
 * Primary Author: Naho Kitade
 * Date Created:   May 2014
 *
 */
/* ========================================================================== */
#ifndef QUERYPROC_H
#define QUERYPROC_H

// ---------------- Prerequisites e.g., Requires "math.h"

// ---------------- Constants

// ---------------- Structures/Types

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/*
 * Compare function passed into merge sort function to compare the
 * DocNode's occurrences.
 * @doc1: first document to compare
 * @doc2: second document to compare
 * @result: returns 1 if doc1 has a greater occurrences.
 * returns 0 if doc1 and doc2 has the same occurrences.
 * returns -1 if doc1 has a smaller occurrences.
 */
int compareOccurrences(DocNode *doc1, DocNode *doc2);

/*
 * Compare function passed into merge sort function to compare the
 * DocNode's documentID.
 * @doc1: first document to compare
 * @doc2: second document to compare
 * @result: returns 1 if doc1 has a greater documentID.
 * returns 0 if doc1 and doc2 has the same documentID.
 * returns -1 if doc1 has a smaller documentID.
 */
int compareIDs(DocNode *doc1, DocNode *doc2);

/*
 *  Looks for the given word in the inverted index, gets its associated
 *  WordNode, get its docs field (Linked List of DocNodes), and returns
 *  this DocNodes.
 *  @word: word to get the DocNode list for.
 *  @hashTab: The inverted index to look up the word in
 *  @result: returns a pointer to the head of the associated DocNode
 *  list.
 */
DocNode *DocsFromWordNode(char *word, HashTable *hashTab);

/*
 * Copies the DocNode provided to the function. Allocates this copy
 * on the heap. The caller is responsible for the freeing of this
 * memory.
 * @docHead: the head of the DocNode list to copy.
 * @result: pointer to the head of the copied DocNode list.
 */
DocNode *CopyDocs(DocNode *docHead);

/*
 * Function used for AND and OR processes.
 * Takes in pointers to two DocNode lists, and merges them together
 * in sorted order according to their document IDs. (descending order)
 * The head of this merged list os stored now at doc1 pointer.
 * doc1 must be a pointer that is not NULL, unless both doc1 and doc2
 * is NULL. doc2 can be NULL, in which case doc1 alone will be sorted
 * according to document ID.
 * @doc1: Head of the first DocNode list
 * @doc2: Head of the second DocNode list
 * @result: returns 0 if doc1 is NULL (assuming doc2 is NULL). Else,
 * returns 1. doc1 points to the head of the sorted DocNode list.
 */
int DocMergedID(DocNode **doc1, DocNode **doc2);

/*
 * Function used for AND processing
 * Takes output from DocMergedID and leaves only the duplicates
 * Makes duplicates into one node by adding the second occurrence
 * to the first DocNode occurrence.
 * @doc1: pointer to the head of a DocNode to process for AND.
 * @result: doc1 contains a DocNode list with only the duplicated
 * DocNode. Returns 1 if successful, and 0 if not.
 */
int ProcessAND(DocNode **doc1);

/*
 * Function used for OR processing.
 * Takes output from DocMergedID and make duplicates into one by
 * adding the second occurrence to the first docnode occurrence.
 * @doc1: pointer to the head of a DocNode to process for OR.
 * @result: doc1 "used to be" duplicated and non duplicated DocNode
 */
int ProcessOR(DocNode **doc1);

/*
 * Sorts given DocNode by occurrences "Rank".
 * @docToSort: head of the DocNode to sort.
 * @result: docToSort now points to a sorted DocNode list.
 */
void SortByRank(DocNode **docToSort);

/*
 * For all document ID in DocNode of DocNode list, the function
 * will find the URL from specific crawler files, and will print out
 * a line per document formatted:
 *              Document ID: documentID URL: http://url.com \n
 * Color coded according to the ranking.
 * Occurrences > 100 prints in GREEN
 * Occurrences > 50 but < 100 prints in CYAN
 * Occurrences > 10 but < 50 prints in YELLOW
 * Occurrences < 10 prints in MAGENTA
 * @printHead: head of the DocNode to print
 * @webPageDir: directory containing output files from crawler
 * @result: prints every DocNode in the list with the above format
 */
void PrintQueryResult(DocNode *printHead, char *webPageDir);

#endif //QUERYPROC_H

