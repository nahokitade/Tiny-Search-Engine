/*	queryProcess.c	handles processing of the queries

	Project name: Tiny Search Engine
	Component name: query

	This file contains all functions needed to process the AND and OR
	of a specific query input.
	
	Primary Author:	Naho Kitade
	Date Created:	May 2014
	
======================================================================*/
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "LLMergeSort.h"
#include "file.h"

// ---------------- Constant definitions 
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAX_LEN_DOCID_DIGITS 20
#define GOOD_RANK 100
#define OKAY_RANK 50
#define BAD_RANK 10

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int compareIDs(DocNode *doc1, DocNode *doc2);
int compareOccurrences(DocNode *doc1, DocNode *doc2);
char *GetURL(char *fileName);
/*====================================================================*/


/*
 *  Looks for the given word in the inverted index, gets its associated 
 *  WordNode, get its docs field (Linked List of DocNodes), and returns 
 *  this DocNodes.
 *  @word: word to get the DocNode list for.
 *  @hashTab: The inverted index to look up the word in
 *  @result: returns a pointer to the head of the associated DocNode
 *  list. 
 */
DocNode *DocsFromWordNode(char *word, HashTable *hashTab){
	GenHashTableNode *wordHTN;
	WordNode *wordWN;	
	DocNode *toRetDoc;
	
	// look up the word and get the WordNode that
	// contains the DocNode to return. 
	wordHTN = HashContains(word, hashTab);
	if(!wordHTN) return NULL;	// the word is not there.

	// get the DocNode in the WordNode that we just 
	// found in the inverted index and return it. 
	wordWN = ((WordNode *)wordHTN->hashKey);
	toRetDoc = wordWN->docs;
	return toRetDoc;
}

/*
 * Copies the DocNode provided to the function. Allocates this copy
 * on the heap. The caller is responsible for the freeing of this
 * memory. 
 * @docHead: the head of the DocNode list to copy.
 * @result: pointer to the head of the copied DocNode list.
 */
DocNode *CopyDocs(DocNode *docHead){
	DocNode *curDoc = docHead;
	DocNode *copyDocHead;
	DocNode *curCopyDoc;
	DocNode *newCopyDoc;
	
	// if the pointer is empty, return NULL
	if(!docHead) return NULL;

	// allocate memory for the first node to be copied.
	newCopyDoc = calloc(1, sizeof(DocNode));
	if(!newCopyDoc) return NULL;

	// assign the appropriate document ID and occurrence value
	// of the original document onto the copy document node.
	newCopyDoc->documentID = curDoc->documentID;
	newCopyDoc->occurrences = curDoc->occurrences;

	// now ready to keep incrementing through the original DocNodes
	// to make the copy in a similar process as above.
	copyDocHead = newCopyDoc;	// keep head to return at end
	curCopyDoc = newCopyDoc; 	// pointer that acts as an iterator for the copy
	curDoc = curDoc->nextDoc;	// pointer that acts as an iterator for the 
					// original DocNode list

	while(curDoc){
		newCopyDoc = calloc(1, sizeof(DocNode));
        	if(!newCopyDoc) return NULL;

		newCopyDoc->documentID = curDoc->documentID;
        	newCopyDoc->occurrences = curDoc->occurrences;

		// after copy, string together the newly created DocNode and
		// increment the pointers forward. 
        	curCopyDoc->nextDoc = newCopyDoc;
        	curDoc = curDoc->nextDoc;
		curCopyDoc = curCopyDoc->nextDoc;
	}
	return copyDocHead;
}

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
int DocMergedID(DocNode **doc1, DocNode **doc2){
	DocNode *curDoc = *doc1;
	DocNode *doc2Ptr = *doc2;

	// if doc1 is empty, we assume doc2 is empty, so nothing should
	// be done
	if(!curDoc && !doc2Ptr) return 0;

	// if doc2 isnt empty, go to the end of the doc1 list and append
	// the head of doc2 to it. 
	if(curDoc && doc2Ptr){ 
		while(curDoc->nextDoc){
			curDoc = curDoc->nextDoc;
		}
		curDoc->nextDoc = doc2Ptr;
	}
	else if(!curDoc && doc2Ptr){
		*doc1 = *doc2;
	}

	// sort this new longer list according to their document IDs. 
	MergeSort(doc1, compareIDs);
	return 1;
}

