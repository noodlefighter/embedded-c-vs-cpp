/*
 * page.c
 *
 *  Created on: 2017-2-7
 *      Author: Ming180
 * Description：UI管理模块
 */

#include "page.h"
#include "app_log.h"

#define PAGE_UNIT_LEN    sizeof(const struct page *)
#define PAGE_STACK_DEPTH 5

bool page_stack_push(struct page_stack *stack, void *obj);
bool page_stack_pop(struct page_stack *stack, void *obj);

static struct page_cfg    page_cfg;
static const struct page *curpage          = NULL;
static bool               page_need_update = false;
uint8_t                   percentage       = 10;

static uint8_t           page_stack_buff[PAGE_STACK_DEPTH * PAGE_UNIT_LEN];
static struct page_stack page_stack = {
    .top = 0, .depth = PAGE_STACK_DEPTH, .cellsize = PAGE_UNIT_LEN, .buff = page_stack_buff};

int page_init(struct page_cfg *cfg)
{
    page_cfg = *cfg;

    curpage = page_cfg.init_page;
    curpage->init(curpage);
}

void page_handler(uint16_t input)
{
    if (!curpage)
        return;

    if ((curpage->cb->state == PAGE_ACTIVE) && (curpage->process)) {
        curpage->process(curpage, input);
    }
}

void page_signal_handler(uint8_t signal_num)
{
    if (!curpage)
        return;

    if ((curpage->cb->state == PAGE_ACTIVE) && (curpage->signal)) {
        curpage->signal(curpage, signal_num);
    }
}

void page_emit_update_signal(void)
{
    page_need_update = true;
}

void page_update_hook(void)
{
    if (!curpage)
        return;

    if (curpage->cb->hook)
        curpage->cb->hook(curpage);

    if (!page_need_update)
        return;

    if (curpage->update) {
        page_need_update = false;
        if (curpage->cb->state == PAGE_ACTIVE)
            curpage->update(curpage);
    }
}

bool page_back_to_last(void)
{
    const struct page *page = NULL;
    bool               ret  = false;

    // 弹出之前页面
    ret = page_stack_pop(&page_stack, &page);

    if (ret) {
        curpage = page;
        curpage->init(curpage);
    }

    return ret;
}

void page_back_to_top(void)
{
    const struct page *page = page_cfg.init_page;

    if (curpage) {
        curpage->cb->state = PAGE_HIDDEN;
    }

    page->cb->state = PAGE_HIDDEN;
}

void page_switch_next(const struct page *page)
{
    if (!page)
        return;

    // 挂起当前显示页面
    if (curpage) {
        curpage->cb->state = PAGE_SUSPEND;

        // 压入当前页面
        page_stack_push(&page_stack, &curpage);
    }

    curpage = page;
    curpage->init(curpage);
}

void page_switch_next_enforce(const struct page *page)
{
    if (!page)
        return;

    curpage = page;
    curpage->init(curpage);
}

bool page_stack_push(struct page_stack *stack, void *obj)
{
    if (!stack || !stack->buff)
        return false;

    if (stack->top >= stack->depth)
        return false;

    memcpy(stack->buff + (stack->cellsize * stack->top), obj, stack->cellsize);
    stack->top++;

    return true;
}

bool page_stack_pop(struct page_stack *stack, void *obj)
{
    if (!stack || !stack->buff)
        return false;

    if (!stack->top)
        return false;

    stack->top--;
    memcpy(obj, stack->buff + (stack->cellsize * stack->top), stack->cellsize);

    return true;
}

const struct page *get_current_page(void)
{
    return curpage;
}
