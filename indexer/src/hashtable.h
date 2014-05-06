/* ========================================================================== */
/* File: hashtable.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * This file contains the definitions for a hashtable of WordNodes and 
 * DocNodes.
 *
 */
/* ========================================================================== */
#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------- Prerequisites e.g., Requires "math.h"

//requires  <string.h>                          // strlen
//requires  <stdlib.h>

// ---------------- Constants
#define MAX_HASH_SLOT 10000                  // number of "buckets"

// ---------------- Structures/Types
typedef struct DocNode {
    int documentID;
    int occurrences;
    struct DocNode *nextDoc;
} DocNode;

typedef struct WordNode {
    char *word;                         // url previously seen
    struct DocNode *docs;
} WordNode;

typedef struct GenHashTableNode{
	void *hashKey;
	struct GenHashTableNode *next;
} GenHashTableNode;


typedef struct HashTable {
    GenHashTableNode *table[MAX_HASH_SLOT];     // actual hashtable
} HashTable;

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
 * @result: Returns 1 if add is successful, 0 if not. 
 */
int HashAdd(char *str, HashTable *hashTab,  int curDocID);


/* Checks if a URL is already in hashtable 
 * @str: char buffer to look up in hash table
 * @hashTab: hash table to look up the string.
 * @result: Returns NULL if the str is not containted, and the GenHashTableNode 
 * containing the match if it is.
 */
GenHashTableNode *HashContains(char *str, HashTable *hashTab);


/* Deletes a single node in hash table. Mainly used by 
 * DeleteHashTable function. 
 * @toDelete: GenHashTableNode to delete (and free memory)
 * @result: Returns the GenHashTableNode pointer to the node that was
 * linked to the deleted node. (NULL if nothing is connected) 
 */
GenHashTableNode *DeleteNode(GenHashTableNode *toDelete);


/* Delete a chain of nodes at a certain index of hash table 
 * @toDeleteHead: the head of the chain of nodes at a index
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteIndexChain(GenHashTableNode *toDeleteHead);


/* Delete the whole hash table 
 * @hashTab: A pointer to the hash table to delete
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteHashTable(HashTable *hashTab);

/* Deletes a single DocNode in hash table. Mainly used by
 * DeleteHashTable function.
 * @docDelete: DocNode to delete (and free memory)
 * @result: Returns the DocNode pointer to the node that was
 * linked to the deleted node. (NULL if nothing is connected)
 */
DocNode *DeleteDoc(DocNode *docDelete);

/* Delete a chain of WordNodes at a certain WordNode of hash table
 * @toDeleteHead: the head of the chain of WordNodes at a index
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
int DeleteDocChain(DocNode *docDeleteHead);

/* Counts a chain of WordNodes at a certain WordNode of hash table
 * @docCountHead: the head of the chain of WordNodes at a index
 * @result: Returns the number of documents counted.
 */
int CountDocuments(DocNode *docCountHead);

/*
 * Makes the indexer hashtable into file with formatting:
 *   word fileID occurrences fileID occurrences ... fileID occurrences \n
 * One line is written per a word that occurred in at least one of
 * the htmls from the crawler indexed. 
 * @fileName: fileName of the new created file to be saved
 * @hashTab: hashTable to create into the file of the above format
 * @result: the file form of the given hashTab at fileName. Returns
 * 1 if successful and 0 if not.
 */
int saveFile(char *fileName, HashTable *hashTab);

/*
 * Makes a indexer hashtable from a file with formatting:
 *   word fileID occurrences fileID occurrences ... fileID occurrences \n
 * One line should be written per a word that occurred in at least one of
 * the htmls from the crawler indexed.
 * @fileName: fileName of the file to be made into a hashtable
 * @hashTab: hashTable to create from a file of the above format
 * @result: the modified hashTab created from the file, fileName. Returns 1 
 * if successful and 0 if not. 
 */
int readFile(char *fileName, HashTable *hashTab);

#endif // HASHTABLE_H