/*
 * Compare function passed into merge sort function to compare the 
 * DocNode's documentID.
 * @doc1: first document to compare
 * @doc2: second document to compare
 * @result: returns 1 if doc1 has a greater documentID.
 * returns 0 if doc1 and doc2 has the same documentID.
 * returns -1 if doc1 has a smaller documentID.
 */
int compareIDs(DocNode *doc1, DocNode *doc2){
	if(doc1->documentID > doc2->documentID) return 1;
	else if(doc1->documentID == doc2->documentID) return 0;
	else return -1;
}


/*
 * Function used for AND processing
 * Takes output from DocMergedID and leaves only the duplicates
 * Makes duplicates into one node by adding the second occurrence 
 * to the first DocNode occurrence.
 * @doc1: pointer to the head of a DocNode to process for AND.
 * @result: doc1 contains a DocNode list with only the duplicated 
 * DocNode. Returns 1 if successful, and 0 if not. 
 */
int ProcessAND(DocNode **doc1){
	if(!*doc1) return 0;
	
	// set initial variables for prev, cur, and next Node pointers.
	// tempNode is needed to free unneeded DocNodes.
	DocNode *prevNode = NULL;
	DocNode *curNode = *doc1;
	DocNode *nextNode = curNode->nextDoc;
	DocNode *tempNode;
	int dupCount = 0;		// incremented means that the document
					// had a duplicate.

	while(nextNode){
		// duplicate case.
		if(curNode->documentID == nextNode->documentID){
			// add the occurrences of the two nodes uo in the 
			// curNode, free the duplicated unneeded DocNode
			curNode->occurrences += nextNode->occurrences;
			curNode->nextDoc = nextNode->nextDoc;
			free(nextNode);
			dupCount++;		// know now that curNode was duplicate
			nextNode = curNode->nextDoc; 	// reassign nextNode
		}		
		// non-duplicate case
		else{
			if(!dupCount){	// if not duplicate, we need to delete curNode
				// Need to delete the head of the list as it was not 
				// duplicate. 
				if(!prevNode){
					tempNode = curNode;
                                	curNode = curNode->nextDoc;
					// to remove the curNode, just move the head
					// pointer, doc1 to nextDoc.
					*doc1 = curNode;
                                	free(tempNode);
				}
				// the curNode is not the head of the list
				else{
					tempNode = curNode;
					// simply splice out the curNode and free.
					// reassign curNode position
					prevNode->nextDoc = curNode->nextDoc;
					curNode = prevNode->nextDoc;
					free(tempNode);	
				}
			}
			// if curNode was duplicate, we delete nothing.
			// and move on by incrementing curNode, prevNode
			// and nexNode.
			else{
				prevNode = curNode;
				curNode = curNode->nextDoc;
			}
			nextNode = nextNode->nextDoc;
			dupCount = 0;		// dont forget to reset dupCount
		}
	}

	// need to delete last element if it was not duplicated.
	if(!dupCount){
		// same mechanism as above explanation.
                if(!prevNode){	
                         tempNode = curNode;
                         curNode = curNode->nextDoc;
                         *doc1 = curNode;
                         free(tempNode);
                 }
                 else{
                         tempNode = curNode;
                         prevNode->nextDoc = curNode->nextDoc;
                         curNode = prevNode->nextDoc;
                         free(tempNode);
                 }
        }
	return 1;	// success
}


/*
 * Function used for OR processing.
 * Takes output from DocMergedID and make duplicates into one by 
 * adding the second occurrence to the first docnode occurrence. 
 * @doc1: pointer to the head of a DocNode to process for OR.
 * @result: doc1 "used to be" duplicated and non duplicated DocNode 
 */
