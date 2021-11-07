#include "etl/list.h"
#include <stdio.h>

#define LIST_SIZE  25

#define CASE 0

struct item {
    int a;
    int b;
    int c;
};

typedef etl::list<item, LIST_SIZE> mylist1_t;

// 观察模板对代码尺寸的膨胀
#if(CASE == 0)
typedef item item2;
typedef etl::list<item2, LIST_SIZE> mylist2_t;
#elif(CASE == 1)
typedef item item2;
typedef etl::list<item2, LIST_SIZE+1> mylist2_t;
#elif(CASE == 2)
struct item2 {
    int a;
    int b;
    short int c;
};
typedef etl::list<item2, LIST_SIZE> mylist2_t; // case3
#endif

static mylist1_t mylist1;
static mylist2_t mylist2;

extern "C" {

void cpp_list(void)
{
    printf("---cpp_list---\n");

    // init
    for (int i = 0; i < LIST_SIZE; i++) {
        mylist1.push_front((item){.a = i, .b = i, .c = i});
        mylist2.push_front((item2){.a = i, .b = i, .c = i});
    }

    // foreach
    {
        mylist1_t::iterator iter;
        for (iter = mylist1.begin(); iter != mylist1.end(); iter++) {
            printf("a=%d,b=%d,c=%d\n", iter->a, iter->b, iter->c);
        }
    }
    {
        mylist2_t::iterator iter;
        for (iter = mylist2.begin(); iter != mylist2.end(); iter++) {
            printf("a=%d,b=%d,c=%d\n", iter->a, iter->b, iter->c);
        }
    }
}

}
