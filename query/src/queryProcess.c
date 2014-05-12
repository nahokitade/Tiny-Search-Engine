#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashtable.h"
#include "LLMergeSort.h"

//HAVE TO DUPLICATE THE DOCNODE

int compareIDs(DocNode *doc1, DocNode *doc2);
int compareOccurrences(DocNode *doc1, DocNode *doc2);
char *GetURL(char *fileName);
int testDirSlash(const char *str);
char *addPathToFile(char *path, char *fileName);



/*Function 1
Look for the word, Get its docNode, get its Docs, return the Docs. 
*/
DocNode *DocsFromWordNode(char *word, HashTable *hashTab){
	GenHashTableNode *wordHTN;
	WordNode *wordWN;	
	DocNode *toRetDoc;
	
	wordHTN = HashContains(word, hashTab);
	if(!wordHTN) return NULL;

	wordWN = ((WordNode *)wordHTN->hashKey);
	toRetDoc = wordWN->docs;
	return toRetDoc;
}

//COPYING FUNCTION ^ or separately
DocNode *CopyDocs(DocNode *docHead){
	DocNode *curDoc = docHead;
	DocNode *copyDocHead;
	DocNode *curCopyDoc;
	DocNode *newCopyDoc;
	
	if(!docHead) return NULL;

	newCopyDoc = calloc(1, sizeof(DocNode));
	if(!newCopyDoc) return NULL;

	newCopyDoc->documentID = curDoc->documentID;
	newCopyDoc->occurrences = curDoc->occurrences;

	copyDocHead = newCopyDoc;
	curCopyDoc = newCopyDoc; 
	curDoc = curDoc->nextDoc;	

	while(curDoc){
		newCopyDoc = calloc(1, sizeof(DocNode));
        	if(!newCopyDoc) return NULL;

		newCopyDoc->documentID = curDoc->documentID;
        	newCopyDoc->occurrences = curDoc->occurrences;

        	curCopyDoc->nextDoc = newCopyDoc;
        	curDoc = curDoc->nextDoc;
		curCopyDoc = curCopyDoc->nextDoc;
	}
	return copyDocHead;
}

/*
Function 2 for AND and OR 
Merge two doc nodes in sorted order. (doc IDs.)
merged list stored now at doc1. 
*/
int DocMergedID(DocNode **doc1, DocNode **doc2){
	DocNode *curDoc = *doc1;
	DocNode *doc2Ptr = *doc2;
	if(!curDoc) return 0;
	if(doc2Ptr){
		while(curDoc->nextDoc){
			curDoc = curDoc->nextDoc;
		}
		curDoc->nextDoc = doc2Ptr;
	}

	MergeSort(doc1, compareIDs);
	return 1;
}

int compareIDs(DocNode *doc1, DocNode *doc2){
	if(doc1->documentID > doc2->documentID) return 1;
	else if(doc1->documentID == doc2->documentID) return 0;
	else return -1;
}


/*
Function 3 for AND
Takes output from function 2 and get all the duplicates (according to the number of words)
make duplicates into one by adding the second occurrence to the first docnode occurrence.
Return only docNode chain with duplicated DocNode
*/
int ProcessAND(DocNode **doc1){
	if(!*doc1) return 0;
	
	DocNode *prevNode = NULL;
	DocNode *curNode = *doc1;
	DocNode *nextNode = curNode->nextDoc;
	DocNode *tempNode;
	int dupCount = 0;
	while(nextNode){
		if(curNode->documentID == nextNode->documentID){
			// HOPE THIS WORKS
			curNode->occurrences += nextNode->occurrences;
			curNode->nextDoc = nextNode->nextDoc;
			free(nextNode);
			dupCount++;
			nextNode = curNode->nextDoc;
		}		
		else{
			if(!dupCount){
				if(!prevNode){
					tempNode = curNode;
                                	curNode = curNode->nextDoc;
					*doc1 = curNode;
                                	free(tempNode);
				}

				else{
					tempNode = curNode;
					prevNode->nextDoc = curNode->nextDoc;
					curNode = prevNode->nextDoc;
					free(tempNode);	
				}
			}
			else{
				prevNode = curNode;
				curNode = curNode->nextDoc;
			}
			nextNode = nextNode->nextDoc;
			dupCount = 0;
		}
	}
	if(!dupCount){
                if(!prevNode){
                         tempNode = curNode;
                         curNode = curNode->nextDoc;
                         *doc1 = curNode;
                         free(tempNode);
                 }

                 else{
                         tempNode = curNode;
                         prevNode->nextDoc = curNode->nextDoc;
                         curNode = prevNode->nextDoc;
                         free(tempNode);
                 }
        }
	//*doc1 = *doc1->nextDoc;
	return 1;
}


