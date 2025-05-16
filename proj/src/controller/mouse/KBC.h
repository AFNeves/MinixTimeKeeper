#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../utils.h"

#include "i8042.h"

/**
 * @brief Reads the KBC output buffer
 * 
 * @param byte Pointer to the byte to store the read value
 * @param mouse Indicates if the data is from the mouse (1) or keyboard (0)
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (read_KBC_output)(uint8_t *byte, uint8_t mouse);

/**
 * @brief Writes a command to the KBC
 * 
 * @param port The port to write to
 * @param command The command to write
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (write_to_KBC)(uint8_t port, uint8_t command);

#endif /* _LCOM_KBC_H_ */
