/* ========================================================================== */
/* File: file.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * Author: Ira Ray Jenkins - jenkins@cs.dartmouth.edu
 * Date: Tue Apr 29, 2014
 *
 * These functions are provided for the students to simplify the manipulation
 * of files and directories.
 */
/* ========================================================================== */
#define _BSD_SOURCE                          // scandir,
                                             // students shouldn't take advantage
                                             // of the bsd extensions, but
                                             // it makes it easier to test file
                                             // types

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdlib.h>                          // free, calloc
#include <string.h>                          // strlen, strcpy
#include <dirent.h>                          // scandir, alphasort
#include <stdio.h>

#include <sys/stat.h>                        // stat functionality

// ---------------- Local includes  e.g., "file.h"
#include "file.h"                             // file/dir functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
static int SelectFile(const struct dirent *entry);

// ---------------- Public functions

int IsDir(const char *path)
{
    struct stat statbuf;                     // directory stat buffer

    // make sure we have a path
    if(!path) return 0;

    // if we can stat it, and it's a directory
    return (!stat(path, &statbuf) && S_ISDIR(statbuf.st_mode));
}

int GetFilenamesInDir(const char *dir, char ***filenames)
{
    struct dirent **namelist;                // list of dir entries from scandir
    int num_ents;                            // number of regular files found
    int status;                              // return status

    // make sure we have a directory path to work with
    if(!dir) { return -1; }

    // scan the directory for regular files
    status = num_ents = scandir(dir, &namelist, SelectFile, alphasort);
    if(num_ents < 0) {                       // something went wrong scanning
        return -1;
    }

    // allocate the filenames array
    *filenames = calloc(num_ents, sizeof(char*));
    if(!*filenames) {
        status = -1;
        goto cleanup;                        // sorry Dijkstra
    }

    // copy all the filenames and free the dirents
    for(int i = 0; i < num_ents; i++) {
        // allocate a filename large enough to contain the name
        (*filenames)[i] = calloc(strlen(namelist[i]->d_name) + 1, sizeof(char));
        if(!(*filenames)[i]) {
            status = -1;
            goto cleanup;                    // sorry Dijkstra
        }

        // copy the filename
        strcpy((*filenames)[i], namelist[i]->d_name);
    }

cleanup:
    if(namelist) {
        for(int i = 0; i < num_ents; i++) {
            if(namelist[i])
                free(namelist[i]);
        }
        free(namelist);
    }

    return status;
}

/*
 * SelectFile - test if a directory entry is a file
 * @entry: directory entry to test
 *
 * Returns non-zero if the directory entry is a regular file; otherwise, 0.
 *
 * This function uses the BSD dirent extensions, d_type and  DT_REG. Posix
 * doesn't promise that dirent will contain a type, but BSD does. Using this
 * avoids a separate call to stat.
 *
 * Should have no use outside of this file, thus declared static.
 */
static int SelectFile(const struct dirent *entry)
{
    return(entry->d_type == DT_REG);  // BSD ONLY
}

/*
 * Converts a file to a string after skipping the amount
 * of lines at the beginning of the file indicated by
 * startingLine
 * @startingLine: Which line of the file you want to
 * convert to a string.
 * @fileName: The name of the file to convert to a string
 * @result: returns the string converted version of the
 * file given. 
 */
char *fileToString(char* fileName, int startingLine){
        char *doc;		// file made into string
        long length;		// length of the file
	char tempc;		// temporary character to skip over first 2 lines
	int currentLine = 0;	// loop counter until startingLine
	int skipCount = 0;	// how many character we skipped

        FILE *file = fopen(fileName, "rb");
        if(!file) return NULL;

	// set pointer to end, get the length of the file,
	// set pointer back to start
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

	// skip until the specified startingLine position
	while(currentLine < startingLine){
		tempc = fgetc(file);
		if(tempc == '\n'){ // \n signifies new line
			currentLine++;
		}
		skipCount++;
	}

	// allocate sufficient memory and read the whole file
	// from after the skipped lines
        doc = calloc((length - skipCount) + 1, sizeof(char));
        if(!doc) return NULL;

        fread(doc, sizeof(char), length - skipCount, file);

        fclose(file);

        return doc;
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

