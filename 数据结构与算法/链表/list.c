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

list *listAddNodeHead(list *list, void *value) {
    listNode *newNode;

    if ((newNode = malloc(sizeof(*newNode))) == NULL)
        return NULL;
    
    newNode->value = value;
    listLinkNodeHead(list, newNode);

    return list;
}

void listLinkNodeTail(list *list, listNode *node) {
    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }

    list->len++;
}

list *listAddNodeTail(list *list, void *value) {
    listNode *newNode;

    if ((newNode = malloc(sizeof(*newNode))) == NULL)
        return NULL;
    
    newNode->value = value;
    listLinkNodeTail(list, newNode);

    return list;
}

list *listInsertNode(list *list, listNode *node, void *value, bool after) {
    listNode *newNode;

    if ((newNode = malloc(sizeof(*newNode))) == NULL)
        return NULL;
    
    newNode->value = value;

    if (after) {
        newNode->prev = node;
        newNode->next = node->next;
        node->next = newNode;
        if (list->tail == node) {
            list->tail = newNode;
        }
    } else {
        newNode->prev = node->prev;
        newNode->next = node;
        node->prev = newNode;
        if (list->head == node) {
            list->head = newNode;
        }
    }

    list->len++;
    return list;
}

void listUnlinkNode(list *list, listNode *node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->next;

    node->prev = node->next = NULL;

    list->len--;
}

void listDelNode(list *list, listNode *node) {
    listUnlinkNode(list, node);

    if (list->free)
        list->free(node->value);
    
    free(node);
}

listIter *listGetIterator(list *list, int direction) {
    listIter *iter;

    if ((iter = malloc(sizeof(*iter))) == NULL)
        return NULL;

    if (direction == START_HEAD)
        iter->next = list->head;
    else
        iter->next = list->tail;
    
    iter->dir = direction;

    return iter;
}

void listReleaseIterator(listIter *iter) {
    free(iter);
}

void listRewindHead(list *list, listIter *iter) {
    iter->dir = START_HEAD;
    iter->next = list->head;
}

void listRewindTail(list *list, listIter *iter) {
    iter->dir = START_TAIL;
    iter->next = list->tail;
}

listNode *listNext(listIter *iter) {
    listNode *cur = iter->next;

    if (cur != NULL) {
        if (iter->dir == START_HEAD)
            iter->next = cur->next;
        else
            iter->next = cur->prev;
    }

    return cur;
}

list *listDup(list *orig) {
    list *copy;
    listIter iter;
    listNode *cur;

    if ((copy = listCreate()) == NULL)
        return NULL;
    
    copy->dup = orig->dup;
    copy->free = orig->free;
    copy->match = orig->match;

    listRewindHead(orig, &iter);
    while ((cur = listNext(&iter)) != NULL) {
        void *value;

        if (copy->dup) {
            if ((value = copy->dup(cur->value)) == NULL) {
                listRelease(copy);
                return NULL;
            }
        } else {
            value = cur->value;
        }

        if (listAddNodeTail(copy, value) == NULL) {
            if (copy->free)
                copy->free(value);
            listRelease(copy);
            return NULL;
        }
    }

    return copy;
}

listNode *listSearchKey(list *list, void *key) {
    listIter iter;
    listNode *cur;

    listRewindHead(list, &iter);
    while ((cur = listNext(&iter)) != NULL) {
        if (list->match) {
            if (list->match(cur->value, key))
                return cur;
        } else {
            if (cur->value == key)
                return cur;
        }
    }

    return NULL;
}

listNode *listIndex(list *list, long index) {
    listNode *node;

    if (index < 0) {
        index = -index - 1;
        node = list->tail;
        while (node && index--) 
            node = node->prev;
    } else {
        node = list->head;
        while (node && index--)
            node = node->next;
    }

    return node;
}

void listRotateTailToHead(list *list) {
    if (list->len <= 1) 
        return;

    listNode *tail = list->tail;
    list->tail = tail->prev;
    list->tail->next = NULL;
    tail->prev = NULL;

    list->head->prev = tail;
    tail->next = list->head;
    list->head = tail;
}

void listRotateHeadToTail(list *list) {
    if (list->len <= 1)
        return;
    
    listNode *head = list->head;
    list->head = head->next;
    list->head->prev = NULL;
    head->next = NULL;

    list->tail->next = head;
    head->prev = list->tail;
    list->tail = head;
}

void listJoin(list *l, list *o) {
    if (o->len == 0)
        return;
    
    o->head->prev = l->tail;

    if (l->tail) 
        l->tail->next = o->head;
    else
        l->head = o->head;
    
    l->tail = o->tail;

    l->len += o->len;

    o->head = o->tail = NULL;
    o->len = 0;
}

void listInitNode(listNode *node, void *value) {
    node->prev = node->next = NULL;
    node->value = node->value;
}