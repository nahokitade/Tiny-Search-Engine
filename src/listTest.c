#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "common.h"

int main(){

List *newDLL = CreateDLL();

int emptySuccess;

emptySuccess = IsEmptyList(newDLL);

printf("If IsEmptyList method is successful, should print 1: %d\n", emptySuccess);

int removeFail = (!removeTop(newDLL))? 1 : 0;

printf("Remove should fail if empty, so should print 1: %d\n",  removeFail);

Webpage page = 
WebPage *pageAdd

int appendSuccess

return 1;
}




