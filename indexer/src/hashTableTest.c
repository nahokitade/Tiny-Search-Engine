#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"

int main(){
HashTable *hashTable = CreateNewHashTab();

char *str1;

str1 = calloc(10, sizeof(char));

str1 = strcpy(str1, "cats");

HashAdd(str1, hashTable, 1);

char *str2;

str2 = calloc(10, sizeof(char));

str2 = strcpy(str2, "dogs");

GenHashTableNode *shouldBeNull = HashContains(str2, hashTable);

int testNum = (shouldBeNull)? 1 : 0;

printf("If look up is successful, this should be 0. Verify: %d\n", testNum);

GenHashTableNode *shouldNotBeNull = HashContains(str1, hashTable);

testNum = (shouldNotBeNull)? 1 : 0;

printf("If look up is successful, this should be 1. Verify: %d\n", testNum);

printf("DocumentID = %d     Occurrences = %d\n", ((WordNode *)shouldNotBeNull->hashKey)->docs->documentID, ((WordNode *)shouldNotBeNull->hashKey)->docs->occurrences);

HashAdd(str1, hashTable, 1);

shouldNotBeNull = HashContains(str1, hashTable);

testNum = (shouldNotBeNull)? 1 : 0;

printf("If look up is successful, this should be 1. Verify: %d\n", testNum);

DocNode *curDoc = ((WordNode *)shouldNotBeNull->hashKey)->docs;

while(curDoc){
	printf("DocumentID = %d     Occurrences (should be 2) = %d\n", curDoc->documentID, curDoc->occurrences);

	curDoc = curDoc->nextDoc;
}

HashAdd(str2, hashTable, 20);

shouldNotBeNull = HashContains(str2, hashTable);

testNum = (shouldNotBeNull)? 1 : 0;

printf("If look up is successful, this should be 1. Verify: %d\n", testNum);

curDoc = ((WordNode *)shouldNotBeNull->hashKey)->docs;

while(curDoc){
        printf("DocumentID (should be 20) = %d     Occurrences (should be 1) = %d\n", curDoc->documentID, curDoc->occurrences);

        curDoc = curDoc->nextDoc;
}

HashAdd(str1, hashTable, 28);

shouldNotBeNull = HashContains(str1, hashTable);

testNum = (shouldNotBeNull)? 1 : 0;

printf("If look up is successful, this should be 1. Verify: %d\n", testNum);

curDoc = ((WordNode *)shouldNotBeNull->hashKey)->docs;

while(curDoc){
        printf("DocumentID = %d     Occurrences = %d\n", curDoc->documentID, curDoc->occurrences);

        curDoc = curDoc->nextDoc;
}

saveFile("test", hashTable);

//free(str1);
//free(str2);
DeleteHashTable(hashTable);
//free(hashTable);

return 1;

}
