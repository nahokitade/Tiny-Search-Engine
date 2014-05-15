/*	indexer.c	indexer component of the tiny search engine 

	Project name:    Tiny Search Engine
	Component name:  Indexer

	This file contains ...
	
	Primary Author:	 Naho Kitade 
	Date Created:	 May 2014

	Special considerations:  
			 Files that are passed into this program, if
			 it exists, will be written over with the 
			 outputs of Indexer. If it does not exist, the 
			 file will be created. An existing file is assumed
			 to have reading and writing permissions.
	
======================================================================*/
// ---------------- Open Issues 

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"
#include "file.h"
#include "web.h"

// ---------------- Constant definitions 
#define LINES_TO_SKIP 2
#define NORM_ARG_COUNT 3
#define TEST_ARG_COUNT 5
#define MIN_WORD_LEN 3

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int buildIndexFromDirectory(char *dirName, HashTable *invInd);
char *addPathToFile(char *path, char *fileName);
int testDirSlash(const char *str);

/*====================================================================*/
int main(int argc, char *argv[]){
	int success;
	int status = 1;

	// no extra arguments. Kindly tell user the correct arguments
	if(argc == 1){
		fprintf(stderr, 
		"Usage: ./indexer  [TARGET_DIRECTORY] [RESULTS FILENAME] \n"
		"For test run: ./indexer  [TARGET_DIRECTORY] [RESULTS FILENAME] [RESULTS FILENAME] [REWRITEN FILENAME]");
		return 0;
	}

	// Need correct amount of arguments. 
	if(argc != NORM_ARG_COUNT && argc != TEST_ARG_COUNT){
		fprintf(stderr, "You must input 3 arguments for the normal run, or 5 arguments for the test run.");
		return 0;
	}

	// need first argument to be a directory
	if(!IsDir(argv[1])){
                fprintf(stderr, "Given \"directory\" is not a directory.");
		return 0;
        }
	
	HashTable *invertedIndex;
	invertedIndex = calloc(1, sizeof(HashTable));
	
	if(!invertedIndex){ 
		status = 0;
		goto cleanup;
	}

	printf("Building the index...\n");
	fflush(stdout);

	// build index from the given directory
	success = buildIndexFromDirectory(argv[1], invertedIndex);
	if(!success){ 
		status = 0;
		goto cleanup;
	}

	// save the created index into the given file
	success = saveFile(argv[2], invertedIndex);
	if(!success){ 
		status = 0;
		goto cleanup;
	}
	
	cleanup:
		if(invertedIndex) DeleteHashTable(invertedIndex);
		if(status == 0){
			fprintf(stderr, "Failed index building or output processes.");
			return status;
		}
		
	if(TEST_ARG_COUNT == argc){ // this means testing mode.

		// create new index
		HashTable *testInvertedIndex;
        	testInvertedIndex = calloc(1, sizeof(HashTable));
        	if(!testInvertedIndex){
			status = 0;
			goto cleanup2;
		}

		printf("Testing index...\n");
		fflush(stdout);

		// rebuild and save the 
		success = readFile(argv[3], testInvertedIndex);
		if(!success){ 
			status = 0;
			goto cleanup2;
		}

		saveFile(argv[4], testInvertedIndex);
		if(!success){ 
			goto cleanup2;
			status = 0;
		}

		printf("Test complete!\n");
		fflush(stdout);

		// clean up
		cleanup2:
			if(testInvertedIndex){
				DeleteHashTable(testInvertedIndex);
			}
			if(status == 0){
				fprintf(stderr, "Failed index building or output processes while testing.");
                		return status;
			}
	}

	return 1;
}

/*
 * Given a directory, builds a hashtable out of the all of the words within 
 * all of the files in the directory.
 * @dirName: directory containing all of the files
 * @invInd: an empty HashTable pointer to build the hashtable into
 * @results: returns 1 if successful, 0 if not.
 */
int buildIndexFromDirectory(char *dirName, HashTable *invInd){
	char **filenames = NULL;	// array containing pointers of valid files
	int num_files = 0;		// number of valid files
	int i;
	int pos = 0;			// pos used for getting all valid words
        char *word;			// word we just got from the GetNextWord
	int curDocID;			// DocumentID of the file GetNextWord calls on

	// make an array of valid files and the number of those valid files
	num_files = GetFilenamesInDir(dirName, &filenames);
	if(num_files < 0) {
		// failed to get any filenames (various reasons)
		return 0;
	} 
	else{
		for(i = 0; i < num_files; i++){
			// convert filename into an int curDocID =
			curDocID = atoi(filenames[i]);

			char *fileWithPath = addPathToFile(dirName, filenames[i]);
			// process file into string char *doc =
			// Skip two lines in the beginning that is not html
			char *doc = fileToString(fileWithPath, LINES_TO_SKIP);

			// Get all the words within the HTML.
			while((pos = GetNextWord(doc, pos, &word)) > 0){
				NormalizeWord(word);
                 		// ignore any word that is not as big as 3 characters
                 		if(strlen(word) < MIN_WORD_LEN){
					free(word);
					continue;
				}
				// add the word to the hash table
				HashAdd(word, invInd, curDocID);
        		}
			// free everything we just allocated. We are done with them.
			pos = 0;
			free(fileWithPath);
			free(filenames[i]);
			free(doc);
		}
	// final clean up
	free(filenames);	
 	}
    return 1;
}