/*
Function 4 for OR
Takes output from function 2 and make duplicates into one by adding the second occurrence to the first docnode occurrence. 
Return docNode chain with duplicated and non duplicated DocNode.
*/
int ProcessOR(DocNode **doc1){
        if(!*doc1) return 0;
        DocNode *prevNode = *doc1;
        DocNode *curNode = prevNode->nextDoc;
        while(curNode){
                if(prevNode->documentID == curNode->documentID){
                        // HOPE THIS WORKS
                        prevNode->occurrences += curNode->occurrences;
                        prevNode->nextDoc = curNode->nextDoc;
                        free(curNode);
                        curNode = prevNode->nextDoc;
                }
                else{
                        prevNode = prevNode->nextDoc;
                        curNode = curNode->nextDoc;
                }
        }
        return 1;
}


/*
Function 6 for AND and OR
Tree sort, merge sort, or something according to the occurrences of the word. 
return this sorted DocNode
*/
void SortByRank(DocNode **docToSort){
        MergeSort(docToSort, compareOccurrences);
}


int compareOccurrences(DocNode *doc1, DocNode *doc2){
        if(doc1->occurrences > doc2->occurrences) return 1;
        else if(doc1->occurrences == doc2->occurrences) return 0;
        else return -1;
}


/*
Function 8 for AND and OR
For all docID in docNode of docNode chains
go to crawler files, get the URL for that document
print documentID and URL \n
*/
void PrintQueryResult(DocNode *printHead, char *webPageDir){
	DocNode *tempDoc;
	int docID;
	char docIDChar[20];
	char *URL;
	char *fileName;
	int count = 0;
	while(printHead){
		tempDoc = printHead;
		docID = printHead->documentID;

		sprintf(docIDChar, "%d", docID);

		fileName = addPathToFile(webPageDir, docIDChar); //START HERE;

		URL = GetURL(fileName);
		
		printf("Document ID:%d URL:%s\n", docID, URL);

		printHead = printHead->nextDoc;
		free(tempDoc);		
		free(fileName);
		free(URL);
		count++;
	}
	printf("\nTotal Pages Found: %d\n", count);
}

/*
 * Combines the given path and a file name to make the file accessible
 * @path: path to the given filename's file
 * @fileName: fileName to add the path to
 * @results: returns the string that has the path and filename attached.
 */
char *addPathToFile(char *path, char *fileName){
        char *fileWithPath;
        if(testDirSlash(path)){
                fileWithPath = calloc(strlen(path) + strlen(fileName) + 1, sizeof(char));
                sprintf(fileWithPath, "%s%s", path, fileName);
        }
        else{
                fileWithPath = calloc(strlen(path) + strlen(fileName) + 2, sizeof(char));
                sprintf(fileWithPath, "%s/%s", path, fileName);
        }
        return fileWithPath;
}


/* Sees if a given directory name has a slash at the end of it's name.
 * returns 1 if it does, and 0 if it does not.
 */
int testDirSlash(const char *str){
	if(!*str || !str) return 0;
	return (str[strlen(str) - 1] == '/') ? 1 : 0;
}

char *GetURL(char *fileName){
	char tempc;
	int letCount = 0;
	char *URL;
	
	FILE *file = fopen(fileName, "rb");
	if(!file) return NULL;
	
	tempc = fgetc(file);
	while(tempc != '\n'){
                tempc = fgetc(file);
                // count the length of the word until space
                letCount++;
        }
        // rewind pointer, and save the URL into an allocated memory
        fseek(file, -(letCount + 1), SEEK_CUR);
        URL = calloc(letCount + 1, sizeof(char));
	if(!URL) return NULL;

        fread(URL, sizeof(char), letCount, file);

	fclose(file);
	return URL;
}


void PrintDocChain(DocNode *docNodeHead){
	DocNode *curDocNode = docNodeHead;
        // go through the whole chain of document nodes
        while(curDocNode){
                // write out the documentID and occurrences at
                // current line
                printf("DocumentID = %d \n", curDocNode->documentID);
                printf("Occurrences = %d \n\n ", curDocNode->occurrences);
                curDocNode = curDocNode->nextDoc;
        }
}









