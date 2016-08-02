/**
 * @description
 * @fileName main.c.
 * @author komatsu
 * @date 8/2/16.
 * @version 0.0
 */

#include <stdio.h>
#include "classes/core/PubSub/PubSub.h"


char *TOPIC_LAUNCH = "event_launch";


static void unsubscribe_callback(void *data) {
    puts((char *)data);
    pusub_unsubscribe(TOPIC_LAUNCH, unsubscribe_callback);
}

static void subscribe_topic() {
    pubsub_subscribe(TOPIC_LAUNCH, unsubscribe_callback);
}

static void publish_topic() {
    pubsub_publish(TOPIC_LAUNCH, "hello world");
}


int main(void) {
    pubsub_init();
    subscribe_topic();
    publish_topic();
    pubsub_destory();

    return 0;

}
