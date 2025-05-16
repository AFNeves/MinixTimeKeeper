#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "i8042.h"

int (read_KBC_output)(uint8_t *byte, uint8_t mouse);

int (write_to_KBC)(uint8_t port, uint8_t command);

#endif /* _LCOM_KBC_H_ */
