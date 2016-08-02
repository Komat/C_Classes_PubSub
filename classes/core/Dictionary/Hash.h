/**
 * @fileName Hash.h.
 * @author komatsu
 * @version 0.0
 * @date 8/2/16.
 * @description
 */

#ifndef DICTIONARY_HASH_H
#define DICTIONARY_HASH_H


#include <string.h>
#include <stdlib.h>

typedef struct hash_template_type {
    struct hash_template_type *prev;
    struct hash_template_type *next;
    char *key;
    void *val;
} hash_template;


typedef struct {
    hash_template *head;
    hash_template *tail;

    void (*free)(char *key, void *val);
} hash;


hash_template *dictionary_hash_new(char *key, void *val);

hash *hash_new();

void hash_destroy(hash *self);

#endif //DICTIONARY_HASH_H
