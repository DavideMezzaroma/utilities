#include "./dynarr.h"
#include <stdlib.h>
#include <string.h>

DArray* da_create(size_t element_size){
	DArray* da_ptr;
	da_ptr = malloc(sizeof(DArray));
	if(da_ptr == NULL) return NULL;
	da_ptr->data = NULL;
	da_ptr->size = 0;
	da_ptr->capacity = 0;
	da_ptr->element_size = element_size;
	return da_ptr;
}

void da_destroy(DArray* dyn_array){
	if(dyn_array->data != NULL) free(dyn_array->data);

	free(dyn_array);
}

void da_clear(DArray* dyn_array){
	free(dyn_array->data);
	dyn_array->size = 0;
	dyn_array->capacity = 0;
}

size_t da_capacity(DArray* dyn_array){
	return dyn_array->capacity;
}

size_t da_size(DArray* dyn_array){
	return dyn_array->size;
}

void* da_get(DArray* dyn_array, size_t idx){
	if(dyn_array == NULL || idx >= dyn_array->size) return NULL;

	return (char *)dyn_array->data + idx * dyn_array->element_size;
}

void da_set(DArray* dyn_array, size_t idx, const void* new_element){
	if(dyn_array == NULL || idx >= dyn_array->size) return;

	void* old_element = da_get(dyn_array, idx);
	memcpy(old_element, new_element, dyn_array->element_size);
	return;
}

int da_add(DArray* dynarr, const void* new_element){
	if(dynarr->capacity <= dynarr->size){
		size_t new_capacity = dynarr->capacity == 0 ? 4 : dynarr->capacity * 2;
		void * new_data = realloc(dynarr->data, new_capacity * dynarr->element_size);
		if(new_data == NULL) return -1;
		dynarr->capacity = new_capacity;
		dynarr->data = new_data;
	}
	memcpy((char *)dynarr->data + dynarr->size * dynarr->element_size, new_element, dynarr->element_size);
	dynarr->size += 1;
	return 0;
}
