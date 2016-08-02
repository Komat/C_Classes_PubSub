/**
 * @description
 * @fileName Item.c.
 * @author komatsu
 * @date 8/2/16.
 * @version 0.0
 */

#include "Item.h"

/**
 *
 * @param val
 * @return
 */
item *item_new(void *val) {
    item *self;
    if (!(self = malloc(sizeof(item))))
        return NULL;
    self->prev = NULL;
    self->next = NULL;
    self->val = val;
    return self;
}
