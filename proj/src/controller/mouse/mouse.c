#include "mouse.h"

int mouse_hook_id = 2;
uint8_t byte_index = 0;
uint8_t mouse_byte;
uint8_t mouse_data[3];
struct packet mouse_packet;
MouseInfo mouse_info;

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

void (mouse_make_packet)()
{
    // Mouse Packet Bytes
    mouse_packet.bytes[0] = mouse_data[0];
    mouse_packet.bytes[1] = mouse_data[1];
    mouse_packet.bytes[2] = mouse_data[2];
    // Mouse Buttons
    mouse_packet.lb = mouse_data[0] & MOUSE_LB;
    mouse_packet.mb = mouse_data[0] & MOUSE_MB;
	mouse_packet.rb = mouse_data[0] & MOUSE_RB;
    // Mouse Overflow
    mouse_packet.x_ov = mouse_data[0] & MOUSE_OVERFLOW_X;
    mouse_packet.y_ov = mouse_data[0] & MOUSE_OVERFLOW_Y;
	// Mouse Position Delta
    mouse_packet.delta_x = (mouse_data[0] & MOUSE_SIGNAL_X) ?
												 (mouse_data[1] | 0xFF00) : mouse_data[1];
	mouse_packet.delta_y = (mouse_data[0] & MOUSE_SIGNAL_Y) ?
												 (mouse_data[2] | 0xFF00) : mouse_data[2];
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
