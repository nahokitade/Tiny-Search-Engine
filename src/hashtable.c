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

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
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

HashTable *CreateNew(){
	if((HashTable *hashP = calloc(sizeof(HashTable))) == NULL) return NULL;
	return hashP;
}

//WHERE TO ALLOCATE MEMORY? WHERE TO MALLOC??
int HashAdd(const char *str, HashTable *hashTab){
	if((HashTableNode *addNode = calloc(sizeof(HashTableNode))) == NULL) return 0;
	addNode->url = str;
	addNode->next = NULL; //CAN YOU ASSIGN ANYTHING TO NULL??
	unsigned long hashValue = JenkinsHash(*str, MAX_HASH_SLOT);
	
	HashTableNode *presentNode = hashTab[hashValue]; //TEST HERE.

	if(presentNode == NULL){
		hashTab[hashValue] = addNode; // didn't find anything in slot, so add the current node at slot.
	}
	else{
		// found something in the slot, so go down the list until the last element and 
		// append 
		while(presentNode->next != NULL){
			presentNode = presentNode->next; // DO I NEED -> HERE????????
		}
		presentNode->next = addNode;
	}
	return 1;
}

/* see if a URL is already in hashtable
 *  * Returns 0 if the url is not containted,
 *   */
int HashContains(const char *str, HashTable *hashTab){
	unsigned long hashValue = JenkinsHash(*str, MAX_HASH_SLOT);
	if(presentNode == NULL){
		return 0;
        }
        else{
                while(presentNode.next != NULL || strcmp(presentNode.url, *str) != 0){
                        presentNode = presentNode->next;
                }
                return (presentNode != NULL)? 1 : 0;
        }
}

/* delete a node */
HashTableNode *DeleteNode(HashTableNode *toDelete){
	HashTableNode nextTemp = toDelete->next;
	free(toDelete->url);
	free(toDelete->next);
	return nextTemp;
}

/* deletes a chain in one index */
int DeleteIndexChain(HashTableNode *toDeleteHead){
	while(toDeleteHead){
		toDeleteHead = DeleteNode(toDeleteHead)
	}
	return 1;
}


/* delete whole hash table */
int DeleteHashTable(HashTable *hashTab){
	if(!hashTab) return 0;

	int i;
	for(i = 0; i <= MAX_HASH_SLOT; i++){
		HashTableNode *toDeleteHead = hashTab[i];
		if(!HashTableNode) continue;
		DeleteIndexChain(toDeleteHead);
	}
	free(hashTab);
	return 1;
}

}