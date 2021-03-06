#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "hashtable.h"

int i;

int main(){

HashTable *newHash = CreateNewHashTab();

char *e1;
e1 = calloc(30, sizeof(char));
strcpy(e1, "Element 1");

printf("adding first element: %s\n", e1);

int success;
success = HashAdd(e1, newHash);

printf("should print 1 on add success: %d\n", success);

int containsSuccess;
containsSuccess = HashContains(e1, newHash);

printf("should print 1 on containment success: %d\n", containsSuccess);

char *notContainedStr;
notContainedStr = calloc(30, sizeof(char));
strcpy(notContainedStr, "Not Contained");

containsSuccess = HashContains(notContainedStr, newHash);

printf("should print 0 on containment failure: %d\n", containsSuccess);

printf("adding previous uncontained element: %s\n", notContainedStr);

success = HashAdd(notContainedStr, newHash);

printf("should print 1 on add success: %d\n", success);

containsSuccess = HashContains(notContainedStr, newHash);

printf("should print 1 on containment success now: %d\n", containsSuccess);

char *url;
url = calloc(30, sizeof(char));
strcpy(url, "www.dartmouth.edu");

HashAdd(url, newHash);

containsSuccess = HashContains(url, newHash);

printf("added url like string should print 1 on containment success: %d\n", containsSuccess);

printf("deleting hash table now...\n");

int deleteSuccess = DeleteHashTable(newHash);

printf("if delete is successful, should print 1: %d\n", deleteSuccess);


return 1;
}


