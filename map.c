#include "map.h"

/* djb2 hash method */
size_t hash(const char* str) {
    size_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + *str;
        str++;
    }
    return hash;
}

void map_node_new(map_node* self, const char* key, size_t hash, void* value) {
    *self = (map_node){
        .hash = hash,
        .key = key,
        .value = value,
        .next = nullptr};
}
void map_node_free(map_node* self) {
    if (self == nullptr) {
        return;
    }
    map_node_free(self->next);
    free(self);
}

void map_new(map* self) {
    *self = (map){
        .bucket_num = 16,
        .node_num = 0,
        .buckets = nullptr};
    self->buckets = malloc(sizeof(*(self->buckets)) * self->bucket_num);
    if (self->buckets == nullptr) {
        return;
    }
    memset(self->buckets, 0, sizeof(*(self->buckets)) * self->bucket_num);
}
void map_set(map* self, const char* key, void* value) {
    size_t raw_hash = hash(key);
    size_t idx_hash = raw_hash % self->bucket_num;

    /* Check if there already is data */
    if (self->buckets[idx_hash] != nullptr) {
        /* If the hashes are the same, the value needs to be replace */
        if (self->buckets[idx_hash]->hash == raw_hash) {
            self->buckets[idx_hash]->value = value;
        } else {
            /* Collision detected */
            map_node* current = self->buckets[idx_hash];
            while (current->next != nullptr) {
                current = current->next;
            }
            /* Just allocate a node */
            current->next = malloc(sizeof(map_node));
            if (current->next == nullptr) {
                return;
            }
            map_node_new(current->next, key, raw_hash, value);
        }
    } else {
        /* No collision detected, just allocate a node */
        map_node* new_node = malloc(sizeof(map_node));
        if (new_node == nullptr) {
            return;
        }
        map_node_new(new_node, key, raw_hash, value);
        /* Assign the newly allocated node */
        self->buckets[idx_hash] = new_node;
    }
    self->node_num++;
}
void* map_get(map* self, const char* key) {
    size_t raw_hash = hash(key);
    size_t idx_hash = raw_hash % self->bucket_num;

    /* Check if there already is data */
    if (self->buckets[idx_hash] != nullptr) {
        /* Check if the hash is the same */
        if (self->buckets[idx_hash]->hash == raw_hash) {
            /* Return the data */
            return self->buckets[idx_hash]->value;
        } else {
            /* Traverse through the linked list */
            map_node* current = self->buckets[idx_hash]->next;
            while (current != nullptr) {
                /* Check for the raw hash values */
                if (current->hash == raw_hash) {
                    return current->value;
                }
                current = current->next;
            }
            return nullptr;
        }
    } else {
        /* No data */
        return nullptr;
    }
}

void map_free(map* self) {
    for (size_t i = 0; i < self->bucket_num; i++) {
        map_node* c = self->buckets[i];
        /* If the bucket even exists */
        if (c != nullptr) {
            map_node_free(c);
        }
    }

    /* Final cleanup */
    free(self->buckets);
    self->bucket_num = 0;
    self->node_num = 0;
}
