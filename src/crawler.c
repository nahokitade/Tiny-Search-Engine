/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author: Naho Kitade
 * Date: April 2014
 *
 * Input:
 *
 * Command line options:
 *
 * Output:
 *
 * Error Conditions:
 *
 * Special Considerations:
 *
 */
/* ========================================================================== */
// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>                           // printf

#include <curl/curl.h>                       // curl functionality

#include <sys/types.h>			     // for stat()
#include <sys/stat.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "web.h"                             // curl and html functionality
#include "list.h"                            // webpage list functionality
#include "hashtable.h"                       // hashtable functionality
#include "utils.h"                           // utility stuffs

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

/* ========================================================================== */

int main(int argc, char* argv[])
{
	int docID = 1;
	char *dirName;
	char *sourceURL;
	//int assertInt(const char* const str, long *val);
	int writePage(WebPage *pageToWrite, char *dirName, int *docIDAddr);
	int testDirSlash(const char *str);

	// check command line arguments
	if(argc != 4){ // need exactly 4 args
		fprintf(stderr, "Usage: ./crawler [seedURL] [webPageDirectory] [maxWebPageDepth]");
		return 0;
	}

	// need prefix of the url given to be the URL_PREFIX
	if(!(strncmp(argv[1], URL_PREFIX, strlen(URL_PREFIX))) == 0){
		fprintf(stderr, "The URL must have prefix: %s", URL_PREFIX);
                return 0;
        }

	if(!NormalizeURL(argv[1])){
		fprintf(stderr, "Was unable to normalize the seed URL given.");
                return 0;
	}

	sourceURL = argv[1];
	
	struct stat givDir;
	// checks if the given "directory" exisits at all
	if(stat(argv[2], &givDir) == -1){
		fprintf(stderr, "Directory cannot be found. The directory must exist and be already created.");
                return 0;
	} 

	// checks if the given "directory" is a directory.
	if(!(S_ISDIR(givDir.st_mode))){
		fprintf(stderr, "Given \"directory\" is not a directory.");
                return 0;
	}

	dirName = argv[2];
	
	//long *searchDepth = 0;
	// make sure that the third argument is an int.
	int searchDepth = atoi(argv[3]);
	/*if(!searchDepth){
		fprintf(stderr, "The search depth must be a integer value.");
                return 0;
	}*/

	// make sure that search depth is not greater than MAX_DEPTH
	// and larger than 0.
	if(searchDepth > MAX_DEPTH || searchDepth < 0){
		fprintf(stderr, "Search depth cannot exceed 4, and cannot be negative.");
                return 0;
	}

	
	// init curl
	curl_global_init(CURL_GLOBAL_ALL);

	// setup seed page
	WebPage* source; // make webpage for source
	source = calloc(1, sizeof(WebPage));
	if(!source) return 0;

	char *urlGiven; // allocate memory for the url to be stored in hash
	urlGiven  = calloc(strlen(sourceURL), sizeof(char));
	if(!urlGiven) return 0;
	strcpy(urlGiven, sourceURL);

	// Set the depth and url of the WebPage
	source->url = urlGiven;
	source->depth = 0;
	
	// get seed webpage
	if(GetWebPage(source)){ 
		// write seed file
		if(!(writePage(source, dirName, &docID))){
			fprintf(stderr, "No space to allocate filename.");
			return 0;
		}
	}
	else{
		fprintf(stderr, "The given URL is not valid.");
		return 0;
	}


	// add seed page to hashtable
	HashTable *hashTable;
	hashTable = CreateNewHashTab();
	if(!hashTable) return 0;
	HashAdd(source->url, hashTable);

	// extract urls from seed page
	int pos = 0;
 	char *result;
 	char *base_url = URL_PREFIX;
 	List *URLList = CreateDLL();
	int counter2 = 1;
	
 	while((pos = GetNextURL(source->html, pos, base_url, &result)) > 0) {
      		// DO SOMETHING WITH THE RESULT
		if(!(searchDepth >= 1)) continue;
		if(!NormalizeURL(result)) continue;
                if(!((strncmp(result, URL_PREFIX, strlen(URL_PREFIX))) == 0)) continue;
		if(HashContains(result, hashTable)) continue;
		char *resultSave;
		resultSave = calloc(strlen(result) + 1, sizeof(char));
		if(!resultSave) return 0;
		strcpy(resultSave, result);
		WebPage *pageAdd;
		pageAdd = calloc(1, sizeof(WebPage));
		if(!pageAdd) return 0;
		pageAdd->url = resultSave;
		pageAdd->depth = (source->depth + 1);
		printf("This is next url: %s\nNext depth:%d\n\n", pageAdd->url, pageAdd->depth);
		appendDLL(pageAdd, URLList);
		counter2++;
 	}
	pos = 0;
	deleteWebPage(source);

	int counter1 = 1;	

	while(!IsEmptyList(URLList)){
        	// get next url from list
		WebPage *nextURL = removeTop(URLList);
		printf("This is nextURL: %s\n Depth is: %d\n", nextURL->url, nextURL->depth);
		if(nextURL) printf("This should be a valid WebPage struct.\n\n");
        	// get webpage for url
		if(GetWebPage(nextURL)){
                	// write page file
                	if(!(writePage(nextURL, dirName, &docID))){
                        	fprintf(stderr, "No space to allocate filename.");
                        	return 0;
               	 	}
			counter1++;
        	}

        	// extract urls from webpage
		while((pos = GetNextURL(nextURL->html, pos, base_url, &result)) > 0) {
                	// DO SOMETHING WITH THE RESULT
			if(!(searchDepth >= nextURL->depth + 1)) continue;
        	        if(!NormalizeURL(result)) continue;
        	        if(!((strncmp(result, URL_PREFIX, strlen(URL_PREFIX))) == 0)) continue;
        	        if(HashContains(result, hashTable)) continue;
			char *resultSave;
                       	resultSave = calloc(strlen(result) + 1, sizeof(char));
                        if(!resultSave) return 0;

                        strcpy(resultSave, result);
                        WebPage *pageAdd;
                        pageAdd = calloc(1, sizeof(WebPage));
	
        	        if(!pageAdd) return 0;
                	pageAdd->url = resultSave;
                        pageAdd->depth = (nextURL->depth + 1);
                        printf("This is next url: %s\nNext depth:%d\n\n", pageAdd->url, pageAdd->depth);
                        appendDLL(pageAdd, URLList);
			counter2++;
        	}
		pos = 0;
		deleteWebPage(nextURL);
	}
    	// cleanup curl
    	// clean up hash table
    	curl_global_cleanup();
	DeleteHashTable(hashTable);
	free(URLList);

	printf("Number of files written = %d\n Number of URLs gotten = %d\n", counter1, counter2);

    	return 1;
}


/*int assertInt(const char* const str, long *val){
        char *point;
        *val = strtol(str, &point, 10);
        if(str != '\0' && point == '\0'){ // checking if conversion was successful
                return 1;
        }
        else return 0;
}*/


int testDirSlash(const char *str){
	if(!*str || !str) return 0;
	return (str[strlen(str) - 1] == '/') ? 1 : 0;
}

int writePage(WebPage *pageToWrite, char *dirName, int *docIDAddr){
	FILE *file;
        //CALLOC HERE
        char *fileName;
        fileName = calloc((strlen(dirName) + 9), sizeof(char));
        if(!fileName) return 0;

        if(testDirSlash(dirName)){
                sprintf(fileName, "%s%d", dirName, *docIDAddr);
        }
        else sprintf(fileName, "%s/%d", dirName, *docIDAddr);

        file = fopen(fileName, "a+");
        (*docIDAddr)++;
        fprintf(file,"%s\n%d\n%s", pageToWrite->url, pageToWrite->depth, pageToWrite->html);
        free(fileName);
        fclose(file);
	return 1;
}
