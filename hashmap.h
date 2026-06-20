#include <stdlib.h>
#include <stdbool.h>

#ifndef HASHMAP_H_
#define HASHMAP_H_

typedef struct HM_Element {
    void* key;
    void* value;
} HM_Element;

typedef struct HM_Hashmap {
    size_t size;
    size_t key_size;
    bool (*compare_keys)(const void* key1, const void* key2);
    HM_Element** buckets;
} HM_Hashmap;

extern HM_Element* const HM_DELETED;

/*
        hm_hash(key, key_size)
        hm_create(map, key_size, value_size)
        hm_put(map, key, value)
        hm_get(map, key)
        hm_remove(map, key)
    hm_contains_key(map, key)
    hm_contains_value(map, value)
    hm_size(map)
    hm_is_empty(map)
    hm_clear(map)
    hm_key_set(map)
    hm_values(map)
*/

size_t hm_hash(const void* key, size_t key_size);

HM_Hashmap* hm_create(size_t hm_size, size_t key_size, bool (*compare)(const void* key1, const void* key2));

void hm_put(HM_Hashmap* map, const void* key, const void* value);

void* hm_get(HM_Hashmap* map, const void* key);

void hm_remove(HM_Hashmap* map, const void* key);

#endif // HASHMAP_H_
