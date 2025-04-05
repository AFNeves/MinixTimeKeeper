#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/* General Macros */

#define KB_IRQ 1     /**< @brief Keyboard IRQ line */
#define MOUSE_IRQ 12 /**< @brief Mouse IRQ line */

#define KB_DELAY 20000 /**< @brief Delay between each attempt */
#define MAX_ATTEMPTS 5 /**< @brief Maximum number of attempts */

#define ESC_BREAKCODE 0x81    /**< @brief Breakcode for the ESC key */
#define BREAK_CODE_BIT BIT(7) /**< @brief Bit that indicates if a key is being pressed or released */

/* KBC REGISTERS */

#define KBC_STATUS_REG 0x64 /**< @brief Status register register */
#define KBC_IN_BUF 0x64     /**< @brief Input buffer register */
#define KBC_IN_BUF_ARG 0x60 /**< @brief Input buffer register */
#define KBC_OUT_BUF 0x60    /**< @brief Output buffer register */

/* STATUS REGISTER CODES */

#define PARITY_ERROR BIT(7)   /**< @brief Parity error bit */
#define TIMEOUT_ERROR BIT(6)  /**< @brief Timeout error bit */
#define MOUSE_DATA_BIT BIT(5) /**< @brief Mouse data available bit */
#define FULL_IN_BUF BIT(1)    /**< @brief Full input buffer bit */
#define FULL_OUT_BUF BIT(0)   /**< @brief Full output buffer bit */

/* KBC Commands Values */

#define KBC_READ_CMD 0x20    /**< @brief Read command for the KBC */
#define KBC_WRITE_CMD 0x60   /**< @brief Write command for the KBC */
#define KBC_WRITE_MOUSE 0xD4 /**< @brief Write command for the mouse */

/* KBC Command Byte */

#define KBC_KB_INT BIT(0)    /**< @brief Keyboard interrupt enable bit */
#define KBC_MOUSE_INT BIT(1) /**< @brief Mouse interrupt enable bit */

/* Mouse Macros */

#define MOUSE_ACK  0xFA /**< @brief Mouse Acknowledgment byte */
#define MOUSE_NACK 0xFE /**< @brief Mouse Error byte */

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

#endif /* _LCOM_I8042_H */
