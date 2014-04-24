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

WebPage page;
WebPage *pageAdd = &page;

pageAdd->url = "www.dartmouth.edu";

int appendSuccess = appendDLL(pageAdd, newDLL);

printf("If appendDLL method is successful, should print 1: %d\n", appendSuccess);

emptySuccess = IsEmptyList(newDLL);

printf("If IsEmptyList method is successful, should print 0: %d\n", emptySuccess);

WebPage *retPage = removeTop(newDLL);

printf("Remove should be successful, and should print dartmouth url: %s\n", retPage->url);

emptySuccess = IsEmptyList(newDLL);

printf("If IsEmptyList method is successful, should print 1: %d\n", emptySuccess);

WebPage page2;
WebPage *pageAdd2 = &page2;

pageAdd2->url = "www.dartmouth.edu2";

WebPage page3;
WebPage *pageAdd3 = &page3;

pageAdd3->url = "www.dartmouth.edu3";

WebPage page4;
WebPage *pageAdd4 = &page4;

pageAdd4->url = "www.dartmouth.edu4";

appendSuccess = appendDLL(pageAdd2, newDLL);

printf("If appendDLL method is successful, should print 1: %d\n", appendSuccess);

appendSuccess = appendDLL(pageAdd3, newDLL);

printf("If appendDLL method is successful, should print 1: %d\n", appendSuccess);

appendSuccess = appendDLL(pageAdd4, newDLL);

printf("If appendDLL method is successful, should print 1: %d\n", appendSuccess);

retPage = removeTop(newDLL);

printf("Remove should be successful, and should print dartmouth url: %s\n", retPage->url);

retPage = removeTop(newDLL);

printf("Remove should be successful, and should print dartmouth url: %s\n", retPage->url);

retPage = removeTop(newDLL);

printf("Remove should be successful, and should print dartmouth url: %s\n", retPage->url);

removeFail = (!removeTop(newDLL))? 1 : 0;

printf("Remove should fail if empty, so should print 1: %d\n",  removeFail);

emptySuccess = IsEmptyList(newDLL);

printf("If IsEmptyList method is successful, should print 1: %d\n", emptySuccess);

}




