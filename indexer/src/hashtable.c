/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Naho Kitade
 * Date: April 2014
 *
 * You should include in this file your functionality for the hashtable as
 * described in the assignment and lecture.
 */
/* ========================================================================== */

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>
#include <stdio.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "file.h"

// ---------------- Function Definitions
unsigned long JenkinsHash(const char *str, unsigned long mod)
{
    size_t len = strlen(str);
    unsigned long hash, i;

    for(hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % mod;
}

/* Creates a new HashTable structure
 * @result: a pointer to a HashTableStructure
 * pointer. 
 * The caller is responsible for freeing this
 * memory.
 */
HashTable *CreateNewHashTab(){
	HashTable *hashP;
	hashP = calloc(1, sizeof(HashTable));
	if(!hashP) return NULL;
	return hashP;
}

/* Adding a specific string to hashtable
 * @str: char buffer to add to hash
 * @hashTab: hash table to add the string
 */
int HashAdd(char *str, HashTable *hashTab, int curDocID){

	// allocate memory for the new node
	GenHashTableNode *addNode; 
	
	addNode = HashContains(str, hashTab);

	if(!addNode){
		addNode = calloc(1, sizeof(GenHashTableNode));
        	if(!addNode) return 0;
		
		WordNode *addWord;
		addWord = calloc(1, sizeof(GenHashTableNode));	
		if(!addWord) return 0;
		
		addWord->word = str;

		DocNode *addDoc;
		addDoc = calloc(1, sizeof(DocNode));
		if(!addDoc) return 0;

		addDoc->documentID = curDocID;
		addDoc->occurrences = 1;

		addWord->docs = addDoc;

		addNode->hashKey = addWord;

		unsigned long hashValue = JenkinsHash(str, MAX_HASH_SLOT);
		
		GenHashTableNode *presentNode = hashTab->table[hashValue]; 

		if(presentNode == NULL){
			hashTab->table[hashValue] = addNode; // didn't find anything in slot, so add the current node at slot.
		}
		else{
			// found something in the slot, so go down the list until the last element and 
			// append 
			while(presentNode->next != NULL){
				presentNode = presentNode->next; 
			}
			presentNode->next = addNode;
		}
		return 1;
	}
	else{
		DocNode *curDoc = ((WordNode*)addNode->hashKey)->docs;
		DocNode *prevDoc;
		for( ; curDoc != NULL; curDoc = curDoc->nextDoc){
			if(curDoc->documentID == curDocID){
				curDoc->occurrences = (curDoc->occurrences + 1);
				return 1;
			}
			prevDoc = curDoc;
		}
		
                DocNode *addDoc;
                addDoc = calloc(1, sizeof(DocNode));
                if(!addDoc) return 0;

                addDoc->documentID = curDocID;
                addDoc->occurrences = 1;

		prevDoc->nextDoc = addDoc;

		return 1;
	}
}

/* Checks if a URL is already in hashtable
 * @str: char buffer to look up in hash table
 * @hashTab: hash table to look up the string.
 * @result: Returns 0 if the str is not containted, and 1 if it is.
 */
GenHashTableNode *HashContains(char *str, HashTable *hashTab){
	unsigned long hashValue = JenkinsHash(str, MAX_HASH_SLOT);
	GenHashTableNode *presentNode;

	// go through the linked list in the place that the given string hashed to, to
	// see if the string is contained in the hash table.
	for(presentNode = hashTab->table[hashValue]; presentNode != NULL; presentNode = presentNode->next) {
        	if (strcmp(str, ((WordNode *)presentNode->hashKey)->word) == 0) return presentNode;
    	}
	return NULL;
}

DocNode *DeleteDoc(DocNode *docDelete){
	DocNode *nextTemp = docDelete->nextDoc;
	free(docDelete);
	return nextTemp;
}


int DeleteDocChain(DocNode *docDeleteHead){
	while(docDeleteHead){
		docDeleteHead = DeleteDoc(docDeleteHead);
	}
	return 1;
}

/* Deletes a single node in hash table. Mainly used by
 * DeleteHashTable function.
 * @toDelete: HashTableNode to delete (and free memory)
 * @result: Returns the HashTableNode pointer to the node that was
 * linked to the deleted node. (NULL if nothing is connected)
 */
GenHashTableNode *DeleteNode(GenHashTableNode *toDelete){
	GenHashTableNode *nextTemp = toDelete->next;
	free(((WordNode *)toDelete->hashKey)->word);
	DeleteDocChain(((WordNode *)toDelete->hashKey)->docs);
	free(((WordNode *)toDelete->hashKey));
	free(toDelete);
	return nextTemp;
}

/* Delete a chain of nodes at a certain index of hash table
 * @toDeleteHead: the head of the chain of nodes at a index
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteIndexChain(GenHashTableNode *toDeleteHead){
	while(toDeleteHead){
		toDeleteHead = DeleteNode(toDeleteHead);
	}
	return 1;
}

/* Delete the whole hash table
 * @hashTab: A pointer to the hash table to delete
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteHashTable(HashTable *hashTab){
	if(!hashTab) return 0;

	int i;
	// go though all slots in the hashtable and delete all the 
	// nodes in the linked list.
	for(i = 0; i < MAX_HASH_SLOT; i++){
		GenHashTableNode *toDeleteHead = hashTab->table[i];
		if(!toDeleteHead) continue;
		DeleteIndexChain(toDeleteHead);
	}
	// free the whole hashtable
	free(hashTab);
	return 1;
}


int CountDocuments(DocNode *docCountHead){
	DocNode *tempPtr = docCountHead;
        int count = 0;
	while(tempPtr){
                count++;
		tempPtr = tempPtr->nextDoc;
        }
        return count;
}

int saveFile(char *fileName, HashTable *hashTab){
	FILE *output = fopen(fileName, "a+");
	int i;

        for(i = 0; i <= MAX_HASH_SLOT; i++){
                GenHashTableNode *curHashNode = hashTab->table[i];
                if(!curHashNode) continue;

		while(curHashNode){

			WordNode *curWordNode = ((WordNode *)curHashNode->hashKey);
	
			fprintf(output,"%s ", curWordNode->word);
			int docCount = CountDocuments(curWordNode->docs);
			fprintf(output,"%d ", docCount);
	
			DocNode *curDocNode = curWordNode->docs;

			while(curDocNode){
				fprintf(output,"%d ", curDocNode->documentID);
				fprintf(output,"%d ", curDocNode->occurrences);
				curDocNode = curDocNode->nextDoc;
			}

		curHashNode = curHashNode->next;
		}
		fprintf(output,"\n");
        }
	fclose(output);
	return 1;
}


int readFile(char *fileName, HashTable *hashTab){
	char *input = fileToString(fileName);
	



	return 1;
}

