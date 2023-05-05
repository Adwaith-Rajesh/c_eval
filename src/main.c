#include <stdio.h>

#include "linked_list.h"

int main() {
    printf("Hello, World\n");

    // some test code
    LinkedList *list = ll_init();
    ll_free(list);

    return 0;
}
