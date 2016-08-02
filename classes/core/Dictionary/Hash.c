/**
 * @fileName Hash.c.
 * @author komatsu
 * @version 0.0
 * @date 8/2/16.
 * @description
 */

#include "Hash.h"

/**
 *
 * @return
 */
hash *hash_new() {
    hash *self;
    if (!(self = malloc(sizeof(hash)))) {
        return NULL;
    }
    self->head = NULL;
    self->tail = NULL;
    self->free = NULL;
    return self;
}

/**
 *
 * @param self
 */
void hash_destroy(hash *self) {
    hash_template *next;
    hash_template *curr = self->head;

    while (curr) {
        next = curr->next;
        if (self->free) self->free(curr->key, curr->val);
        free(curr);
        curr = next;
    }

    free(self);
}


/**
 *
 * @param key
 * @param val
 * @return
 */
hash_template *dictionary_hash_new(char *key, void *val) {
    hash_template *self;
    if (!(self = malloc(sizeof(hash_template)))) {
        return NULL;
    }
    self->prev = NULL;
    self->next = NULL;
    self->key = key;
    self->val = val;
    return self;
}
