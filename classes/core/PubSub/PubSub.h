/**
 * @description
 * @fileName PubSub.h.
 * @author komatsu
 * @date 8/2/16.
 * @version 0.0
 */

#ifndef PUBSUB_PUBSUB_H
#define PUBSUB_PUBSUB_H

#include <stdio.h>

#include "../ItemList/classes/core/ItemList/ItemList.h"
#include "../Dictionary/classes/core/Dictionary/Dictionary.h"


typedef void (*Subscriber)(void *context);

void pubsub_publish(char *event_name, void *data);

void pubsub_subscribe(char *event_name, Subscriber fn);

void pusub_unsubscribe(char *event_name, Subscriber fn);

hash* pubsub_new();

void pubsub_destory();


#endif //PUBSUB_PUBSUB_H
