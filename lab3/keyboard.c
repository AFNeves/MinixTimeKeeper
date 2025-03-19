#include "keyboard.h"

int hook_id = 1;
uint8_t scancode = 0;

int (keyboard_subscribe_int)(uint8_t *bit_no)
{
    if (bit_no == NULL) return 1;

    *bit_no = hook_id;

    return sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (keyboard_unsubscribe_int)()
{
    return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)()
{
    read_KBC_output();
}

int (read_KBC_output)()
{
    uint8_t status;
    uint8_t attempts = MAX_ATTEMPTS;

    while (attempts)
    {
        // Read KBC to see if there is data to read
        if (util_sys_inb(KBC_STATUS_REG, &status) != 0) return 1;

        // Check if there is data to read
        if ((status & FULL_OUT_BUF) != 0)
        {
            // Retrieve scancode from the output buffer
            if (util_sys_inb(KBC_OUT_BUF, &scancode) != 0) return 1;

            // Check if there was an error
            if ((status & (PARITY_ERROR | TIMEOUT_ERROR)) != 0) return 1;

            return 0;
        }

        // Wait for the KBC to be ready
        tickdelay(micros_to_ticks(KB_DELAY));
        attempts--;
    }

    return 1;
}
