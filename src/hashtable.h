/* ========================================================================== */
/* File: hashtable.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a hashtable of urls.
 *
 */
/* ========================================================================== */
#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "common.h"                          // common functionality

// ---------------- Constants
#define MAX_HASH_SLOT 10000                  // number of "buckets"

// ---------------- Structures/Types

typedef struct HashTableNode {
    char *url;                               // url previously seen
    struct HashTableNode *next;              // pointer to next node
} HashTableNode;

typedef struct HashTable {
    HashTableNode *table[MAX_HASH_SLOT];     // actual hashtable
} HashTable;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/* Creates a new hash table structure 
 * Returns a pointer to the newly allocated hash table
 * Must free memory after use by calling DeleteHashTable.
 */
HashTable *CreateNewHashTab();


/*
 * jenkins_hash - Bob Jenkins' one_at_a_time hash function
 * @str: char buffer to hash
 * @mod: desired hash modulus
 *
 * Returns hash(str) % mod. Depends on str being null terminated.
 * Implementation details can be found at:
 *     http://www.burtleburtle.net/bob/hash/doobs.html
 */
unsigned long JenkinsHash(const char *str, unsigned long mod);


/* Adding a specific string to hashtable
 * @str: char buffer to add to hash
 * @hashTab: hash table to add the string
 */
int HashAdd(char *str, HashTable *hashTab);


/* Checks if a URL is already in hashtable 
 * @str: char buffer to look up in hash table
 * @hashTab: hash table to look up the string.
 * Returns 0 if the str is not containted, and 1 if it is.
 */
int HashContains(char *str, HashTable *hashTab);


/* Deletes a single node in hash table. Mainly used by 
 * DeleteHashTable function. 
 * @toDelete: HashTableNode to delete (and free memory)
 * Returns the HashTableNode pointer to the node that was
 * linked to the deleted node. (NULL if nothing is connected) 
 */
HashTableNode *DeleteNode(HashTableNode *toDelete);


/* Delete a chain of nodes at a certain index of hash table 
 * @toDeleteHead: the head of the chain of nodes at a index
 * Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteIndexChain(HashTableNode *toDeleteHead);


/* Delete the whole hash table 
 * @hashTab: A pointer to the hash table to delete
 * Return 1 if the delete is successful, and 0 if not.
 */
int DeleteHashTable(HashTable *hashTab);



#endif // HASHTABLE_H
