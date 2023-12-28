#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct map_node map_node;
typedef struct map_node {
    size_t hash;
    const char* key;
    void* value;
    map_node* next;
} map_node;

typedef struct {
    map_node** buckets;
    size_t bucket_num;
    size_t node_num;
} map;

typedef struct {
    size_t bucket_idx;
    map_node* current;
} map_iter;

void map_new(map* self);
void map_set(map* self, const char* key, void* value);
void* map_get(map* self, const char* key);
void map_free(map* self);
