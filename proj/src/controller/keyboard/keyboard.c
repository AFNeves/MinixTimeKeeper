#include "keyboard.h"

int kb_hook_id = 1;
uint8_t scancode;
int (keyboard_subscribe_interrupts)()
{
    return sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kb_hook_id);
}

int (keyboard_unsubscribe_int)()
{
    return sys_irqrmpolicy(&kb_hook_id);
}

void (kbc_ih)()
{
    read_KBC_output(&scancode, 0);
}
