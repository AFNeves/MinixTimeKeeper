#include <lcom/lcf.h>
#include <lcom/lab4.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"

extern int timer_counter;
extern uint8_t byte_index;
extern struct packet mouse_packet;

int main(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

    lcf_log_output("/home/lcom/labs/lab4/output.txt");
    
    if (lcf_start(argc, argv)) return 1;

    lcf_cleanup();

    return 0;
}

int (mouse_test_packet)(uint32_t cnt) {
    message msg;
    int ipc_status;

    uint8_t irq_set;
    if (mouse_subscribe_int(&irq_set) != 0) return 1;
	if (mouse_write_command(MOUSE_DATA_REPORT_ENABLE) != 0) return 1;
    
    while (cnt)
    {
        if (driver_receive(ANY, &msg, &ipc_status) != 0 ) continue;

        if (is_ipc_notify(ipc_status))
        {
            switch (_ENDPOINT_P(msg.m_source))
            {
                case HARDWARE:
                    if (msg.m_notify.interrupts & BIT(irq_set))
                    {
						mouse_ih();
						mouse_sync();

						if (byte_index == 3)
						{
							mouse_make_packet();
							mouse_print_packet(&mouse_packet);
							byte_index = 0;
							cnt--;
						}
                    }
                    break;
                default:
                    break;
            }
        }
    }

	if (mouse_write_command(MOUSE_DATA_REPORT_DISABLE) != 0) return 1;
    if (mouse_unsubscribe_int() != 0) return 1;
	
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    message msg;
    int ipc_status;

    uint8_t timer_irq_set, mouse_irq_set;
    if (timer_subscribe_int(&timer_irq_set) != 0) return 1;
    if (mouse_subscribe_int(&mouse_irq_set) != 0) return 1;
	if (mouse_write_command(MOUSE_DATA_REPORT_ENABLE) != 0) return 1;
    
    uint8_t seconds = idle_time;
    while (seconds != 0)
    {
        if (driver_receive(ANY, &msg, &ipc_status) != 0 ) continue;

        if (is_ipc_notify(ipc_status))
        {
            switch (_ENDPOINT_P(msg.m_source))
            {
                case HARDWARE:
                    if (msg.m_notify.interrupts & BIT(mouse_irq_set))
                    {
						mouse_ih();
						mouse_sync();

						if (byte_index == 3)
						{
							mouse_make_packet();
							mouse_print_packet(&mouse_packet);
							byte_index = 0;
						}
                        seconds = idle_time;
                        timer_counter = 0;
                    }
                    if (msg.m_notify.interrupts & BIT(timer_irq_set))
                    {
                        timer_int_handler();
                        if (timer_counter % sys_hz() == 0) seconds--;
                    }
                    break;
                default:
                    break;
            }
        }
    }

	if (mouse_write_command(MOUSE_DATA_REPORT_DISABLE) != 0) return 1;
    if (mouse_unsubscribe_int() != 0) return 1;
    if (timer_unsubscribe_int() != 0) return 1;
	
    return 0;
}

/*
int (mouse_test_gesture)() {
    To be completed
    printf("%s: under construction\n", __func__);
    return 1;
}
*/

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
