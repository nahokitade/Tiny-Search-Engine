#include <stdio.h>

#include "hashtable.h"

int main(){
	HashTable *hashTable = CreateNewHashTab();

	readFile( "readTest", hashTable);

	GenHashTableNode *shouldNotBeNull = HashContains("animals", hashTable);

	int testNum = (shouldNotBeNull)? 1 : 0;

	printf("If look up is successful, this should be 1. Verify: %d\n", testNum);

	saveFile( "readTestOut", hashTable);

return 1;

}
