#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/* General Macros */

#define KB_IRQ 1 /**< @brief Keyboard IRQ line */

#define KB_DELAY 20000 /**< @brief Delay between each attempt */
#define MAX_ATTEMPTS 5 /**< @brief Maximum number of attempts */

#define ESC_BREAKCODE 0x81     /**< @brief Breakcode for the ESC key */
#define BREAK_CODE_BIT BIT(7)  /**< @brief Bit that indicates if a key is being pressed or released */

/* KBC REGISTERS */

#define KBC_STATUS_REG 0x64 /**< @brief Status register register */
#define KBC_IN_BUF 0x64     /**< @brief Input buffer register */
#define KBC_IN_BUF_ARG 0x60 /**< @brief Input buffer register */
#define KBC_OUT_BUF 0x60    /**< @brief Output buffer register */

/* STATUS REGISTER CODES */

#define PARITY_ERROR BIT(7)  /**< @brief Parity error bit */
#define TIMEOUT_ERROR BIT(6) /**< @brief Timeout error bit */
#define FULL_IN_BUF BIT(1)   /**< @brief Full input buffer bit */
#define FULL_OUT_BUF BIT(0)  /**< @brief Full output buffer bit */

/* KBC Commands Values */

#define KBC_READ_CMD 0x20 /**< @brief Read command for the KBC */
#define KBC_WRITE_CMD 0x60 /**< @brief Write command for the KBC */

#endif /* _LCOM_I8042_H */
