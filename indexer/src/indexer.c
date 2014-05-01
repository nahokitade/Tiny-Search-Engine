/*	file.c	one-line description

	Copyright 2013 (if any)

	License (if any)

	Project name:
	Component name:

	This file contains ...
	
	Primary Author:	
	Date Created:	

	Special considerations:  
		(e.g., special compilation options, platform limitations, etc.) 
	
======================================================================*/
// do not remove any of these sections, even if they are empty
//
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

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 
int buildIndexFromDirectory(char *dirName, HashTable *invInd);
char *addPathToFile(char *path, char *fileName);

/*====================================================================*/
int main(int argc, char *argv[]){
	if(!IsDir(argv[1])){
		fprintf(stderr, "Given \"directory\" is not a directory.");
	}

	HashTable *invertedIndex;
	invertedIndex = calloc(1, sizeof(HashTable));
	if(!invertedIndex) return 0;

	printf("Building the index...\n");
	
	buildIndexFromDirectory(argv[1], invertedIndex);

	saveFile(argv[2], invertedIndex);

	DeleteHashTable(invertedIndex);

	/*HashTable *testInvertedIndex;
        testInvertedIndex = calloc(1, sizeof(HashTable));
        if(!testInvertedIndex) return 0;
	
	if(5 == argc){
		printf("Testing index...\n");
		//readFile(argv[3], testInvertedIndex);
		saveFile(argv[4], testInvertedIndex);
		printf("Test complete!");
		DeleteHashTable(testInvertedIndex);
	}*/

	return 1;
}

int buildIndexFromDirectory(char *dirName, HashTable *invInd){

	char **filenames = NULL;
	int num_files = 0;
	int i;
	int pos = 0;
        char *word;
	int curDocID;

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
			char *doc = fileToString(fileWithPath);

			while((pos = GetNextWord(doc, pos, &word)) > 0){
				NormalizeWord(word);
                 		// do something with word
				HashAdd(word, invInd, curDocID);
        		}

			pos = 0;
			free(fileWithPath);
			free(filenames[i]);
			free(doc);
		}
	free(filenames);	
 	}
    return 1;
}

char *addPathToFile(char *path, char *fileName){
	char *fileWithPath;
	fileWithPath = calloc(strlen(path) + strlen(fileName) + 1, sizeof(char));
	
	sprintf(fileWithPath, "%s%s", path, fileName);

	return fileWithPath;
}
