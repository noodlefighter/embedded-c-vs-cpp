/*
 * page.h
 *
 *  Created on: 2017-2-7
 *      Author: Ming180
 */



#ifndef PAGE_H_
#define PAGE_H_

#include <stdint.h>
#include <stdbool.h>

class Page {

};


struct PageConfig {
    const Page *init_page;
};


class PageManager
{
public:
    PageManager(PageConfig &cfg) {
        m_page_cfg = cfg;
    }

private:
    PageConfig m_page_cfg;
    const Page *curpage;
    bool page_need_update = false;
    uint8_t percentage = 10;

    // ~Page() { }
};



#define PAGE_HIDDEN  0x00
#define PAGE_ACTIVE  0x01
#define PAGE_SUSPEND 0x02
#define PAGE_EXIT    0x03

#define PAGE_KEY_MENU 3
#define PAGE_KEY_FUNC 4

struct page;

enum page_signal_num {
    PAGE_SIGNAL_NONE = 0,
    PAGE_SIGNAL_INPUT, // 输入事件
    PAGE_SIGNAL_PAINT_ALL, // 重绘全部
    PAGE_SIGNAL_PAINT_UPDATE, // 重绘更新部分
};

struct page_signal {
    enum page_signal_num sig_num; // 信号编号
    intptr_t             sig_val; // 信号数据
};

struct page_vtbl {
    void (*init)(const struct page *page);
    void (*fini)(const struct page *page);
    void (*signal)(const struct page *page, struct page_signal sig);
};

struct page {
    uint8_t          state;
    struct page_vtbl vtbl;
};


struct PageStack {
    uint8_t  top;
    uint8_t  depth;
    uint8_t  cellsize;
    uint8_t *buff;

    PageStack() {

    }
};



bool page_stack_push(struct page_stack *stack, void *obj);
bool page_stack_pop(struct page_stack *stack, void *obj);


int page_init(struct page_cfg *cfg);

void page_raise_signal(struct page_signal signal_num);
void page_schedule(void);

void page_emit_update_signal(void);
void page_update_hook(void);

bool page_back_to_last(void);
void page_back_to_top(void);

void page_switch_next(const struct page *page);
void page_switch_next_enforce(const struct page *page);

const struct page *get_current_page(void);

#endif // PAGE_H_
