#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void *createInt(int n) {
    int *p = malloc(sizeof(int));
    if (p != NULL) *p = n;
    return p;
}

void freeInt(void *n) {
    if (n != NULL) free(n);
}

void listTest() {
    list *listOne = listCreate();
    listOne->free = &freeInt;

    for (int i = 0; i < 10; i++)
        listAddNodeTail(listOne, createInt(i));
    
    for (int i = 100; i < 110; i++)
        listAddNodeHead(listOne, createInt(i));

    listIter iter;
    listRewindHead(listOne, &iter);
    listNode *cur;
    while ((cur = listNext(&iter)) != NULL) {
        printf("%d ", *((int *)cur->value));
    }
}

int main() {
    listTest();
    return 0;
}