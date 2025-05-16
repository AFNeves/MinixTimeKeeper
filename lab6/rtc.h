#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>

#include <stdint.h>

/* ----------- RTC Macros ---------- */

/* General Macros */

#define RTC_IRQ 8 /**< @brief RTC IRQ line */

#define RTC_DELAY 5000    /**< @brief Standard Delay value */
#define RTC_MAX_ATTEMPTS 5 /**< @brief Maximum number of attempts */

/* Register Address */

#define RTC_ADDR_REG 0x70 /**< @brief RTC Address Register Address */
#define RTC_DATA_REG 0x71 /**< @brief RTC Data Input/Output Register Address */

/* Register Number */

#define RTC_SECONDS 0       /**< @brief RTC Seconds Register Number */
#define RTC_SECONDS_ALARM 1 /**< @brief RTC Seconds Alarm Register Number */
#define RTC_MINUTES 2       /**< @brief RTC Minutes Register Number */
#define RTC_MINUTES_ALARM 3 /**< @brief RTC Minutes Alarm Register Number */
#define RTC_HOURS 4         /**< @brief RTC Hours Register Number */
#define RTC_HOURS_ALARM 5   /**< @brief RTC Hours Alarm Register Number */
#define RTC_DAY_OF_WEEK 6   /**< @brief RTC Day of Week Register Number */
#define RTC_DAY_OF_MONTH 7  /**< @brief RTC Day of Month Register Number */
#define RTC_MONTH 8         /**< @brief RTC Month Register Number */
#define RTC_YEAR 9          /**< @brief RTC Year Register Number */

#define RTC_REG_A 10 /**< @brief RTC Register A Number */
#define RTC_REG_B 11 /**< @brief RTC Register B Number */
#define RTC_REG_C 12 /**< @brief RTC Register C Number */
#define RTC_REG_D 13 /**< @brief RTC Register D Number */

/* Control Register Bits */

// Register A
#define RTC_UIP BIT(7) /**< @brief RTC Update In Progress Bit */

// Register B
#define RTC_SET BIT(7)  /**< @brief RTC Inhibit Update Bit */
#define RTC_PIE BIT(6)  /**< @brief RTC Periodic Interrupt Enable Bit */
#define RTC_AIE BIT(5)  /**< @brief RTC Alarm Interrupt Enable Bit */
#define RTC_UIE BIT(4)  /**< @brief RTC Update Interrupt Enable Bit */
#define RTC_DM BIT(2)   /**< @brief RTC Data Mode Bit */
#define RTC_24HR BIT(1) /**< @brief RTC 24 Hour Mode Bit */

// Register C
#define RTC_IRQF BIT(7) /**< @brief RTC Interrupt Flag Bit */
#define RTC_PF BIT(6)   /**< @brief RTC Periodic Flag Bit */
#define RTC_AF BIT(5)   /**< @brief RTC Alarm Flag Bit */
#define RTC_UF BIT(4)   /**< @brief RTC Update Flag Bit */

/* ---- Auxiliary Data Structures ---- */

/**
 * @brief Data structure that holds the RTC's time data.
*/
typedef struct {
    uint8_t hours;   /**< @brief Hours */
    uint8_t minutes; /**< @brief Minutes */
    uint8_t seconds; /**< @brief Seconds */
} rtc_time_data;

/**
 * @brief Data structure that holds the RTC's date data.
*/
typedef struct {
    uint8_t day;       /**< @brief Day */
    uint8_t month;     /**< @brief Month */
    uint8_t year;      /**< @brief Year */
    uint8_t dayNumber; /**< @brief Day of the Week */
} rtc_date_data;

/* ----------- Functions ----------- */

/**
 * @brief Subscribes the RTC's interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (rtc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes the RTC's interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_unsubscribe_int)();

/**
 * @brief Converts a BCD number to binary
 * 
 * @param bcd BCD number to convert
 * 
 * @return Converted binary number
*/
uint8_t bcd_to_bin(uint8_t bcd);

/**
 * @brief Converts a binary number to BCD
 * 
 * @param bin Binary number to convert
 * 
 * @return Converted BCD number
*/
uint8_t bin_to_bcd(uint8_t bin);

/**
 * @brief Converts the RTC's time data to 24h format
*/
void convert_to_24h();

/**
 * @brief Initializes the RTC
 * 
 * Reads the RTC's modes and sets the RTC's data structures
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_start)();

/**
 * @brief Reads a RTC register
 * 
 * Reads a given RTC register and stores the output in the given pointer
 * 
 * @param port Address to be read from
 * @param output Pointer to store the output
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_read)(uint8_t port, uint8_t *output);

/**
 * @brief Writes a byte to a RTC register
 * 
 * Writes a byte to a RTC's address register
 * 
 * @param port Address to be written to
 * @param value Value to be written
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_write)(uint8_t port, uint8_t value);

/**
 * @brief Updates the RTC's time structure
 * 
 * Reads the RTC's time and updates the RTC structure
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_update_time)();

/**
 * @brief Updates the RTC's date structure
 * 
 * Reads the RTC's date and updates the RTC structure
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_update_date)();

/**
 * @brief Sets the RTC's alarm
 * 
 * Enables the RTC's alarm interrupt and sets the alarm time
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_set_alarm)(rtc_time_data alarm_time);

/**
 * @brief Disables the RTC's alarm
 * 
 * Disables the RTC's alarm interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (rtc_disable_alarm)();

#endif /* _LCOM_RTC_H_ */
