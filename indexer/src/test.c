#include <stdio.h>

int main() {
	int i = 10;
	int *i_ptr = &i;
	int *i_ptr_2 = i_ptr;
	
	printf("i: %d\n", i);
	
	printf("i_ptr: %p\n", (void *)i_ptr);
	printf("*i_ptr: %d\n", *i_ptr);
	//printf("&i_ptr: %p\n", &i_ptr);
	
	printf("i_ptr_2: %p\n", (void *)i_ptr_2);
	printf("*i_ptr_2: %d\n", *i_ptr_2);
	//printf("&i_ptr_2: %p\n", &i_ptr_2);

	// what happens if you change i_ptr_2 ? What about *i_ptr_2?	

	(*i_ptr_2)++;

	printf("i_ptr: %p\n", (void *)i_ptr);
        printf("*i_ptr: %d\n", *i_ptr);
        //printf("&i_ptr: %p\n", &i_ptr);

        printf("i_ptr_2: %p\n", (void *)i_ptr_2);
        printf("*i_ptr_2: %d\n", *i_ptr_2);
        //printf("&i_ptr_2: %p\n", &i_ptr_2);
}
