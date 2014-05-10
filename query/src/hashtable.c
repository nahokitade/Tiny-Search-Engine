/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * Author: Naho Kitade
 * Date: May 2014
 *
 * Functionality:
 * 	hashtable created for the indexer. This is more a dictionary structure
 * 	than a hashtable. The Dictionary structure is needed for it's fast insert
 * 	and look up to count the occurences of a certain word in a certain file
 * 	containing html codes for a url. 
 * 
 */
/* ========================================================================== */

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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
	
	// see if a word is contained already in the hashtable. 
	// Two cases (word already contained or not) are processed
	// very differently
	addNode = HashContains(str, hashTab);
	if(!addNode){ // the word is not contained in the hashtable.

		// allocate memory for a hashtable node, WordNode
		// and DocNode
		addNode = calloc(1, sizeof(GenHashTableNode));
        	if(!addNode) return 0;
		
		WordNode *addWord;
		addWord = calloc(1, sizeof(GenHashTableNode));	
		if(!addWord) return 0;
		
		addWord->word = str; // add current word into the WordNode

		DocNode *addDoc;
		addDoc = calloc(1, sizeof(DocNode));
		if(!addDoc) return 0;

		// link the DocNode, WordNode, and hashtable node correctly.
		addDoc->documentID = curDocID; // store documentID passed into function
		addDoc->occurrences = 1; // count of occurences starts at 1
		addWord->docs = addDoc;
		addNode->hashKey = addWord;

		// find the index that the word hashes to
		unsigned long hashValue = JenkinsHash(str, MAX_HASH_SLOT);
		GenHashTableNode *presentNode = hashTab->table[hashValue]; 

		if(presentNode == NULL){
			// didn't find anything in slot, so add the current node
			// at slot.
			hashTab->table[hashValue] = addNode;
		}
		else{
			// found something in the slot, so go down the list until 
			// the last element and append 
			while(presentNode->next != NULL){
				presentNode = presentNode->next; 
			}
			presentNode->next = addNode;
		}
		return 1;
	}
	else{  // the word was already in the hashtable
		free(str); // we do not need the actual words anymore so free. 

		// iterate through the DocNode chain stored at the current WordNode
		// position, while keeping a previous pointer so we can use it later
		// to append to this DocNode chain
		DocNode *curDoc = ((WordNode*)addNode->hashKey)->docs;
		DocNode *prevDoc;
		for( ; curDoc != NULL; curDoc = curDoc->nextDoc){
			if(curDoc->documentID == curDocID){
				// if there is a document ID match, we have seen the
				// word already in a the same document to increment
				// its occurrence value and return
				curDoc->occurrences = (curDoc->occurrences + 1);
				return 1;
			}
			prevDoc = curDoc;
		}
		
                DocNode *addDoc;
                addDoc = calloc(1, sizeof(DocNode));
                if(!addDoc) return 0;

		// we didnt find a DocNode with the same document ID as the current
		// file so store the document ID into a new DocNode, and the occurrence
		// of this word in this document is the starting number, 1.
                addDoc->documentID = curDocID;
                addDoc->occurrences = 1;

		// append this new DocNode into the DocNode chain.
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

/* Deletes a single DocNode in hash table. Mainly used by
 * DeleteHashTable function.
 * @docDelete: DocNode to delete (and free memory)
 * @result: Returns the DocNode pointer to the node that was
 * linked to the deleted node. (NULL if nothing is connected)
 */
DocNode *DeleteDoc(DocNode *docDelete){
	DocNode *nextTemp = docDelete->nextDoc;
	free(docDelete);
	return nextTemp;
}

/* Delete a chain of WordNodes at a certain WordNode of hash table
 * @toDeleteHead: the head of the chain of WordNodes at a index
 * @result: Returns 1 if the delete is successful, and 0 if not.
 */
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

/* Counts a chain of WordNodes at a certain WordNode of hash table
 * @docCountHead: the head of the chain of WordNodes at a index
 * @result: Returns the number of documents counted.
 */
int CountDocuments(DocNode *docCountHead){
	DocNode *tempPtr = docCountHead;
        int count = 0;
	
	// iterate through the whole DocNode chain 
	// and count the number of DocNodes
	while(tempPtr){
                count++;
		tempPtr = tempPtr->nextDoc;
        }
        return count;
}

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
int saveFile(char *fileName, HashTable *hashTab){
	FILE *output = fopen(fileName, "w");
	int i;
	
	if(!output) return 0;
	
	// iterate throughthe whole hashtable
        for(i = 0; i < MAX_HASH_SLOT; i++){

                // skip all the empty indexes
		GenHashTableNode *curHashNode = hashTab->table[i];
                if(!curHashNode) continue;
		
		// go through the whole chain of hash table nodes at the current
		// index
		while(curHashNode){
			
			// dive into the hashtable node's WordNode
			WordNode *curWordNode = ((WordNode *)curHashNode->hashKey);
	
			// write out the word and document count at current line
			fprintf(output,"%s ", curWordNode->word);
			int docCount = CountDocuments(curWordNode->docs);
			fprintf(output,"%d ", docCount);
	
			// get the first document node of the chain of document nodes.
			DocNode *curDocNode = curWordNode->docs;

			// go through the whole chain of document nodes
			while(curDocNode){
				// write out the documentID and occurrences at 
				// current line
				fprintf(output,"%d ", curDocNode->documentID);
				fprintf(output,"%d ", curDocNode->occurrences);
				curDocNode = curDocNode->nextDoc;
			}

			// move to next hash node.
			curHashNode = curHashNode->next;
			fprintf(output,"\n");
		}
        }
	fclose(output);
	return 1;
}

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
int readFile(char *fileName, HashTable *hashTab){
	FILE *input = fopen(fileName, "r");		// file to read from
	int i;						
	int letCount = 0;				// counts length of read word
	int docID, occurrences, numFiles;		// ints read from the file
	char *word;					// stores the read word
	char tempc;					
	unsigned long hashValue;			
	WordNode *addWord;				// New WordNode, DocNode, and hash table node
	DocNode *addDoc, *prevDoc;			// in reconstruction of hashtable as well as 
	GenHashTableNode *curHashNode, *newHashNode;	// previous pointers to some constructs

	if(!input) return 0;

	// read until the end of a file 
	while((tempc = fgetc(input)) != EOF){	
		// read until next space (or non alphabet)
		while(isalpha(tempc)){
			tempc = fgetc(input);
			// count the length of the word until space
			letCount++;
		}
		
		// rewind pointer, and save the word into an allocated memory
		fseek(input, -(letCount + 1), SEEK_CUR);
		word = calloc(letCount + 1, sizeof(char));
		fread(word, sizeof(char), letCount, input);
		
		// find where the word naturally hashes to.
		hashValue = JenkinsHash(word, MAX_HASH_SLOT);
		curHashNode = hashTab->table[hashValue];

		// allocate memory for the new GenHashTableNode and WordNode
		newHashNode = calloc(1, sizeof(GenHashTableNode));
		if(!newHashNode) return 0;
		addWord = calloc(1, sizeof(WordNode));
		if(!addWord) return 0;
		
		// store the found word into the new WordNode and store the 
		// this WordNode into the newly created GenHashTableNode
		addWord->word = word;
		newHashNode->hashKey = addWord;

		// connect this newHashNode in the right place of the hashtable.
		if(!curHashNode){
			hashTab->table[hashValue] = newHashNode;
		}
		else{
			while(curHashNode->next) curHashNode = curHashNode->next;
			curHashNode->next = newHashNode;
		}

		// find the number of the files containing the current word 
		// (this is the word in the line of a file right after the word)
		fscanf(input ," %d ", &numFiles);

		// iterate through the current line for the rest of the numbers
		// encoding the documentID and occurrences of the word. We iterate
		// numFiles times.
		for(i = 0; i < numFiles; i++){
			
			// find the int encoding documentID and occurrences.
			fscanf(input, "%d %d ", &docID, &occurrences);

			// Need to make a new DocNode, so allocate memory for that
			// and store the newly found documentID and occurrences 
			// into this new DocNode
			addDoc = calloc(1, sizeof(DocNode));
			addDoc->documentID = docID;
			addDoc->occurrences = occurrences;

			// link the new DocNode to the right DocNode or WordNode
			// in the first iteration, the DocNode will be added to
			// the WordNode. All other iteration should link an existing 
			// DocNode to the current DocNode
			if(i == 0){
				addWord->docs = addDoc;
				prevDoc = addDoc;
			}
			else{
				prevDoc->nextDoc = addDoc;
				prevDoc = prevDoc->nextDoc;
			}
		}	
		// set the letter count back to 0.
		letCount = 0;
	}
	fclose(input);
	return 1;
}

