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

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "web.h"                             // curl and html functionality
#include "list.h"                            // webpage list functionality
#include "hashtable.h"                       // hashtable functionality
#include "utils.h"                           // utility stuffs

// ---------------- Constant definitions
#define MAX_DEPTH 4

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

/* ========================================================================== */

int main(int argc, char* argv[])
{
	long *searchDepth;
	CURL *curl;
	int docID = 1;
	int depth = 0;
	int assertInt(const char* const str, long *val);

	// check command line arguments
	if(argc != 3){
		fprintf(stderr, "USAGE err1.")
		return 0;
	}

	if((strncmp(argv[1], URL_PREFIX, strlen(URL_PREFIX))) == 0){
		fprintf(stderr, "USAGE err6.")
                return 0;
        }
	
	struct stat givDir;
	if(stat(argv[2], &givDir) == -1){
		fprintf(stderr, "USAGE err2.")
                return 0;
	} 

	if(!(S_ISDIR(givDir.st_mode))){
		fprintf(stderr, "USAGE err3.")
                return 0;
	}
	
	if(!(assertInt(argv[3], &searchDepth))){
		fprintf(stderr, "USAGE err4.")
                return 0;
	}

	if(*searchDepth > MAX_DEPTH || *searchDepth < 0){
		fprintf(stderr, "USAGE err5.")
                return 0;
	}

	
	// init curl
	curl_global_init(CURL_GLOBAL_ALL);

	// setup seed page
	if((WebPage* source = malloc(sizeof(WebPage))) == NULL) return 0;
	if((char *urlGiven = malloc(sizeof(argv[1]))) == NULL) return 0;
	source->url = urlGiven;
	source->depth = depth;
	depth++;
	
	// get seed webpage
	if(GetWebpage(page)){ //PROBLEM HERE!!!!!
		// write seed file
		FILE *file;
		file = fopen("%argv[1]/%docID", "a+");
		fprintf(file,"%s/n%d/n%s", page->url, page->depth, page->html);
		fclose(file);
	}
	else{
		fprintf(stderr, "USAGE err5.")
		return 0;
	}


	// add seed page to hashtable
	if((HashTable *hashTable = CreateNew()) = NULL) return 0;
	HashAdd(source.url, hashTable);

	// extract urls from seed page
	int pos = 0;
 	char *result;
 	char *base_url = URL_PREFIX;
 	List *URLList = CreateDLL();
	
 	while((pos = GetNextURL(source.url, pos, base_url, &result) > 0) {
      		// DO SOMETHING WITH THE RESULT
		if((MAXDEPTH >= (depth + 1)) && !(HashContains(result, hashTable))){
			if((char *resultSave = malloc(sizeof(result))) == NULL) return NULL;
			if((WebPage *pageAdd = malloc(sizeof(WebPage))) == NULL) return NULL;
			pageAdd->url = resultSave;
			pageAdd->depth = depth + 1;
			append(pageAdd, URLList);
		}
 	}
	depth++;

	// while there are urls to crawl
        	// get next url from list

        	// get webpage for url

        	// write page file

        	// extract urls from webpage

    	// cleanup curl
    	curl_global_cleanup();

    	return 1;
}


int assertInt(const char* const str, long *val){
        char *point;
        *val = strtol(str, &point, 10);
        if(str == point){ // checking if conversion was successful
                return 0;
        }
        else return 1;
}
