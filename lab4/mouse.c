#include "mouse.h"

int mouse_hook_id = 2;

int (mouse_subscribe_int)(uint8_t *bit_no)
{
    if (bit_no == NULL) return 1;

    *bit_no = mouse_hook_id;

    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)()
{
    return sys_irqrmpolicy(&mouse_hook_id);
}

void (mouse_ih)()
{

}
