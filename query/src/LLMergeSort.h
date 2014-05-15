/* ========================================================================== */
/* File: LLMergeSort.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: query
 *
 * This file contains all the function necessary (besides the compare functions)
 * necessary to perform merge sort recursively on a linked list of DocNodes.
 * 
 * Primary Author: Naho Kitade
 * Date Created:   May 2014
 *
 */
/* ========================================================================== */
#ifndef LLMERGESORT_H
#define LLMERGESORT_H
 
// ---------------- Prerequisites e.g., Requires "math.h"
   
// ---------------- Constants
  
// ---------------- Structures/Types
  
// ---------------- Public Variables
  
// ---------------- Prototypes/Macros
  
/*
 * Overall sorting function that performs merge sort on a
 * linked list of DocNodes.
 * @docHead: head of the DocNode list to sort.
 * @compareFunc: function that will define how to compare two
 * DocNodes, doc1 and doc2.
 * @result: docHead will contain the sorted linked list.
 */
DocNode *Merge(DocNode *doc1, DocNode *doc2, int(*compareFunc)(DocNode *doc1, DocNode *doc2));

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
int SplitHalf(DocNode *toSplit, DocNode **firstHalf, DocNode **lastHalf);

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
void MergeSort(DocNode **docHead, int(*compareFunc)(DocNode *doc1, DocNode *doc2));

#endif // LLMERGESORT_H

