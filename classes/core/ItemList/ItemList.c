/**
 * @description
 * @fileName List.c.
 * @author komatsu
 * @date 8/2/16.
 * @version 0.0
 */

#include "ItemList.h"

/**
 *
 * @return
 */
item_list *item_list_new() {
    item_list *self;
    if (!(self = malloc(sizeof(item_list))))
        return NULL;
    self->head = NULL;
    self->tail = NULL;
    self->free = NULL;
    self->match = NULL;
    self->len = 0;
    return self;
}

/**
 *
 * @param self
 */
void item_list_destroy(item_list *self) {
    unsigned int len = self->len;
    item *next;
    item *curr = self->head;

    while (len--) {
        next = curr->next;
        if (self->free) self->free(curr->val);
        free(curr);
        curr = next;
    }

    free(self);
}

/**
 *
 * @param self
 * @param node
 * @return
 */
item *item_list_rpush(item_list *self, item *node) {
    if (!node) return NULL;

    if (self->len) {
        node->prev = self->tail;
        node->next = NULL;
        self->tail->next = node;
        self->tail = node;
    } else {
        self->head = self->tail = node;
        node->prev = node->next = NULL;
    }

    ++self->len;
    return node;
}

/**
 *
 * @param self
 * @return
 */
item *item_list_rpop(item_list *self) {
    if (!self->len) return NULL;

    item *node = self->tail;

    if (--self->len) {
        (self->tail = node->prev)->next = NULL;
    } else {
        self->tail = self->head = NULL;
    }

    node->next = node->prev = NULL;
    return node;
}

/**
 *
 * @param self
 * @return
 */
item *item_list_lpop(item_list *self) {
    if (!self->len) return NULL;

    item *node = self->head;

    if (--self->len) {
        (self->head = node->next)->prev = NULL;
    } else {
        self->head = self->tail = NULL;
    }

    node->next = node->prev = NULL;
    return node;
}

/**
 *
 * @param self
 * @param node
 * @return
 */
item *item_list_lpush(item_list *self, item *node) {
    if (!node) return NULL;

    if (self->len) {
        node->next = self->head;
        node->prev = NULL;
        self->head->prev = node;
        self->head = node;
    } else {
        self->head = self->tail = node;
        node->prev = node->next = NULL;
    }

    ++self->len;
    return node;
}

/**
 *
 * @param self
 * @param val
 * @return
 */
item *item_list_find(item_list *self, void *val) {
    list_iterator *it = item_list_iterator_new(self, LIST_HEAD);
    item *node;

    while ((node = item_list_iterator_next(it))) {
        if (self->match) {
            if (self->match(val, node->val)) {
                item_list_iterator_destroy(it);
                return node;
            }
        } else {
            if (val == node->val) {
                item_list_iterator_destroy(it);
                return node;
            }
        }
    }

    item_list_iterator_destroy(it);
    return NULL;
}

/**
 *
 * @param self
 * @param index
 * @return
 */
item *item_list_at(item_list *self, int index) {
    list_direction direction = LIST_HEAD;

    if (index < 0) {
        direction = LIST_TAIL;
        index = ~index;
    }

    if ((unsigned) index < self->len) {
        list_iterator *it = item_list_iterator_new(self, direction);
        item *node = item_list_iterator_next(it);
        while (index--) node = item_list_iterator_next(it);
        item_list_iterator_destroy(it);
        return node;
    }

    return NULL;
}

/**
 *
 * @param self
 * @param node
 */
void item_list_remove(item_list *self, item *node) {
    node->prev
    ? (node->prev->next = node->next)
    : (self->head = node->next);

    node->next
    ? (node->next->prev = node->prev)
    : (self->tail = node->prev);

    if (self->free) self->free(node->val);

    free(node);
    --self->len;
}


// ---------------------------------------------------------------------------------------------------
// ITERATOR
// ---------------------------------------------------------------------------------------------------
/**
 *
 * @param list
 * @param direction
 * @return
 */
list_iterator *item_list_iterator_new(item_list *list, list_direction direction) {
    item *node = direction == LIST_HEAD
                        ? list->head
                        : list->tail;
    return item_list_iterator_new_from_node(node, direction);
}

/**
 *
 * @param node
 * @param direction
 * @return
 */
list_iterator *item_list_iterator_new_from_node(item *node, list_direction direction) {
    list_iterator *self;
    if (!(self = malloc(sizeof(list_iterator))))
        return NULL;
    self->next = node;
    self->direction = direction;
    return self;
}

/**
 *
 * @param self
 * @return
 */
item *item_list_iterator_next(list_iterator *self) {
    item *curr = self->next;
    if (curr) {
        self->next = self->direction == LIST_HEAD
                     ? curr->next
                     : curr->prev;
    }
    return curr;
}

/**
 *
 * @param self
 */
void item_list_iterator_destroy(list_iterator *self) {
    free(self);
    self = NULL;
}


