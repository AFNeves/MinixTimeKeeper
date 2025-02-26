#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

extern int counter;

int main(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

    lcf_log_output("/home/lcom/labs/lab2/output.txt");
    
    if (lcf_start(argc, argv))
        return 1;

    lcf_cleanup();

    return 0;
}

int (timer_test_read_config)(uint8_t timer, enum timer_status_field field)
{
    uint8_t configuration;

    if (timer_get_conf(timer, &configuration) != 0) return 1;

    if (timer_display_conf(timer, configuration, field) != 0) return 1;

    return 0;
}

int (timer_test_time_base)(uint8_t timer, uint32_t freq)
{
    if (timer > 2) return 1;

    if (timer_set_frequency(timer, freq) != 0) return 1;

    return 0;
}

int (timer_test_int)(uint8_t time)
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
                    if (msg.m_notify.interrupts & irq_set) /* subscribed interrupt */
                    {
                        timer_int_handler();

                        if (counter % 60 == 0)
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
