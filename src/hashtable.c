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

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "hashtable.h"

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

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

int i;

HashTable *CreateNewHashTab(){
	HashTable *hashP;
	hashP = calloc(1, sizeof(HashTable));
	if(!hashP) return NULL;
	return hashP;
}

//WHERE TO ALLOCATE MEMORY? WHERE TO MALLOC??
int HashAdd(char *str, HashTable *hashTab){
	HashTableNode *addNode; 
	addNode = calloc(1, sizeof(HashTableNode));
	if(!addNode) return 0;

	addNode->url = str;
	addNode->next = NULL; 
	unsigned long hashValue = JenkinsHash(str, MAX_HASH_SLOT);
	
	HashTableNode *presentNode = hashTab->table[hashValue]; 

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

/* see if a URL is already in hashtable
 *  * Returns 0 if the url is not containted,
 *   */
int HashContains(char *str, HashTable *hashTab){
	unsigned long hashValue = JenkinsHash(str, MAX_HASH_SLOT);
	HashTableNode *presentNode;

	for(presentNode = hashTab->table[hashValue]; presentNode != NULL; presentNode = presentNode->next) {
        	if (strcmp(str, presentNode->url) == 0) return 1;
    	}
	
	return 0;
}

/* delete a node */
HashTableNode *DeleteNode(HashTableNode *toDelete){
	HashTableNode *nextTemp = toDelete->next;
	free(toDelete->url);
	free(toDelete);
	return nextTemp;
}

/* deletes a chain in one index */
int DeleteIndexChain(HashTableNode *toDeleteHead){
	while(toDeleteHead){
		toDeleteHead = DeleteNode(toDeleteHead);
	}
	return 1;
}


/* delete whole hash table */
int DeleteHashTable(HashTable *hashTab){
	if(!hashTab) return 0;

	int i;
	for(i = 0; i <= MAX_HASH_SLOT; i++){
		HashTableNode *toDeleteHead = hashTab->table[i];
		if(!toDeleteHead) continue;
		DeleteIndexChain(toDeleteHead);
	}
	free(hashTab);
	return 1;
}

