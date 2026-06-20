#include "./hashmap.h"
#include <string.h>

static HM_Element deleted_element;
HM_Element* const HM_DELETED = &deleted_element;

size_t hm_hash(const void* key, size_t key_size){
    const unsigned char* p = (const unsigned char*) key;
    unsigned int hash = 2166136261U;
    for(size_t i = 0; i < key_size; i++){
        hash ^= p[i];
        hash *= 16777619;
    }
    return hash;
}

HM_Hashmap* hm_create(size_t hm_size, size_t key_size, bool (*compare)(const void* key1, const void* key2)){
    HM_Hashmap* map = malloc(sizeof(HM_Hashmap));
    map->size = hm_size;
    map->key_size = key_size;
    map->compare_keys = compare;

    size_t map_bytes = hm_size * sizeof(HM_Element);
    map->buckets = malloc(map_bytes);
    if(map->buckets)
        memset(map->buckets, 0, map_bytes);

    return map;
}

void hm_put(HM_Hashmap* map, const void* key, const void* value){
    size_t h = hm_hash(key, map->key_size);
    size_t start_index = h % map->size;
    size_t index = start_index;
    long first_deleted_idx = -1;

    while(map->buckets[index] != NULL){

        // if we find a deleted place we save the index
        if(map->buckets[index] == HM_DELETED){
            if(first_deleted_idx == -1)
                first_deleted_idx = index;
        }

        // if key already exists we update the value
        else if(map->compare_keys(map->buckets[index], key)){
            map->buckets[index]->value = (void*)value;
            return;
        }

        index = (index + 1) % map->size;

        // full map (counting deleted)
        if(index == start_index) break;
    }

    size_t insert_idx = (first_deleted_idx == -1) ? index : (size_t) first_deleted_idx;

    // completely full map (should resize)
    if(map->buckets[insert_idx] != NULL && map->buckets[insert_idx] != HM_DELETED)
        return;

    // otherwise we need to add a new element to the map
    HM_Element* new_element = malloc(sizeof(HM_Element));
    new_element->key = (void*)key;
    new_element->value = (void*)value;

    map->buckets[insert_idx] = new_element;
}


void* hm_get(HM_Hashmap* map, const void* key){
    size_t h = hm_hash(key, map->key_size);
    size_t start_index = h % map->size;
    size_t index = start_index;

    while(map->buckets[index] != NULL){
        if(map->buckets[index] != HM_DELETED){
            if(map->compare_keys(map->buckets[index]->key, key)){
                return map->buckets[index]->value;
            }
        }
        index = (index + 1) % map->size;
        if(index == start_index) break;
    }
    return NULL;
}

void hm_remove(HM_Hashmap* map, const void* key){
    size_t h = hm_hash(key, map->key_size);
    size_t start_index = h % map->size;
    size_t index = start_index;

    while(map->buckets[index] != NULL){
        if(map->buckets[index] != HM_DELETED){
            if(map->compare_keys(map->buckets[index]->key, key))
                map->buckets[index] = HM_DELETED;
        }
        index = (index + 1) % map->size;
        if(index == start_index) break;
    }
}
