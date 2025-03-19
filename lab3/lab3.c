#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.c"

extern uint8_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
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
                        kbd_print_scancode(!(scancode & BREAK_CODE), 1, &scancode);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (keyboard_unsubscribe_int() != 0) return 1;

    return 0;
}

int (kbd_test_poll)()
{
  int ipc_status, r;
    message msg;

    uint8_t irq_set;
    if (timer_subscribe_int(&irq_set) != 0) return 1;
    
    while (time > 0) {
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */                
                    if (msg.m_notify.interrupts & BIT(irq_set)) /* subscribed interrupt */
                    {
                        timer_int_handler();

                        if (counter % sys_hz() == 0) 
                        {
                            timer_print_elapsed_time();
                            time--;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (timer_unsubscribe_int() != 0) return 1;

    return 0;
}

int (kbd_test_timed_scan)(uint8_t n)
{
  int ipc_status, r;
    message msg;

    uint8_t irq_set;
    if (keyb(&irq_set) != 0) return 1;
    
    while (time > 0) {
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */                
                    if (msg.m_notify.interrupts & BIT(irq_set)) /* subscribed interrupt */
                    {
                        timer_int_handler();

                        if (counter % sys_hz() == 0) 
                        {
                            timer_print_elapsed_time();
                            time--;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (timer_unsubscribe_int() != 0) return 1;

    return 0;
}
