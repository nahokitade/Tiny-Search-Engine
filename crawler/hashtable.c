/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Naho Kitade
 * Date: April 2014
 *
 * Functionality: a implementation for a hashtable structure used in crawler.
 * Used for quick search of a url to determine if the url was previously 
 * visited by the crawler.
 */
/* ========================================================================== */

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "hashtable.h"

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
int HashAdd(char *str, HashTable *hashTab){
	// allocate memory for the new node
	HashTableNode *addNode; 
	addNode = calloc(1, sizeof(HashTableNode));
	if(!addNode) return 0;

	// store new string as URL 
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

/* Checks if a URL is already in hashtable
 * @str: char buffer to look up in hash table
 * @hashTab: hash table to look up the string.
 * @result: Returns 0 if the str is not containted, and 1 if it is.
 */
int HashContains(char *str, HashTable *hashTab){
	unsigned long hashValue = JenkinsHash(str, MAX_HASH_SLOT);
	HashTableNode *presentNode;

	// go through the linked list in the place that the given string hashed to, to
	// see if the string is contained in the hash table.
	for(presentNode = hashTab->table[hashValue]; presentNode != NULL; presentNode = presentNode->next) {
        	if (strcmp(str, presentNode->url) == 0) return 1;
    	}
	return 0;
}

/* Deletes a single node in hash table. Mainly used by
 * DeleteHashTable function.
 * @toDelete: HashTableNode to delete (and free memory)
 * @result: Returns the HashTableNode pointer to the node that was
 * linked to the deleted node. (NULL if nothing is connected)
 */
HashTableNode *DeleteNode(HashTableNode *toDelete){
	HashTableNode *nextTemp = toDelete->next;
	free(toDelete->url);
	free(toDelete);
	return nextTemp;
}

/* Delete a chain of nodes at a certain index of hash table
 * @toDeleteHead: the head of the chain of nodes at a index
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteIndexChain(HashTableNode *toDeleteHead){
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
	for(i = 0; i <= MAX_HASH_SLOT; i++){
		HashTableNode *toDeleteHead = hashTab->table[i];
		if(!toDeleteHead) continue;
		DeleteIndexChain(toDeleteHead);
	}
	// free the whole hashtable
	free(hashTab);
	return 1;
}

