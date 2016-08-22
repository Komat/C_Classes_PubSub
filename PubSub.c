/**
 * @description
 * @fileName PubSub.c.
 * @author komat
 * @date 8/2/16.
 * @version 0.0
 */

#include "PubSub.h"


static hash *s_callbacks;

/**
 *
 * @param event_name
 * @return
 */
static item_list *get_event_handler_list(char *event_name) {
    item_list *result;
    hash_item *pair = dictionary_get(s_callbacks, event_name);

    if (pair) {
        result = pair->val;
    } else {
        result = item_list_new();
        dictionary_set(s_callbacks, event_name, result);
    }
    return result;
}

/**
 *
 * @param event_name
 * @param processer
 * @param context
 */
static void foreach_event_callback(char *event_name, void (*processer)(item *, item_list *, void *), void *context) {
    item *node;
    item_list *callbacks = get_event_handler_list(event_name);
    list_iterator *it = item_list_iterator_new(callbacks, LIST_HEAD);
    while ((node = item_list_iterator_next(it))) {
        processer(node, callbacks, context);
    }
}

/**
 *
 * @param node
 * @param callbacks
 * @param context
 */
static void fire_handler(item *node, item_list *callbacks, void *context) {
    void *data = context;
    Subscriber fn = (Subscriber) node->val;
    fn(data);
}

/**
 *
 * @param node
 * @param callbacks
 * @param context
 */
static void remove_handler(item *node, item_list *callbacks, void *context) {
    Subscriber fn = (Subscriber) context;
    if (node->val == fn) {
        item_list_remove(callbacks, node);
    }
}

/**
 *
 * クリア
 *
 * @param key
 * @param list
 */
static void free_callbacks(char *key, void *list) {
    item_list_destroy((item_list *) list);
}

/**
 *
 * チャンネルを発行
 *
 * @param event_name
 * @param data
 */
void pubsub_publish(char *event_name, void *data) {
    foreach_event_callback(event_name, fire_handler, data);
}

/**
 *
 * 購読解除
 *
 * @param event_name
 * @param fn
 */
void pubsub_unsubscribe(char *event_name, Subscriber fn) {
    foreach_event_callback(event_name, remove_handler, fn);
}

/**
 *
 *
 *
 * @param event_name
 * @param fn
 */
void pubsub_subscribe(char *event_name, Subscriber fn) {
    item_list *callbacks = get_event_handler_list(event_name);
    item *node = item_new(fn);
    item_list_rpush(callbacks, node);
}

/**
 *
 * PubSub Initialize
 *
 * @return
 */
hash *pubsub_new() {

    s_callbacks = hash_new();
    s_callbacks->free = free_callbacks;

    return s_callbacks;
}

/**
 *
 */
void pubsub_destory() {
    hash_destroy(s_callbacks);
}
