#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

int main(){
DocNode *tempProcessDocNode;
DocNode *processDocNode;

HashTable *hashTable;
hashTable = CreateNewHashTab();

readFile("testindex.dat", hashTable);

char *word = "kitty";

tempProcessDocNode = DocsFromWordNode(word, hashTable);

PrintDocChain(tempProcessDocNode);

processDocNode = CopyDocs(tempProcessDocNode);

printf("Printing copied DocNode...\n");
PrintDocChain(processDocNode);

MergeSort(&processDocNode, compareIDs);

printf("Printing original DocNode...\n");

PrintDocChain(tempProcessDocNode);

printf("Printing sorted copied DocNode...\n");
PrintDocChain(processDocNode);

ProcessOR(processDocNode);

printf("Printing ORed DocNode...\n");
PrintDocChain(processDocNode);

return 1;
}

