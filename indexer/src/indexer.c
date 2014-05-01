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

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"

// ---------------- Constant definitions 

// ---------------- Macro definitions

// ---------------- Structures/Types 

// ---------------- Private variables 

// ---------------- Private prototypes 

/*====================================================================*/
int main(int argc, char *argv[]){

	HashTable *invertedIndex;
	invertedIndex = calloc(1, sizeof(HashTable));
	if(!invertedIndex) return 0;

	printf("Building the index...\n");
	
	buildIndexFromDirectory(argv[1], invertedIndex);

	saveFile(argv[2], invertedIndex);

	DeleteHashTable(invertedIndex);

	HashTable *testInvertedIndex;
        testInvertedIndex = calloc(1, sizeof(HashTable));
        if(!testInvertedIndex) return 0;
	
	if(5 == argc){
		printf("Testing index...\n");
		readFile(argv[3], testInvertedIndex);
		saveFile(argv[4], testInvertedIndex);
		printf("Test complete!");
		DeleteHashTable(testInvertedIndex);
	}

	return 1;
}

int buildIndexFromDirectory(HashTable invInd, char *dirName){
	struct dirent **existingFiles;
	int i, numOfFiles;
	numOfFiles = scandir(".", &existingFiles, 0, alphasort);
	if (numOfFiles < 0) return 0;
    	else {
        	for (i = 0; i < numOfFiles; i++) {
			printf("%s\n", existingFiles[i]->d_name);

	




           		free(existingFiles[i]);
            	}
        }
    	free(existingFiles);
    return 1;

}

int buildIndexPerFile(HashTable invInd, char *fileName){




}













