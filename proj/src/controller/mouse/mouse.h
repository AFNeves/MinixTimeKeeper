#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../utils.h"

#include "i8042.h"

#include "KBC.h"

typedef struct {
    int x, y;
    bool left_click, right_click;
} MouseInfo;

extern MouseInfo mouse_info;

/**
 * @brief Subscribes the Mouse interrupts
 * 
 * @param bit_no Pointer to store the bit number
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes the Mouse interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (mouse_unsubscribe_int)();

/**
 * @brief Mouse Interrupt Handler
 * 
 * Reads the KBC's output buffer and stores the scancode
 */
void (mouse_ih)();

/**
 * @brief Synchronizes the mouse data
 * 
 * Stores the mouse data in the mouse_data array
 */
void (mouse_sync)();

/**
 * @brief Makes a mouse packet
 * 
 * Creates a mouse packet from the mouse data
 */
void (mouse_make_packet)();

/**
 * @brief Writes a command to the mouse
 * 
 * @param command The command to be sent to the mouse
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (mouse_write_command)(uint8_t command);

#endif /* _LCOM_MOUSE_H_ */
