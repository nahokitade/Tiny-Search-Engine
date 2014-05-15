#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

int main(){
DocNode *tempProcessDocNode;
DocNode *processDocNode;
DocNode *processDocNode2;
int missCounter = 0;

HashTable *hashTable;
hashTable = CreateNewHashTab();

readFile("testindex2.dat", hashTable);

char *word = "kitty";

tempProcessDocNode = DocsFromWordNode(word, hashTable);

processDocNode = CopyDocs(tempProcessDocNode);

DocNode *procDNCur = processDocNode;
DocNode *tempProcDNCur = tempProcessDocNode;
while(procDNCur || tempProcDNCur){
	if(procDNCur->documentID != tempProcDNCur->documentID){
		missCounter++;
	}
	if(procDNCur->occurrences != tempProcDNCur->occurrences){
                missCounter++;
        }
	procDNCur = procDNCur->nextDoc;
	tempProcDNCur = tempProcDNCur->nextDoc;
}

if(missCounter) printf("FAIL: Copy is not identical to the original.\n");
else printf("SUCCESS: Copy is identical to the original.\n");

MergeSort(&processDocNode, compareIDs);

processDocNode2 = CopyDocs(processDocNode);

ProcessOR(&processDocNode);

SortByRank(&processDocNode);

printf("Printing ORed DocNode Query Result...\n");
PrintQueryResult(processDocNode, "/net/class/cs50/tse/crawler/lvl3/");

SortByRank(&processDocNode2);

printf("Printing ANDed DocNode Query Result...\n");
PrintQueryResult(processDocNode2, "/net/class/cs50/tse/crawler/lvl3/");

return 1;
}

