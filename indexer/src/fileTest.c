#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
char *doc = fileToString("fileTest");


printf("the contents of fileTest are:\n %s", doc);

free(doc);

return 1;
}
