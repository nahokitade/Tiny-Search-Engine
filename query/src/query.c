/*	file.c	one-line description

	Copyright 2013 (if any)

	License (if any)

	Project name:
	Component name:

	This file contains ...
	
	Primary Author:	
	Date Created:	

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "SinLL.h"
#include "queryProcess.h"
#include "web.h"
#include "file.h"

// ---------------- Constant definitions 
#define AND "AND"
#define OR "OR"
#define MAX_QUERY_LEN 100
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/


int main(int argc, char* argv[]){
	int success;			// contains 1 if removing from SinLL was successful
	int orNext;			// contains > 0 if the next word in query should be ORed
	int firstAdd;			// contains > 0 if the addition to SinLL is the first addition
	int tempChar;			// used to flush the stdin for too long inputs
	char query[MAX_QUERY_LEN];	// contains string of query
	char *getsSucc;			// determines if EOF is met.

	if(argc != 3){		// invalid number of arguments
		fprintf(stderr, ANSI_COLOR_RED "Usage: query [INDEXER OUTPUT FILE] [CRAWLER OUTPUT FILE DIRECTORY]"  ANSI_COLOR_RESET "\n");
		return 0;
	}

	if(!(access(argv[1], F_OK) != -1)){
		fprintf(stderr, ANSI_COLOR_RED "First argument is not a valid file."  ANSI_COLOR_RESET "\n");
                return 0;
	}

	if(!IsDir(argv[2])){	// invalid "directory"
		fprintf(stderr, ANSI_COLOR_RED "Second argument is not a directory."  ANSI_COLOR_RESET "\n");
		return 0;
	}

	HashTable *invertedIndex;
	invertedIndex = calloc(1, sizeof(HashTable));

	readFile(argv[1], invertedIndex);	// recreate inverted index


	while(1){
		// get the query from user
		fputs("QUERY> ", stdout);
  		fflush(stdout); 
		
		getsSucc = fgets(query, sizeof(char)*MAX_QUERY_LEN, stdin);
		if(!getsSucc) break;	// EOF means exiting program

		// this means the user input more than MAX_QUERY_LEN characters to query
		if(getsSucc[strlen(getsSucc)-1] != '\n'){
			fprintf(stderr, ANSI_COLOR_RED "Query length is over the maximum 1000 characters!"     ANSI_COLOR_RESET "\n");
			while((tempChar = getchar()) != '\n' && tempChar != EOF){
				/*do nothing*/
			}
			continue;
		}

		// at this stage, the next add is the first add, and we have not seen a 
		// OR yet.
		orNext = 0;
		firstAdd = 1;

		SinLL *wordList = CreateSinLL();

		char *wordP;  
		wordP = strtok(query," ");

		// get all the words from the query
		while(wordP){
			// last word in query will have a \n attached to it, so if 
			// there is a \n at the end of a word, take that out
			if(wordP[strlen(wordP)-1] == '\n'){
				wordP[strlen(wordP)-1] = 0;
			}

			// ignore ANDs.
			if(strcmp(AND, wordP) == 0){ 
				wordP = strtok (NULL, " ");
				continue;
			}
	
			// ignore ORs but make sure you OR the next coming word.
			if(strcmp(OR, wordP) == 0){
				orNext = 1;
				wordP = strtok (NULL, " ");
				continue;			
			}

			// make word lowercase. If this word is the first one, or 
			// the previous word was OR, make a new node in the SinLL 
			// of WordChainList
			NormalizeWord(wordP);
			if(firstAdd){
				appendNewWordChain(wordP, wordList);
				firstAdd = 0;
        	        }
			else if(orNext){
				appendNewWordChain(wordP, wordList);
				orNext = 0;
			}
			// if not the previous two cases, just append the word to 
			// current node.
			else{
				appendWord(wordP, wordList);
			}
			wordP = strtok (NULL, " ");
		}
		
		// first process will AND all the words contained in each WordChainNodes
		// of the list.
		WordChainNode *curWordChain = wordList->head;
		while(curWordChain){		// while there are more nodes
			firstAdd = 1;
			DocNode *tempProcessDocNode;	// contains original DocNodes to AND from index
                	DocNode *processDocNode;	// contains copied version of above.

			WordsLL *wordsProc = curWordChain->words;	// gettng first set of words.
			while(wordsProc){	// while there are more words
	
				// get DocNodes associated with that word from the inverted index and 
				// copy it as to not mess up the inverted index. 
				tempProcessDocNode = DocsFromWordNode(wordsProc->word, invertedIndex);	
				processDocNode = CopyDocs(tempProcessDocNode);
				
				// merge the above DocNodes with the DocNodes saved at the current
				// WordChainNode.
				DocMergedID(&processDocNode, &(curWordChain->docs));			

				// if it is the first add, we want to skip this step. If it isnt the 
				// first add, and the above DocNodes with the ocNodes saved at the current
				// WordChainNode.	
				if(!firstAdd){
					ProcessAND(&processDocNode);
				}

				// Add the processed (ANDed) DocNode chain at the current
				// WordChainNode.
				AddDocNodeChain(curWordChain, processDocNode);
			
				// iterate through to the next word at the current node.
				wordsProc = wordsProc->nextWord;
				firstAdd = 0;
			}
			// move on to the next node. 
			curWordChain = curWordChain->nextWords;
		}
		
		// now we OR each individual WordChainNodes' DocNode lists.
		curWordChain = wordList->head;
		DocNode *curDocs;
		DocNode *nextDocs;
		success = removeTopDoc(wordList, &curDocs);	// gets the DocNode list from the first node
		// if there you fail here, it means that the list is empty/
		if(success){
			success = removeTopDoc(wordList, &nextDocs);	// gets the next DocNode list from
									// the next WordChainNode
			while(success){		// if you fail here, there was only one WordChainNode in the list

				// process the DocNodes together by ORing them
				DocMergedID(&curDocs, &nextDocs);
				ProcessOR(&curDocs);
				// move on to the next DocNodes from the next WordChainNode.
				success = removeTopDoc(wordList, &nextDocs);
			}
		}
		// the list was empty, so found nothing. 
		else{
			printf("Found 0 pages\n"); 
			continue;
		}

		// sort by the rank and print the results.
		SortByRank(&curDocs);
		PrintQueryResult(curDocs, argv[2]);
		free(wordList);		// clean up for next query
	}
	DeleteHashTable(invertedIndex); 	// final clean up
	return 1;
}



