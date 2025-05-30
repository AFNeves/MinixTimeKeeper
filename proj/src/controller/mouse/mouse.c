#include "mouse.h"

int mouse_hook_id = 2;
uint8_t byte_index = 0;
uint8_t mouse_byte;
uint8_t mouse_data[3];
MouseInfo mouse_info;
extern vbe_mode_info_t vbe_info;

int (mouse_subscribe_int)()
{
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)()
{
    return sys_irqrmpolicy(&mouse_hook_id);
}

void (mouse_ih)()
{
    read_KBC_output(&mouse_byte, 1);
}

void (mouse_sync)()
{
    if ((byte_index == 0 && (mouse_byte & FIRST_BYTE)) ||
        byte_index > 0)
    {
        mouse_data[byte_index] = mouse_byte;
        byte_index++;
    }
}

void (update_mouse_info)()
{
    // Mouse Buttons
    mouse_info.lb = mouse_data[0] & MOUSE_LB;
    mouse_info.rb = mouse_data[0] & MOUSE_RB;

    // Mouse Position
    mouse_info.x += (mouse_data[0] & MOUSE_SIGNAL_X) ? (mouse_data[1] | 0xFF00) : mouse_data[1];
    mouse_info.y -= (mouse_data[0] & MOUSE_SIGNAL_Y) ? (mouse_data[2] | 0xFF00) : mouse_data[2];

    // Normalize Mouse Position
    if (mouse_info.x < 0) mouse_info.x = 0;
    if (mouse_info.y < 0) mouse_info.y = 0;
    if (mouse_info.x > vbe_info.XResolution - 1) mouse_info.x = vbe_info.XResolution - 1;
    if (mouse_info.y > vbe_info.YResolution - 1) mouse_info.y = vbe_info.YResolution - 1;
}

int (mouse_write_command)(uint8_t command)
{
    uint8_t status;
    uint8_t response;
    uint8_t attempts = MAX_ATTEMPTS;

    while (attempts)
    {
        // Request forwarding to the mouse
        if (write_to_KBC(KBC_IN_BUF, KBC_WRITE_MOUSE) != 0) return 1;

        // Write the Mouse Command to port 0x60
        if (write_to_KBC(KBC_IN_BUF_ARG, command) != 0) return 1;

        // Delay to allow the mouse to process the command
        tickdelay(micros_to_ticks(KB_DELAY));

        // Read the status register to check for errors
        if (util_sys_inb(KBC_STATUS_REG, &status) != 0) return 1;

        // Check if the output buffer is full
        if ((status & FULL_OUT_BUF) != 0)
        {
            // Read the ACK byte from the mouse
            if (util_sys_inb(KBC_OUT_BUF, &response) != 0) return 1;

            // If mouse acknowledges the command, return 0
            if (response == MOUSE_ACK) return 0;
        }

		attempts--;
    }

    return 1;
}
