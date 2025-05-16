#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"

extern uint8_t scancode;
extern int timer_counter;

#ifdef LAB3
extern uint32_t counter_SYS_INB;
#endif

int main(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

    lcf_log_output("/home/lcom/labs/lab3/output.txt");
    
    if (lcf_start(argc, argv)) return 1;

    lcf_cleanup();

    return 0;
}

int (kbd_test_scan)()
{
    message msg;
    int ipc_status;

    uint8_t irq_set;
    if (keyboard_subscribe_int(&irq_set) != 0) return 1;
    
    while (scancode != ESC_BREAKCODE)
    {
        if (driver_receive(ANY, &msg, &ipc_status) != 0 ) continue;

        if (is_ipc_notify(ipc_status))
        {
            switch (_ENDPOINT_P(msg.m_source))
            {
                case HARDWARE:
                    if (msg.m_notify.interrupts & BIT(irq_set))
                    {
                        kbc_ih();
                        kbd_print_scancode(!(scancode & BREAK_CODE_BIT), 1, &scancode);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (keyboard_unsubscribe_int() != 0) return 1;

    #ifdef LAB3
    if (kbd_print_no_sysinb(counter_SYS_INB) != 0) return 1;
    #endif

    return 0;
}

int (kbd_test_poll)()
{
    while (scancode != ESC_BREAKCODE)
    {
        if (read_KBC_output(&scancode) == 0)
            kbd_print_scancode(!(scancode & BREAK_CODE_BIT), 1, &scancode);
    }

    #ifdef LAB3
    if (kbd_print_no_sysinb(counter_SYS_INB) != 0) return 1;
    #endif

    return keyboard_poll_restore();
}

int (kbd_test_timed_scan)(uint8_t n)
{
    message msg;
    int ipc_status;

    uint8_t timer_irq_set, kbd_irq_set;
    if (timer_subscribe_int(&timer_irq_set) != 0) return 1;
    if (keyboard_subscribe_int(&kbd_irq_set) != 0) return 1;
    
    uint8_t seconds = 0;
    while (scancode != ESC_BREAKCODE && seconds < n)
    {
        if (driver_receive(ANY, &msg, &ipc_status) != 0 ) continue;

        if (is_ipc_notify(ipc_status))
        {
            switch (_ENDPOINT_P(msg.m_source))
            {
                case HARDWARE:
                    if (msg.m_notify.interrupts & BIT(kbd_irq_set))
                    {
                        kbc_ih();
                        kbd_print_scancode(!(scancode & BREAK_CODE_BIT), 1, &scancode);
                        seconds = 0;
                        timer_counter = 0;
                    }
                    if (msg.m_notify.interrupts & BIT(timer_irq_set))
                    {
                        timer_int_handler();
                        if (timer_counter % sys_hz() == 0) seconds++;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (timer_unsubscribe_int() != 0) return 1;
    if (keyboard_unsubscribe_int() != 0) return 1;

    return 0;
}
