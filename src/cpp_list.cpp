#include "etl/list.h"
#include <stdio.h>

#define LIST_SIZE  50

struct item {
    int a;
    int b;
    int c;
};

typedef etl::list<item, LIST_SIZE> mylist_t;

static mylist_t mylist;

extern "C" {

void cpp_list(void)
{
    // init
    for (int i = 0; i < LIST_SIZE; i++) {
        mylist.push_front((item){.a = i, .b = i, .c = i});
    }

    // foreach
    {
        mylist_t::iterator iter;
        for (iter = mylist.begin(); iter != mylist.end(); iter++) {
            printf("a=%d,b=%d,c=%d\n", iter->a, iter->b, iter->c);
        }
    }

}

}
