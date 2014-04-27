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
	HashTable *hashTable;
	int assertInt(const char* const str, long *val);
	int writePage(WebPage *pageToWrite, char *dirName, int *docIDAddr);
	int testDirSlash(const char *str);
	struct stat givDir;

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

	// checks if the seed URL can be normalized
	if(!NormalizeURL(argv[1])){
		fprintf(stderr, "Was unable to normalize the seed URL given.");
                return 0;
	}

	sourceURL = argv[1];
	
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
	
	long searchDepth;
	//make sure that the third argument is an int.
	if(!assertInt(argv[3], &searchDepth)){
		fprintf(stderr, "The search depth must be a integer value.");
                return 0;
	}

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
	urlGiven  = calloc(strlen(sourceURL) + 1, sizeof(char));
	if(!urlGiven) return 0;
	strcpy(urlGiven, sourceURL);

	// Set the depth and url of the WebPage
	source->url = urlGiven;
	source->depth = 0;
	
	// get seed webpage	
	int i;
	for(i = 0; i < MAX_TRY; i++){
		if(GetWebPage(source)){ 
			// write seed file
			if(!(writePage(source, dirName, &docID))){
				fprintf(stderr, "No space to allocate filename.");
				return 0;
			}
			break;
		}
		else{
			if(i >= MAX_TRY - 1){
				fprintf(stderr, "The given URL is not valid.");
				return 0;
			}
			sleep(INTERVAL_PER_FETCH);
		}
	}

#ifdef DEBUGGING
	FILE *webWritten;
	
        webWritten = fopen("crawlerPages.log", "a+");
#endif
		
	// create hashtable, and add seed page to hashtable.
	hashTable = CreateNewHashTab();
	if(!hashTable) return 0;
	HashAdd(source->url, hashTable);

	// create the URLList, and extract urls from seed page
	List *URLList = CreateDLL();
	int pos = 0;
 	char *result;
 	char *base_url = source->url;

	#ifdef DEBUGGING
	int counter2 = 1;
	#endif

	if((searchDepth >= 1)){

 		while((pos = GetNextURL(source->html, pos, base_url, &result)) > 0) {
			// NormalizeURL success
			// Restriction on URL's prefix to crawl
			// If the URL is already visited.
			if(!NormalizeURL(result)){
        	                free(result);
        	                continue;
        	        }
        	        if(!((strncmp(result, URL_PREFIX, strlen(URL_PREFIX))) == 0)){
        	                free(result);
        	                continue;
        	        }
			if(HashContains(result, hashTable)){
        	                free(result);
        	                continue;
        	        }
	
			// add that to a WebPage structure with the depth of the crawl
			WebPage *pageAdd;
			pageAdd = calloc(1, sizeof(WebPage));
			if(!pageAdd) return 0;
			pageAdd->url = result; 
			pageAdd->depth = (source->depth + 1);

			#ifdef DEBUGGING
				printf("This is next url: %s\nNext depth:%d\n\n", pageAdd->url, pageAdd->depth);
				counter2++;
			#endif

			// append the created WebPage to the URLList.
			HashAdd(result, hashTable);
			appendDLL(pageAdd, URLList);
	 	}
	}
	// return position to 0 and delete the already crawled WebPage.
	pos = 0;
	deleteWebPage(source);

	#ifdef DEBUGGING
		int counter1 = 1;	
	#endif

	while(!IsEmptyList(URLList)){
        	// get next url from list
		WebPage *nextURL = removeTop(URLList);

		#ifdef DEBUGGING
        	        printf("This is nextURL: %s\n Depth is: %d\n", nextURL->url, nextURL->depth);
        	        if(nextURL) printf("This should be a valid WebPage struct.\n\n");
		#endif

        	// get webpage for url
		if(GetWebPage(nextURL)){
                	// write page file
                	if(!(writePage(nextURL, dirName, &docID))){
                        	fprintf(stderr, "No space to allocate filename.");
                        	return 0;
               	 	}

			#ifdef DEBUGGING
				counter1++;
				fprintf(webWritten,"%d %s\n", nextURL->depth, nextURL->url);
			#endif

        	}
	
		if(searchDepth == nextURL->depth) continue;
		
		base_url = nextURL->url;
        	// extract urls from webpage
		while((pos = GetNextURL(nextURL->html, pos, base_url, &result)) > 0) {
                	// NormalizeURL success
               		// Restriction on URL's prefix to crawl
                	// If the URL is already visited.
        	        if(!NormalizeURL(result)){
				free(result);
				continue;
			}
        	        if(!((strncmp(result, URL_PREFIX, strlen(URL_PREFIX))) == 0)){
				free(result);
				continue;
			}
        	        if(HashContains(result, hashTable)){
				free(result);
				continue;
			}

			// add that to a WebPage structure with the depth of the crawl
                        WebPage *pageAdd;
                        pageAdd = calloc(1, sizeof(WebPage));
        	        if(!pageAdd) return 0;
			pageAdd->url = result;
                        pageAdd->depth = (nextURL->depth + 1);
                        
			#ifdef DEBUGGING
				printf("This is next url: %s\nNext depth:%d\n\n", pageAdd->url, pageAdd->depth);
				counter2++;
			#endif

			// append the created WebPage to the URLList.
			HashAdd(result, hashTable);
                        appendDLL(pageAdd, URLList);
        	}
		// return position to 0 and delete the already crawled WebPage.
		pos = 0;
		deleteWebPage(nextURL);
	}
    	// cleanup curl
    	// clean up hash table and URLList.
    	curl_global_cleanup();
	DeleteHashTable(hashTable);
	free(URLList);

	#ifdef DEBUGGING
		fclose(webWritten);
		printf("Number of files written = %d\n Number of URLs gotten = %d\n", counter1, counter2);
	#endif

    	return 1;
}


/* checks if the given string is some integer. 
 * Returns 1 if it is, and 0 if it is not. 
 */
int assertInt(const char* const str, long *val){
        char *end;
        *val = strtol(str, &end, 10);
        if(str == end){ // checking if conversion was successful
                return 0;
        }
        else return 1;
}

/* Sees if a given directory name has at the end of it's name.
 * returns 1 if it does, and 0 if it does not.
 */
int testDirSlash(const char *str){
	if(!*str || !str) return 0;
	return (str[strlen(str) - 1] == '/') ? 1 : 0;
}

/* Writes out the URL, depth, and html of a given webpage to a file in a 
 * given directory, using the document ID as the filename.
 * returns 1 on suucess and 0 on fail.
 */
int writePage(WebPage *pageToWrite, char *dirName, int *docIDAddr){
	FILE *file;
        char *fileName;
	// allocates enough space for the diretory name and document ID. 
        fileName = calloc((strlen(dirName) + 9), sizeof(char)); 
        if(!fileName) return 0;

	// creates a file name appriately depending on whether the given directory
	// name has a slash at the end. 
        if(testDirSlash(dirName)){
                sprintf(fileName, "%s%d", dirName, *docIDAddr);
        }
        else sprintf(fileName, "%s/%d", dirName, *docIDAddr);

        file = fopen(fileName, "a+");
        (*docIDAddr)++; // increment document ID for the next use.
        fprintf(file,"%s\n%d\n%s", pageToWrite->url, pageToWrite->depth, pageToWrite->html);
        free(fileName); // Dont forget to free the memory allocated for filename.
        fclose(file);
	return 1; 
}
