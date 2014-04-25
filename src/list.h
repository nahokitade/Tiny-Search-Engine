/* ========================================================================== */
/* File: list.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a doubly-linked list of WebPages.
 *
 */
/* ========================================================================== */
#ifndef LIST_H
#define LIST_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "common.h"                          // common functionality

// ---------------- Constants

// ---------------- Structures/Types

typedef struct ListNode {
    WebPage *page;                           // the data for a given page
    struct ListNode *prev;                   // pointer to previous node
    struct ListNode *next;                   // pointer to next node
} ListNode;

typedef struct List {
    ListNode *head;                          // "beginning" of the list
    ListNode *tail;                          // "end" of the list
} List;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/* creates new DLL 
 * Returns a pointer to a new List structure
 * Must free() the memory of the DLL after use
 */
List *CreateDLL();

/* append to a WebPage to the linked list
 * @webPage: WebPage to add to the linked list
 * @linkedList: linkedList to append the WebPage
 * Returns 1 on successful append, 0 if fail.
 */
int appendDLL(WebPage *webPage, List *linkedList);

/* remove from top of DLL
 * @linkedList: linkedList to remove from
 * Returns pointer of the WebPage that was removed, NULL if fail
 */
WebPage *removeTop(List *linkedList);

/* checks if list is empty 
 * @linkedList: linkedList to check if empty
 * Returns 1 if list is empty, 0 if not empty
 */
int IsEmptyList(List *linkedList);


#endif // LIST_H
