#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"
#include "LLMergeSort.h"
#include "queryProcess.h"

int main(){
DocNode *tempProcessDocNode;
DocNode *processDocNode;
DocNode *processDocNode2;

HashTable *hashTable;
hashTable = CreateNewHashTab();

readFile("testindex2.dat", hashTable);

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

processDocNode2 = CopyDocs(processDocNode);

ProcessOR(&processDocNode);

printf("Printing ORed DocNode...\n");
PrintDocChain(processDocNode);

ProcessAND(&processDocNode2);
printf("Printing ANDed DocNode...\n");
PrintDocChain(processDocNode2);

SortByRank(&processDocNode);

printf("Printing Ranked ORed DocNode...\n");
PrintDocChain(processDocNode);

printf("Printing ORed DocNode Query Result...\n");
PrintQueryResult(processDocNode, "/net/class/cs50/tse/crawler/lvl3/");

SortByRank(&processDocNode2);
printf("Printing Ranked ANDed DocNode...\n");
PrintDocChain(processDocNode2);

printf("Printing ANDed DocNode Query Result...\n");
PrintQueryResult(processDocNode2, "/net/class/cs50/tse/crawler/lvl3/");

return 1;
}

