#include "KBC.h"

int (read_KBC_output)(uint8_t *byte, uint8_t mouse)
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
            if (util_sys_inb(KBC_OUT_BUF, byte) != 0) return 1;

            // Check if there was an error
            if ((status & (PARITY_ERROR | TIMEOUT_ERROR)) != 0) return 1;

            // Check if the data is from the mouse
            if (mouse && !(status & MOUSE_DATA_BIT)) return 1;

            // Check if the data is from the keyboard
            if (!mouse && (status & MOUSE_DATA_BIT)) return 1;

            return 0;
        }

        // Wait for the KBC to be ready
        tickdelay(micros_to_ticks(KB_DELAY));
        attempts--;
    }

    return 1;
}

int (write_to_KBC)(uint8_t port, uint8_t command)
{
    uint8_t status;
    uint8_t attempts = MAX_ATTEMPTS;

    while (attempts)
    {
        // Read KBC to see if there is data to read
        if (util_sys_inb(KBC_STATUS_REG, &status) != 0) return 1;

        // Check if we can write to the KBC
        if ((status & FULL_IN_BUF) == 0)
        {
            // Write to the KBC
            if (sys_outb(port, command) != 0) return 1;

            return 0;
        }

        tickdelay(micros_to_ticks(KB_DELAY));
		attempts--;
    }

    return 1;
}
