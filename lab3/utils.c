#include <lcom/lcf.h>

#include <stdint.h>

uint8_t counter_SYS_INB = 0;

/**
 * @brief Retrieves the least significant byte of a 16-bit value.
 * 
 * @param val 16-bit value to be processed.
 * @param lsb Address of memory to store the least significant byte.
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (util_get_LSB)(uint16_t val, uint8_t *lsb) {
    if (lsb == NULL) return 1;

    *lsb = (uint8_t) val;

    return 0;
}

/**
 * @brief Retrieves the most significant byte of a 16-bit value.
 * 
 * @param val 16-bit value to be processed.
 * @param msb Address of memory to store the most significant byte.
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (util_get_MSB)(uint16_t val, uint8_t *msb) {
    if (msb == NULL) return 1;

    *msb = (uint8_t) (val >> 8);

    return 0;
}

/**
 * @brief Reads a byte from a specified port and converts it to a 8-bit value.
 * 
 * @param port Port to read from.
 * @param value Address of memory to store the value processed.
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (util_sys_inb)(int port, uint8_t *value) {
    if (value == NULL) return 1;

    uint32_t val;
    int ret = sys_inb(port, &val); counter_SYS_INB++;
    *value = (uint8_t) val;

    return ret;
}
