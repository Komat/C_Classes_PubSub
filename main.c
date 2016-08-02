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

char *TOPIC_RECEIVE = "topic_receive";

/**
 * 購読解除
 * @param data
 */
static void unsubscribe_callback(void *data) {
    puts((char *)data);
    pusub_unsubscribe(TOPIC_LAUNCH, unsubscribe_callback);
}

/**
 * 購読開始
 */
static void subscribe_topic() {
    pubsub_subscribe(TOPIC_LAUNCH, unsubscribe_callback);
}

/**
 * 発行
 */
static void publish_topic() {
    pubsub_publish(TOPIC_LAUNCH, "hello world");
}

/**
 * 購読解除
 * @param data
 */
static void unsubscribe_demo_callback(void *data) {
    puts((char *)data);
    pusub_unsubscribe(TOPIC_RECEIVE, unsubscribe_demo_callback);
}

/**
 * 購読開始
 */
static void subscribe_demo_topic() {
    pubsub_subscribe(TOPIC_RECEIVE, unsubscribe_demo_callback);
}

/**
 * 発行
 */
static void publish_demo_topic() {
    pubsub_publish(TOPIC_RECEIVE, "EVENT LAUNCH");
}


int main(void) {

    pubsub_new();
    subscribe_topic();
    publish_topic();

    subscribe_demo_topic();
    publish_demo_topic();

    pubsub_destory();

    return 0;

}
