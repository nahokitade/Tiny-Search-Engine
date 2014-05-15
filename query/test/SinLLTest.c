#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashtable.h"
#include "SinLL.h"


int main(){

SinLL *wordList = CreateSinLL();

char *word;
word = calloc(20, sizeof(char));
strcpy(word, "kitty");

appendNewWordChain(word, wordList);

char *word2;
word2 = calloc(20, sizeof(char));
strcpy(word2, "doggy");

appendNewWordChain(word2, wordList);

char *word5;
word5 = calloc(20, sizeof(char));
strcpy(word5, "bat");

appendWord(word5, wordList);

char *word4;
word4 = calloc(20, sizeof(char));
strcpy(word4, "cat");

appendNewWordChain(word4, wordList);

char *word3;
word3 = calloc(20, sizeof(char));
strcpy(word3, "turtle");

appendWord(word3, wordList);

WordChainNode *printChain = wordList->head; 

while(printChain){
	WordsLL *words = printChain->words;
	while(words){
		printf("Word is: %s\n", (words->word));
		words = words->nextWord;
	}
	printf("\n");
	printChain = printChain->nextWords;
}
printf("Words should be kitty  doggy bat  cat turtle.");
}
