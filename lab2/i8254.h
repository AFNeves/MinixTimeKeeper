#ifndef _LCOM_I8254_H_
#define _LCOM_I8254_H_

/* General Macros */

#define TIMER_IRQ  0       /**< @brief Timer 0 IRQ line */
#define TIMER_FREQ 1193182 /**< @brief Default Timer 0 frequency */

/* Port Addresses */

#define TIMER_0    0x40 /**< @brief Timer 0 register */
#define TIMER_CTRL 0x43 /**< @brief Control register */

/* Timer Control */

/* Timer Selection: Bits 7 and 6 */

#define TIMER_SEL0 0x00 /**< @brief Control Word for Timer 0 */

/* Register Selection: Bits 5 and 4 */

#define TIMER_LSB     BIT(4)                  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB     BIT(5)                  /**< @brief Initialize Counter MSB only */
#define TIMER_LSB_MSB (TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */

/* Operating Mode Selection: Bits 3, 2 and 1 */

#define TIMER_SQR_WAVE (BIT(2) | BIT(1)) /**< @brief Mode 3: Square Wave Generator Mode */
#define TIMER_RATE_GEN BIT(2)            /**< @brief Mode 2: Rate Generator Mode */

/* Counting Mode Selection: Bit 0 */

#define TIMER_BCD 0x01 /**< @brief BCD Mode */
#define TIMER_BIN 0x00 /**< @brief Binary Mode */

/* Read-Back Command */

#define TIMER_RB_SEL0   BIT(1)            /**< @brief Select Timer 0 */
#define TIMER_RB_COUNT  BIT(4)            /**< @brief Read Count Value */
#define TIMER_RB_STATUS BIT(5)            /**< @brief Read Status Value */
#define TIMER_RB_CMD    (BIT(7) | BIT(6)) /**< @brief Read Back Command */

#endif /* _LCOM_I8254_H_ */
