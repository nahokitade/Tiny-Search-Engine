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

/* create a new hash table structure 
 */
HashTable *CreateNew();

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

/* adding to hashtable
 */
int HashAdd(char *str, HashTable *hashTab);

/* see if a URL is already in hashtable 
 * Returns 0 if the url is not containted, 
 */
int HashContains(char *str, HashTable *hashTab);

/* deletes a single node in hash table */
HashTableNode *DeleteNode(HashTableNode *toDelete);

/* Delete a chain of nodes at a certain index of hash table */
int DeleteIndexChain(HashTableNode *toDeleteHead);

/* Delete the whole hash table */
int DeleteHashTable(HashTable *hashTab);



#endif // HASHTABLE_H
