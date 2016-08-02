/**
 * @fileName Dictionary.h.
 * @author komatsu
 * @version 0.0
 * @date 8/2/16.
 * @description
 */

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H


#include "Hash.h"

typedef struct {
    hash_template *next;
} dictionary;


hash_template *dictionary_set(hash *self, char *key, void *val);

hash_template *dictionary_get(hash *self, char *key);

void dictionary_remove(hash *self, char *key);

dictionary *dictionary_new(hash *dict);

hash_template *dictionary_next(dictionary *self);

void dictionary_destroy(dictionary *self);


#endif //DICTIONARY_DICTIONARY_H