int ProcessOR(DocNode **doc1){
        if(!*doc1) return 0;
        DocNode *prevNode = *doc1;
        DocNode *curNode = prevNode->nextDoc;

	// go through the whole DocNode list.
        while(curNode){		
		// found a duplicate
                if(prevNode->documentID == curNode->documentID){
			// add the occurrences of the duplicates up and 
			// delete the unneeded curNode.
                        prevNode->occurrences += curNode->occurrences;
                        prevNode->nextDoc = curNode->nextDoc;
                        free(curNode);
                        curNode = prevNode->nextDoc;
                }
                else{
			// if you dont find a duplicate, just continue on.
                        prevNode = prevNode->nextDoc;
                        curNode = curNode->nextDoc;
                }
        }
        return 1;
}


/*
 * Sorts given DocNode by occurrences "Rank".
 * @docToSort: head of the DocNode to sort.
 * @result: docToSort now points to a sorted DocNode list.
 */
void SortByRank(DocNode **docToSort){
        MergeSort(docToSort, compareOccurrences);
}

/*
 * Compare function passed into merge sort function to compare the
 * DocNode's occurrences.
 * @doc1: first document to compare
 * @doc2: second document to compare
 * @result: returns 1 if doc1 has a greater occurrences.
 * returns 0 if doc1 and doc2 has the same occurrences.
 * returns -1 if doc1 has a smaller occurrences.
 */
int compareOccurrences(DocNode *doc1, DocNode *doc2){
        if(doc1->occurrences > doc2->occurrences) return 1;
        else if(doc1->occurrences == doc2->occurrences) return 0;
        else return -1;
}


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
void PrintQueryResult(DocNode *printHead, char *webPageDir){
	DocNode *tempDoc;
	int docID;
	char docIDChar[MAX_LEN_DOCID_DIGITS];
	char *URL;
	char *fileName;
	int rank;
	int count = 0;

	// go through DocNode list to print
	while(printHead){
		tempDoc = printHead;		// stored to free later
		docID = printHead->documentID;	
		rank = printHead->occurrences;
		sprintf(docIDChar, "%d", docID);// make document ID into char*

		fileName = addPathToFile(webPageDir, docIDChar); 

		URL = GetURL(fileName);
		
		// print the appropriate message in the appropriate color according to rank
		if(rank >= GOOD_RANK){
			printf(ANSI_COLOR_GREEN "Document ID:%d URL:%s" ANSI_COLOR_RESET "\n", docID, URL);
		}
		else if(rank > OKAY_RANK){
			printf(ANSI_COLOR_CYAN "Document ID:%d URL:%s" ANSI_COLOR_RESET "\n", docID, URL);
                }
		else if(rank > BAD_RANK){
			printf(ANSI_COLOR_YELLOW "Document ID:%d URL:%s" ANSI_COLOR_RESET "\n", docID, URL);
		}
		else{
			printf(ANSI_COLOR_MAGENTA "Document ID:%d URL:%s" ANSI_COLOR_RESET "\n", docID, URL);
		}
			
		printHead = printHead->nextDoc;

		// free everything we just allocated
		free(tempDoc);		
		free(fileName);
		free(URL);
		count++; 	// add page count
	}
	printf("\nTotal Pages Found: %d\n", count);
}

/*
 * Gets url from a given crawler output file. Memory
 * allocated within the function and the caller is responsible
 * for the freeing of this memory.
 * @fileName: filename with the directory path to the 
 * directory of the crawler files.
 * @result: a char* to the URL from that file. 
 */
char *GetURL(char *fileName){
	char tempc;
	int letCount = 0;
	char *URL;
	
	FILE *file = fopen(fileName, "rb");
	if(!file) return NULL;
	
	tempc = fgetc(file);
	// keep getting the characters until a new line.
	while(tempc != '\n'){
                tempc = fgetc(file);
                // count the length of the word until new line
                letCount++;
        }
        // rewind pointer, and save the URL into an allocated memory
        fseek(file, -(letCount + 1), SEEK_CUR);
        URL = calloc(letCount + 1, sizeof(char));
	if(!URL) return NULL;

	// read the URL length from file into char buffer
        fread(URL, sizeof(char), letCount, file);

	fclose(file);
	return URL;
}
