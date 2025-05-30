#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../KBC.h"

#include "../video/graphic.h"

/**
 * @brief Subscribes the Mouse interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (mouse_subscribe_int)();

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
 * @brief Builds the MouseInfo structure
 * 
 * Builds the MouseInfo structure based on the mouse data
 */
void (update_mouse_info)();

/**
 * @brief Writes a command to the mouse
 * 
 * @param command The command to be sent to the mouse
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (mouse_write_command)(uint8_t command);

#endif /* _LCOM_MOUSE_H_ */
