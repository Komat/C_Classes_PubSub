/**
 * @description
 * @fileName List.h.
 * @author komatsu
 * @date 8/2/16.
 * @version 0.0
 */

#ifndef ITEMLIST_ITEMLIST_H
#define ITEMLIST_ITEMLIST_H

#include <stdlib.h>
#include "Item.h"

typedef enum {
    LIST_HEAD,
    LIST_TAIL
} list_direction;


typedef struct {
    item *head;
    item *tail;
    unsigned int len;

    void (*free)(void *val);

    int (*match)(void *a, void *b);
} item_list;


typedef struct {
    item *next;
    list_direction direction;
} list_iterator;


item_list *item_list_new();

item *item_list_rpush(item_list *self, item *node);

item *item_list_lpush(item_list *self, item *node);

item *item_list_find(item_list *self, void *val);

item *item_list_at(item_list *self, int index);

item *item_list_rpop(item_list *self);

item *item_list_lpop(item_list *self);


void item_list_remove(item_list *self, item *node);

void item_list_destroy(item_list *self);

list_iterator *item_list_iterator_new(item_list *list, list_direction direction);

list_iterator *item_list_iterator_new_from_node(item *node, list_direction direction);

item *item_list_iterator_next(list_iterator *self);

void item_list_iterator_destroy(list_iterator *self);


#endif //ITEMLIST_ITEMLIST_H
