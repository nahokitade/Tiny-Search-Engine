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

/*create new DLL */
List *CreateDLL();

/*
 * add to linked list
 *
 */
int appendDLL(WebPage *webPage, List *linkedList);

/* remove from top of DLL
 */
WebPage *removeTop(List *linkedList);

/* checks if list is empty */
int IsEmptyList(List *linkedList);


#endif // LIST_H
