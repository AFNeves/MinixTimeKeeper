#ifndef _LCOM_UTILS_H_
#define _LCOM_UTILS_H_

#include <lcom/lcf.h>
#include <stdint.h>

#ifndef BIT
#define BIT(n) (1 << (n))
#endif

/* ---------- Data Structures ---------- */

/**
 * @brief Data structure that holds the time data.
*/
typedef struct {
    uint8_t hours;   /**< @brief Hours */
    uint8_t minutes; /**< @brief Minutes */
    uint8_t seconds; /**< @brief Seconds */
} time_struct;

/**
 * @brief Data structure that holds the date data.
*/
typedef struct {
    uint8_t day;       /**< @brief Day */
    uint8_t month;     /**< @brief Month */
    uint8_t year;      /**< @brief Year */
    uint8_t dayNumber; /**< @brief Day of the Week */
} date_struct;

/* ---------- Functions ---------- */

/**
 * @brief Retrieves the least significant byte of a 16-bit value
 * 
 * @param val 16-bit value to be processed
 * @param lsb Address of memory to store the least significant byte
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Retrieves the most significant byte of a 16-bit value
 * 
 * @param val 16-bit value to be processed
 * @param msb Address of memory to store the most significant byte
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 * @brief Reads a byte from a specified port and converts it to an 8-bit value
 * 
 * @param port Port to read from
 * @param value Address of memory to store the processed value
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (util_sys_inb)(int port, uint8_t *value);

#endif /* _LCOM_UTILS_H_ */
