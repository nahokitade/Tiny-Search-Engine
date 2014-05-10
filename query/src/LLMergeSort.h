/* ========================================================================== */
/* File: LLMergeSort.h
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
#ifndef LLMERGESORT_H
#define LLMERGESORT_H
 
// ---------------- Prerequisites e.g., Requires "math.h"
   
// ---------------- Constants
  
// ---------------- Structures/Types
  
// ---------------- Public Variables
  
// ---------------- Prototypes/Macros
  
DocNode *Merge(DocNode *doc1, DocNode *doc2, int(*compareFunc)(DocNode *doc1, DocNode *doc2));
int SplitHalf(DocNode *toSplit, DocNode **firstHalf, DocNode **lastHalf);
void MergeSort(DocNode **docHead, int(*compareFunc)(DocNode *doc1, DocNode *doc2));

#endif // LLMERGESORT_H

