#ifndef _LCOM_I8254_H_
#define _LCOM_I8254_H_

/* General Macros */

#define TIMER_IRQ  0       /**< @brief Timer 0 IRQ line */
#define TIMER_FREQ 1193182 /**< @brief Default Timer 0 frequency */

/* Port Addresses */

#define TIMER_0    0x40 /**< @brief Timer 0 register */
#define TIMER_1    0x41 /**< @brief Timer 1 register */
#define TIMER_2    0x42 /**< @brief Timer 2 register */
#define TIMER_CTRL 0x43 /**< @brief Control register */

/* Timer Control */

/* Timer Selection: Bits 7 and 6 */

#define TIMER_SEL0 0x00   /**< @brief Control Word for Timer 0 */
#define TIMER_SEL1 BIT(6) /**< @brief Control Word for Timer 1 */
#define TIMER_SEL2 BIT(7) /**< @brief Control Word for Timer 2 */

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

#define TIMER_RB_COUNT_  BIT(5)           /**< @brief Read Count Value */
#define TIMER_RB_STATUS_ BIT(4)           /**< @brief Read Status Value */
#define TIMER_RB_SEL(n)  BIT((n) + 1)     /**< @brief Select Timer for Read-Back */
#define TIMER_RB_CMD    (BIT(7) | BIT(6)) /**< @brief Read Back Command */

#endif /* _LCOM_I8254_H_ */