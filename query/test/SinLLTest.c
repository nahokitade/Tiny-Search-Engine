/*	SinLLTest.c		Unit testing for SinLL.c file

	Project name:   Tiny Search Engine
	Component name: query

	This file contains unit testing for the SinLL.c file.
	
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
#include "SinLL.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/

int main(){

// create a list and keep adding different words
SinLL *wordList = CreateSinLL();

char *word;
word = calloc(20, sizeof(char));
strcpy(word, "kitty");

// testing appendNewWordChain function
appendNewWordChain(word, wordList);

char *word2;
word2 = calloc(20, sizeof(char));
strcpy(word2, "doggy");

appendNewWordChain(word2, wordList);

char *word5;
word5 = calloc(20, sizeof(char));
strcpy(word5, "bat");

// testing appendWord function
appendWord(word5, wordList);

char *word4;
word4 = calloc(20, sizeof(char));
strcpy(word4, "cat");

// doing a few more adds
appendNewWordChain(word4, wordList);

char *word3;
word3 = calloc(20, sizeof(char));
strcpy(word3, "turtle");

appendWord(word3, wordList);

WordChainNode *printChain = wordList->head; 
WordChainNode *tempPrintChain;

// printing the words in the list one by one
while(printChain){
	WordsLL *words = printChain->words;
	while(words){
		printf("Word is: %s\n", (words->word));
		free(words->word);
		words = words->nextWord;
	}
	printf("\n");
	tempPrintChain = printChain;
	DeleteWordChainNode(tempPrintChain);
	printChain = printChain->nextWords;
}
// expected results
printf("Words should be kitty  doggy bat  cat turtle.");
free(wordList);
return 1;
}
