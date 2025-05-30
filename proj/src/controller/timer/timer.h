#ifndef _LCOM_TIMER_H_
#define _LCOM_TIMER_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../utils.h"

#include "i8254.h"

/**
 * @brief Subscribes the Timer interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (timer_subscribe_int)();

/**
 * @brief Unsubscribes the Timer interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (timer_unsubscribe_int)();

/**
 * @brief Timer Interrupt Handler
 * 
 * Increments the timer_counter variable
 */
void (timer_ih)();

/**
 * @brief Gets the configuration of the timer
 * 
 * @param timer The timer number (0, 1, or 2)
 * @param st Pointer to store the configuration
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st);

/**
 * @brief Sets the frequency of the timer
 * 
 * @param timer The timer number (0, 1, or 2)
 * @param freq The frequency to set
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

#endif /* _LCOM_TIMER_H_ */
