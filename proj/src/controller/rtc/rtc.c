#include "rtc.h"

int rtc_hook_id = 3;
uint8_t rtc_mode;
uint8_t rtc_time_format;
uint8_t rtc_int_cause;
uint8_t rtc_original_config;
time_struct rtc_time;
date_struct rtc_date;

int (rtc_subscribe_int)()
{
    return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_hook_id);
}

int (rtc_unsubscribe_int)()
{
    return sys_irqrmpolicy(&rtc_hook_id);
}

void (rtc_ih)()
{
    if (rtc_read(RTC_REG_C, &rtc_int_cause) != 0) return;

    if (rtc_int_cause & RTC_UF) rtc_update();

    if (rtc_int_cause & RTC_AF) rtc_disable_alarm();

    if (rtc_int_cause & RTC_PF) return; // Not intended for this project
}

int (rtc_start)()
{
    uint8_t output;
    if (rtc_read(RTC_REG_B, &output)) return 1;

    rtc_mode = output & RTC_DM;
    rtc_time_format = output & RTC_24HR;

    rtc_original_config = output; // Save original config
    output |= RTC_UIE; // Enable updates

    if (rtc_write(RTC_REG_B, output)) return 1;

    return rtc_update();
}

int (rtc_stop)()
{
    return rtc_write(RTC_REG_B, rtc_original_config);
}

int (rtc_update)()
{
    uint8_t output;
    uint8_t attempts = RTC_MAX_ATTEMPTS;

    while (attempts)
    {
        if (rtc_read(RTC_REG_A, &output)) return 1;

        if (!(output & RTC_UIP))
        {
            if (rtc_read(RTC_SECONDS, &output)) return 1;
            rtc_time.seconds = rtc_mode ? output : bcd_to_bin(output);

            if (rtc_read(RTC_MINUTES, &output)) return 1;
            rtc_time.minutes = rtc_mode ? output : bcd_to_bin(output);

            if (rtc_read(RTC_HOURS, &output)) return 1;
            rtc_time.hours = rtc_mode ? output : bcd_to_bin(output);

            if (rtc_read(RTC_DAY_OF_MONTH, &output)) return 1;
            rtc_date.day = rtc_mode ? output : bcd_to_bin(output);

            if (rtc_read(RTC_MONTH, &output)) return 1;
            rtc_date.month = rtc_mode ? output : bcd_to_bin(output);

            if (rtc_read(RTC_YEAR, &output)) return 1;
            rtc_date.year = rtc_mode ? output : bcd_to_bin(output);

            if (rtc_read(RTC_DAY_OF_WEEK, &output)) return 1;
            rtc_date.dayNumber = rtc_mode ? output : bcd_to_bin(output);

            if (!rtc_time_format) convert_to_24h();

            return 0;
        }

        tickdelay(micros_to_ticks(RTC_DELAY));
        attempts--;
    }

    return 1;
}

int (rtc_set_alarm)(time_struct alarm_time)
{
    uint8_t output;
    uint8_t attempts = RTC_MAX_ATTEMPTS;

    // Disable updates
    if (rtc_read(RTC_REG_B, &output)) return 1;
    output |= RTC_SET; // Disable updates
    output |= RTC_AIE; // Enable alarm interrupt
    if (rtc_write(RTC_REG_B, output)) return 1;

    while (attempts)
    {
        if (rtc_read(RTC_REG_A, &output)) return 1;

        if (!(output & RTC_UIP))
        {
            if (rtc_mode) {
                if (rtc_write(RTC_SECONDS_ALARM, alarm_time.seconds) != 0) return 1;
                if (rtc_write(RTC_MINUTES_ALARM, alarm_time.minutes) != 0) return 1;
                if (rtc_write(RTC_HOURS_ALARM, alarm_time.hours) != 0) return 1;
            } else {
                if (rtc_write(RTC_SECONDS_ALARM, bin_to_bcd(alarm_time.seconds)) != 0) return 1;
                if (rtc_write(RTC_MINUTES_ALARM, bin_to_bcd(alarm_time.minutes)) != 0) return 1;
                if (rtc_write(RTC_HOURS_ALARM, bin_to_bcd(alarm_time.hours)) != 0) return 1;
            }
            break;
        }
    }

    // Enable updates
    if (rtc_read(RTC_REG_B, &output)) return 1;
    output &= ~RTC_SET; // Enable updates
    if (rtc_write(RTC_REG_B, output)) return 1;

    return 0;
}

int (rtc_disable_alarm)()
{
    uint8_t output;

    // Disable updates
    if (rtc_read(RTC_REG_B, &output)) return 1;
    output &= ~RTC_AIE; // Disable alarm interrupt
    if (rtc_write(RTC_REG_B, output)) return 1;

    return 0;
}

int (rtc_read)(uint8_t port, uint8_t *output)
{
    if (sys_outb(RTC_ADDR_REG, port) != 0) return 1;

    if (util_sys_inb(RTC_DATA_REG, output) != 0) return 1;

    return 0;
}

int (rtc_write)(uint8_t port, uint8_t value)
{
    if (sys_outb(RTC_ADDR_REG, port) != 0) return 1;

    if (sys_outb(RTC_DATA_REG, value) != 0) return 1;

    return 0;
}

uint8_t bcd_to_bin(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0xF);
}

uint8_t bin_to_bcd(uint8_t bin)
{
    return ((bin / 10) << 4) | (bin % 10);
}

void convert_to_24h()
{
    uint8_t is_PM = rtc_time.hours & BIT(7);

    rtc_time.hours = rtc_time.hours & 0x7F;

    if (is_PM) rtc_time.hours = rtc_time.hours + 12;

    if (rtc_time.hours == 24) rtc_time.hours = 0;
}
