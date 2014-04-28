/* ========================================================================== */
/* File: common.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the common defines and data structures.
 *
 */
/* ========================================================================== */
#ifndef COMMON_H
#define COMMON_H

// ---------------- Prerequisites e.g., Requires "math.h"
//NEEDS stdlib.h

// ---------------- Constants
#define INTERVAL_PER_FETCH 0                // seconds between fetches

#define MAX_DEPTH 4                        // don't want to go too far do

// limit crawling to only this domain
#define URL_PREFIX "http://old-www.cs.dartmouth.edu/~cs50/tse"

// ---------------- Structures/Types

typedef struct WebPage {
    char *url;                               // url of the page
    char *html;                              // html code of the page
    size_t html_len;                         // length of html code
    int depth;                               // depth of crawl
} WebPage;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/* Deletes web page but keeps url intact for Hash table.
 * Returns 1 if delete is successful, 0 if not.
 */
int deleteWebPage(WebPage *toDeleteWeb);

#endif // COMMON_H
