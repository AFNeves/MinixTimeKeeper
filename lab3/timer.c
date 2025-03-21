#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_hook_id = 0;
int timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq)
{
    if (freq > TIMER_FREQ) return 1;

    uint8_t controlWord;
    if (timer_get_conf(timer, &controlWord) != 0) return 1;
    controlWord = (controlWord & 0xCF) | TIMER_LSB_MSB;

    uint16_t val = TIMER_FREQ / freq;
    uint8_t LSB, MSB;
    util_get_LSB(val, &LSB);
    util_get_MSB(val, &MSB);

    if (sys_outb(TIMER_CTRL, controlWord) != 0) return 1;
    if (sys_outb(TIMER_0 + timer, LSB) != 0) return 1;
    if (sys_outb(TIMER_0 + timer, MSB) != 0) return 1;

    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no)
{
    if (bit_no == NULL) return 1;

    *bit_no = timer_hook_id;

    return sys_irqsetpolicy(TIMER_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int (timer_unsubscribe_int)()
{
    return sys_irqrmpolicy(&timer_hook_id);
}

void (timer_int_handler)()
{
    timer_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st)
{
    if (st == NULL || timer > 2) return 1;

    uint8_t readBack = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

    if (sys_outb(TIMER_CTRL, readBack) != 0) return 1;

    if (util_sys_inb(TIMER_0 + timer, st) != 0) return 1;

    return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field)
{
    union timer_status_field_val data;
    switch (field)
    {
        case tsf_all:
            data.byte = st;
            break;
        
        case tsf_initial:
            st = (st >> 4) & 0x03; // Get bit 5 and 4

            if (st == 1) data.in_mode = LSB_only;
            else if (st == 2) data.in_mode = MSB_only;
            else if (st == 3) data.in_mode = MSB_after_LSB;
            else data.in_mode = INVAL_val;

            break;
        
        case tsf_mode:
            st = (st >> 1) & 0x07; // Get bit 3, 2 and 1

            if (st == 6) data.count_mode = 2;
            else if (st == 7) data.count_mode = 3;
            else data.count_mode = st;

            break;

        case tsf_base:
            data.bcd = st & TIMER_BCD;
            break;
        
        default:
            return 1;
    }

    if (timer_print_config(timer, field, data) != 0) return 1;

    return 0;
}
