#ifndef __LIST_H__
#define __LIST_H__

#define bool int
#define true 1
#define false 0

#define START_HEAD 0
#define START_TAIL 1

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct listIter {
    listNode *next;
    int dir;
} listIter; 

typedef struct list {
    listNode *head;
    listNode *tail;
    void *(*dup)(void *value);
    void (*free)(void *value);
    int (*match)(void *value, void *key);
    unsigned long len;
} list;

list *listCreate(void);
void listRelease(list *list);
void listEmpty(list *list);
list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
list *listInsertNode(list *list, listNode *node, void *value, bool after);
void listDelNode(list *list, listNode *node);
listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);
void listReleaseIterator(listIter *iter);
list *listDup(list *orig);
listNode *listSearchKey(list *list, void *key);
listNode *listIndex(list *list, long index);
void listRewindHead(list *list, listIter *iter);
void listRewindTail(list *list, listIter *iter);
void listRotateTailToHead(list *list);
void listRotateHeadToTail(list *list);
void listJoin(list *l, list *o);
void listInitNode(listNode *node, void *value);
void listLinkNodeHead(list *list, listNode *node);
void listLinkNodeTail(list *list, listNode *node);
void listUnlinkNode(list *list, listNode *node);

#endif