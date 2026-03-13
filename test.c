#include "./dynarr.c"
#include "dynarr.h"
#include <stdio.h>

int main(){

	DArray* array = da_create(sizeof(int));

	for(int i = 0; i < 5; i++){
		da_add(array, &i);
	}

	for(int i = 0; i < 5; i++){
		if(array != NULL && da_get(array, i) != NULL) printf("%d\n", *(int *)da_get(array, i));
	}




	return 0;
}
