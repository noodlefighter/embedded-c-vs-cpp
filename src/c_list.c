#include "linux_list.h"
#include <stdio.h>

#define LIST_SIZE  50

struct item {
    struct list_head node;
    int a;
    int b;
    int c;
};

static struct item items[LIST_SIZE];
static LIST_HEAD(mylist);

void c_list(void)
{
    // init
    for (int i = 0; i < LIST_SIZE; i++) {
        items[i].a = items[i].b = items[i].c = i;
        list_add(&items[i].node, &mylist);
    }

    // foreach
    {
        struct item *pos;
        list_for_each_entry(pos, &mylist, node) {
            printf("a=%d,b=%d,c=%d\n", pos->a, pos->b, pos->c);
        }
    }

}
