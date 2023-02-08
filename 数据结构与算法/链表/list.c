#include "list.h"
#include <stdlib.h>

list *listCreate(void) {
    struct list *list;

    if ((list = malloc(sizeof(*list))) == NULL)
        return NULL;
    
    list->head = list->tail = NULL;
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;
    list->len = 0;

    return list;
}

void listEmpty(list *list) {
    listNode *cur, *next;
    unsigned long len;

    cur = list->head;
    len = list->len;
    while (len--) {
        next = cur->next;
        if (list->free)
            list->free(cur->value);
        free(cur);
        cur = cur->next;
    }

    list->head = list->tail = NULL;
    list->len = 0;
}

void listRelease(list *list) {
    listEmpty(list);
    free(list);
}

void listLinkNodeHead(list *list, listNode *node) {
    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

    list->len++;
}

list *listAddNodeHead(list *list, void *value)
{
    listNode *newNode;

    if ((newNode = malloc(sizeof(*newNode))) == NULL)
        return NULL;
    
    newNode->value = value;
    listLinkNodeHead(list, newNode);

    return list;
}