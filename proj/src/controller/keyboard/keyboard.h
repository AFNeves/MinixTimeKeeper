#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#define KEYBOARD_MASK BIT(1)

#include <lcom/lcf.h>
#include <stdint.h>
#include "../utils.h"
#include "KBC.h"

extern uint8_t scancode;

/**
 * @brief Subscribes the Keyboard interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (keyboard_subscribe_interrupts)();

/**
 * @brief Unsubscribes the Keyboard interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (keyboard_unsubscribe_int)();

/**
 * @brief Keyboard Interrupt Handler
 * 
 * Reads the KBC's output buffer and stores the scancode
 */
void (kbc_ih)();

#endif /* _LCOM_KEYBOARD_H_ */
