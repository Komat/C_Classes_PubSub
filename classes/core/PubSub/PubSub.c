/**
 * @description
 * @fileName PubSub.c.
 * @author komatsu
 * @date 8/2/16.
 * @version 0.0
 */

#include "PubSub.h"


static hash *s_callbacks;

static item_list *get_event_handler_list(char *event_name) {
    item_list *result;
    hash_template *pair = dictionary_get(s_callbacks, event_name);

    if (pair) {
        result = pair->val;
    } else {
        result = item_list_new();
        dictionary_set(s_callbacks, event_name, result);
    }
    return result;
}

static void foreach_event_callback(char *event_name, void (*processer)(item *, item_list *, void *), void *context) {
    item *node;
    item_list *callbacks = get_event_handler_list(event_name);
    list_iterator *it = item_list_iterator_new(callbacks, LIST_HEAD);
    while ((node = item_list_iterator_next(it))) {
        processer(node, callbacks, context);
    }
}

static void fire_handler(item *node, item_list *callbacks, void *context) {
    void *data = context;
    SubScriber fn = (SubScriber) node->val;
    fn(data);
}

static void remove_handler(item *node, item_list *callbacks, void *context) {
    SubScriber fn = (SubScriber) context;
    if (node->val == fn) {
        item_list_remove(callbacks, node);
    }
}

static void free_callbacks(char *key, void *list) {
    item_list_destroy((item_list *) list);
}

void pubsub_publish(char *event_name, void *data) {
    foreach_event_callback(event_name, fire_handler, data);
}

void pusub_unsubscribe(char *event_name, SubScriber fn) {
    foreach_event_callback(event_name, remove_handler, fn);
}

void pubsub_subscribe(char *event_name, SubScriber fn) {
    item_list *callbacks = get_event_handler_list(event_name);
    item *node = item_new(fn);
    item_list_rpush(callbacks, node);
}

hash *pubsub_init() {
    s_callbacks = hash_new();
    s_callbacks->free = free_callbacks;

    return s_callbacks;
}

void pubsub_destory() {
    hash_destroy(s_callbacks);
}
