#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AND "AND"
#define OR "OR" 

int main(int argc, char* argv[]){
	int orNext = 0;
	int firstAdd = 1;
	char query[1000];

	HashTable *testInvertedIndex;
	testInvertedIndex = calloc(1, sizeof(HashTable));

	readFile(argv[1], testInvertedIndex);

	fputs("QUERY> ", stdout);
	fflush(stdout); 
   	fgets(query, sizeof(char)*1000, stdin);

	SinLL *wordList = CreateSinLL();

	pos = 0;
	char *word;  
	while((pos = GetNextWord(query, pos, &word)) > 0){
		if(strcmp(AND, word) == 0) continue;
		if(strcmp(OR, word) == 0){
			orNext = 1;
			continue;			
		}
		NormalizeWord(word);
		if(firstAdd){
			appendNewWordChain(word, wordList);
			firstAdd = 0;
                }
		if(orNext){
			appendNewWordChain(word, wordList);
			orNext = 0;
		}
		else{
			appendWord(word, wordList);
		}
	}
	
	WordChainNode *curWordChain = wordList->head;
	while(curWordChain){
		DocNode *tempProcessDocNode;
                DocNode *processDocNode;

		WordsLL *wordsProc = curWordChain->words;
		while(wordsProc){

			tempProcessDocNode = DocsFromWordNode(word, hashTable);
				
			processDocNode = CopyDocs(tempProcessDocNode);
			
			DocMergedID (processDocNode, curWordChain->docs);			

			ProcessAND(&processDocNode);

			AddDocNodeChain(curWordChain, processDocNode);
			
			wordsProc = wordsProc->nextWord;
		}

		curWordChain = curWordChain->nextWords;
	}
	
	curWordChain = wordList->head;
	
}



