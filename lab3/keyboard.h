#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "i8254.h"
#include "i8042.h"

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

void (kbc_ih)();

int (read_KBC_output)();

#endif /* _LCOM_KEYBOARD_H_ */
