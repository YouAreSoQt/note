#include "list.h"
#include <stdio.h>

void listTest() {
    list *listOne;
    if ((listOne = listCreate()) == NULL) {
        printf("create list fail. \n");
        return;
    }

    listAddNodeTail(listOne, 1);
}

int main() {
    listTest();
    return 0;
}