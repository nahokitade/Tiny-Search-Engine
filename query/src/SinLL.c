#include <stdlib.h>


#include "hashtable.h"
#include "SinLL.h"




SinLL *CreateSinLL(){
        SinLL *newSinLL;
        newSinLL = calloc(1, sizeof(SinLL));
        if(!newSinLL) return 0;
        return newSinLL;
}


/* append to a WebPage to the linked list
 * @webPage: WebPage to add to the linked list
 * @linkedList: linkedList to append the WebPage
 * Returns 1 on successful append, 0 if fail.
 */
int appendWord(char *word, SinLL *linkedList){
	// allocate memory for the node to append.
	WordsLL *addNode;
	addNode = calloc(1, sizeof(WordsLL));
	if(!addNode) return 0;
	addNode->word = word; 
	
	WordsLL *curWord = linkedList->tail->words;
	for( ; curWord->nextWord != NULL; curWord = curWord->nextWord);
	
	curWord->nextWord = addNode;

	return 1;
}

int appendNewWordChain(char *word, SinLL *linkedList){
	WordChainNode *newWCN;
	newWCN = calloc(1, sizeof(WordChainNode));
	if(!newWCN) return 0;

	WordsLL *addNode;
        addNode = calloc(1, sizeof(WordsLL));
        if(!addNode) return 0;
        addNode->word = word;
	newWCN->words = addNode;	

	if(IsEmptySinLL(linkedList)){
		linkedList->head = newWCN;
		linkedList->tail = newWCN;
		return 1;
	}
	else{
		linkedList->tail->nextWords = newWCN;
		linkedList->tail = linkedList->tail->nextWords;
		return 1;
	}
}

int AddDocNodeChain(WordChainNode *toAddNode, DocNode *docNodeChain){
	toAddNode->docs = docNodeChain;
	return 1;
}

/* remove from top of DLL
 * @linkedList: linkedList to remove from
 * Returns pointer of the WebPage that was removed, NULL if fail
 */
DocNode *removeTopDoc(SinLL *linkedList){
	if(IsEmptySinLL(linkedList)) return NULL;
	DocNode *toRetDocs = linkedList->head->docs; 
	WordChainNode *toFreeNode = linkedList->head; // need to keep this since this node needs to be freed
	linkedList->head = linkedList->head->nextWords; // make the new head the one after current head

	DeleteWordChainNode(toFreeNode); // free memory of ListNode struct.

	return toRetDocs;
}

int DeleteWordChainNode(WordChainNode *toFreeNode){
	DeleteWordsLLChain(toFreeNode->words);	
	free(toFreeNode);
	return 1;
}

int DeleteWordsLLChain(WordsLL *toFreeWords){
	while(toFreeWords){
		free(toFreeWords->word);
		toFreeWords = toFreeWords->nextWord;
	}
	return 1;
}

/* checks if list is empty
 * @linkedList: linkedList to check if empty
 * Returns 1 if list is empty, 0 if not empty
 */
int IsEmptySinLL(SinLL *linkedList){
	return (linkedList->head == NULL || linkedList->tail == NULL)? 1 : 0;
}

