#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "SinLL.h"
#include "queryProcess.h"
#include "web.h"

#define AND "AND"
#define OR "OR" 

int main(int argc, char* argv[]){

	int success;
	int orNext;
	int firstAdd;

	HashTable *invertedIndex;
	invertedIndex = calloc(1, sizeof(HashTable));

	readFile(argv[1], invertedIndex);


	while(1){
		char *getsSucc;
		int totSize = 10;
		int size = 10;
		int i = 0;
		char *query;
        	char *temp;
		fputs("QUERY> ", stdout);
		fflush(stdout); 
		query = calloc(size, sizeof(char));
		temp = query;
	   	getsSucc = fgets(temp, sizeof(char)*size+i, stdin);
		temp = &query[totSize-1];
		if(!getsSucc) break;
		while((strlen(getsSucc)+1+i) == size && query[totSize-2] != '\n'){
			i = 1;
			totSize += size;
			query = realloc(query, totSize);
			getsSucc = fgets(temp, sizeof(char)*size+i, stdin);
			temp = &query[totSize-i];
		}
		
		printf("query is: %s", query);
		
		orNext = 0;
		firstAdd = 1;

		SinLL *wordList = CreateSinLL();

		char *wordP;  
		wordP = strtok(query," ");
		while(wordP){
			if(wordP[strlen(wordP)-1] == '\n'){
				wordP[strlen(wordP)-1] = 0;
			}
			if(strcmp(AND, wordP) == 0){ 
				wordP = strtok (NULL, " ");
				continue;
			}
			if(strcmp(OR, wordP) == 0){
				orNext = 1;
				wordP = strtok (NULL, " ");
				continue;			
			}
			NormalizeWord(wordP);
			if(firstAdd){
				appendNewWordChain(wordP, wordList);
				firstAdd = 0;
        	        }
			else if(orNext){
				appendNewWordChain(wordP, wordList);
				orNext = 0;
			}
			else{
				appendWord(wordP, wordList);
			}
			wordP = strtok (NULL, " ");
		}
	
		WordChainNode *curWordChain = wordList->head;
		while(curWordChain){
			firstAdd = 1;
			DocNode *tempProcessDocNode;
                	DocNode *processDocNode;

			WordsLL *wordsProc = curWordChain->words;
			while(wordsProc){
	
				tempProcessDocNode = DocsFromWordNode(wordsProc->word, invertedIndex);
					
				processDocNode = CopyDocs(tempProcessDocNode);

				DocMergedID(&processDocNode, &(curWordChain->docs));			

				if(!firstAdd){
					ProcessAND(&processDocNode);
				}

				AddDocNodeChain(curWordChain, processDocNode);
			
				wordsProc = wordsProc->nextWord;
				firstAdd = 0;
			}

			curWordChain = curWordChain->nextWords;
		}
	
		curWordChain = wordList->head;
		DocNode *curDocs;
		DocNode *nextDocs;
		success = removeTopDoc(wordList, &curDocs);
		if(success){
			success = removeTopDoc(wordList, &nextDocs);
			while(success){
				DocMergedID(&curDocs, &nextDocs);
		
				ProcessOR(&curDocs);

				success = removeTopDoc(wordList, &nextDocs);
			}
		}
		else{
			printf("No match was found...\n"); 
			continue;
		}
	
		SortByRank(&curDocs);
	
		PrintQueryResult(curDocs, argv[2]);
		free(wordList);
		//DeleteHashTable(invertedIndex);
		free(query);
		//return 1;
	}
	DeleteHashTable(invertedIndex);
	return 1;
}



