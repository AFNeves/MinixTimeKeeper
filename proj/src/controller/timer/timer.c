#include "timer.h"

int timer_hook_id = 0;
int timer_counter = 0;

int (timer_subscribe_int)()
{
    return sys_irqsetpolicy(TIMER_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int (timer_unsubscribe_int)()
{
    return sys_irqrmpolicy(&timer_hook_id);
}

void (timer_ih)()
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
