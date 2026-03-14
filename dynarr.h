#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <stddef.h>

//generic dyn_arr data structure
typedef struct{
	void* data;
	size_t size;
	size_t capacity;
	size_t element_size;
}DArray;

DArray* da_create(size_t element_size);

void da_destroy(DArray* dyn_array);
void da_clear(DArray* dyn_array);
size_t da_capacity(DArray* dyn_array);
size_t da_size(DArray* dyn_array);

void* da_get(DArray* dyn_array, size_t idx);
void da_set(DArray* dyn_array, size_t idx, const void* new_element);
int da_add(DArray* dyn_array, const void* new_element);
int da_shrink_to_fit(DArray* dyn_arr);
int da_reserve(DArray* dyn_arr, size_t num_elements);


#endif
