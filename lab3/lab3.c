#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"

extern uint8_t scancode;
extern uint8_t counter_SYS_INB;

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
                        kbd_print_scancode(!(scancode & BREAK_CODE_BIT), 1, &scancode);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (keyboard_unsubscribe_int() != 0) return 1;
    if (kbd_print_no_sysinb(counter_SYS_INB) != 0) return 1;

    return 0;
}

int (kbd_test_poll)()
{
    return 1;
}

int (kbd_test_timed_scan)(uint8_t n)
{
    return 1;
}
