#include <lcom/lcf.h>

#include "model/model.h"
#include "view/view.h"

extern SystemState systemState;

int (main)(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/proj/src/debug/trace.txt");

    lcf_log_output("/home/lcom/labs/proj/src/debug/output.txt");

    if (lcf_start(argc, argv)) return 1;

    lcf_cleanup();

    return 0;
}

int setup()
{
    // Setup the Timer frequency
    if (timer_set_frequency(0, GAME_FREQUENCY) != 0) return 1;

    // Setup the frame buffers
    if (set_frame_buffers(VIDEO_MODE) != 0) return 1;

    // Set the video mode
    if (set_graphic_mode(VIDEO_MODE) != 0) return 1;

    // Setup the Sprites
    setup_sprites();

    // Subscribe to interrupts
    if (timer_subscribe_ints() != 0) return 1;
    if (keyboard_subscribe_int() != 0) return 1;
    if (mouse_subscribe_int() != 0) return 1;
    if (rtc_subscribe_int() != 0) return 1;

    // Enable Mouse Stream and Data Reporting
    if (mouse_write_command(MOUSE_DATA_STREAM_MODE) != 0) return 1;
    if (mouse_write_command(MOUSE_DATA_REPORT_ENABLE) != 0) return 1;

    // Start the RTC
    rtc_start();

    return 0;
}

int cleanup()
{
    // Return to Text Mode
    if (vg_exit() != 0) return 1;

    // Destroy all Sprites
    destroy_sprites();

    // Unsubscribe from interrupts
    if (timer_unsubscribe_int() != 0) return 1;
    if (keyboard_unsubscribe_int() != 0) return 1;
    if (mouse_unsubscribe_int() != 0) return 1;
    if (rtc_unsubscribe_int() != 0) return 1;

    // Disable Data Reporting
    if (mouse_write_command(MOUSE_DATA_REPORT_DISABLE) != 0) return 1;

    // Stops the RTC
    rtc_stop();

    return 0;
}

int (proj_main_loop)(int argc, char *argv[])
{
    // Minix Initialization
    if (setup() != 0) return cleanup();

    // Draw the initial frame
    draw_new_frame();

    // Interruption Variables
    message msg;
    int ipc_status;

    while (systemState == RUNNING)
    {
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

        if (is_ipc_notify(ipc_status))
        {
            switch(_ENDPOINT_P(msg.m_source))
            {
                case HARDWARE: 
                    if (msg.m_notify.interrupts & TIMER_MASK)    update_timer_state();
                    if (msg.m_notify.interrupts & KB_MASK)       update_keyboard_state();
                    if (msg.m_notify.interrupts & MOUSE_MASK)    update_mouse_state();
                    if (msg.m_notify.interrupts & RTC_MASK)      rtc_ih();
                    break;
                default:
                    break;
            }
        }
    }

    // Minix Cleanup
    if (cleanup() != 0) return 1;

    return 0;
}
