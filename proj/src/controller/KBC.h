#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "utils.h"

/* ---------- Macros ---------- */

/* General Macros */

#define KB_IRQ    1  /**< @brief Keyboard IRQ Line */
#define MOUSE_IRQ 12 /**< @brief Mouse IRQ Line */

#define KB_MASK    BIT(1) /**< @brief Keyboard IRQ Mask */
#define MOUSE_MASK BIT(2) /**< @brief Mouse IRQ Mask */

#define KB_DELAY     20000 /**< @brief Delay Between each Attempt */
#define MAX_ATTEMPTS 5     /**< @brief Maximum Number of Attempts */

#define ESC_BREAKCODE  0x81   /**< @brief Breakcode for the ESC key */
#define BREAK_CODE_BIT BIT(7) /**< @brief Bit that indicates if a key is being pressed or released */

/* KBC REGISTERS */

#define KBC_STATUS_REG 0x64 /**< @brief Status Register Register */
#define KBC_IN_BUF     0x64 /**< @brief Input Buffer Register */
#define KBC_IN_BUF_ARG 0x60 /**< @brief Input Buffer Register */
#define KBC_OUT_BUF    0x60 /**< @brief Output Buffer Register */

/* STATUS REGISTER CODES */

#define PARITY_ERROR   BIT(7) /**< @brief Parity Error Bit */
#define TIMEOUT_ERROR  BIT(6) /**< @brief Timeout Error Bit */
#define MOUSE_DATA_BIT BIT(5) /**< @brief Mouse Data Available Bit */
#define FULL_IN_BUF    BIT(1) /**< @brief Full Input Buffer Bit */
#define FULL_OUT_BUF   BIT(0) /**< @brief Full Output Buffer Bit */

/* KBC Commands Values */

#define KBC_READ_CMD    0x20 /**< @brief Read Command for the KBC */
#define KBC_WRITE_CMD   0x60 /**< @brief Write Command for the KBC */
#define KBC_WRITE_MOUSE 0xD4 /**< @brief Write Command for the Mouse */

/* KBC Command Byte */

#define KBC_KB_INT    BIT(0) /**< @brief Keyboard Interrupt Enable Bit */
#define KBC_MOUSE_INT BIT(1) /**< @brief Mouse Interrupt Enable Bit */

/* Mouse Macros */

#define MOUSE_ACK  0xFA /**< @brief Mouse Acknowledgment Byte */
#define MOUSE_NACK 0xFE /**< @brief Mouse Error Byte */

#define MOUSE_DATA_STREAM_MODE    0xEA /**< @brief Set Stream Mode */
#define MOUSE_DATA_REPORT_ENABLE  0xF4 /**< @brief Enable Data Reporting */
#define MOUSE_DATA_REPORT_DISABLE 0xF5 /**< @brief Disable Data Reporting */

#define MOUSE_OVERFLOW_Y BIT(7) /**< @brief Y Overflow */
#define MOUSE_OVERFLOW_X BIT(6) /**< @brief X Overflow */
#define MOUSE_SIGNAL_Y   BIT(5) /**< @brief Y Sign */
#define MOUSE_SIGNAL_X   BIT(4) /**< @brief X Sign */
#define FIRST_BYTE       BIT(3) /**< @brief First Byte */
#define MOUSE_MB         BIT(2) /**< @brief Middle Button */
#define MOUSE_RB         BIT(1) /**< @brief Right Button */
#define MOUSE_LB         BIT(0) /**< @brief Left Button */

/* ---------- Functions ---------- */

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
