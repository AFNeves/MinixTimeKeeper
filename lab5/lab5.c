#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphic.h"
#include "keyboard.h"

extern uint8_t scancode;

int main(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

    lcf_log_output("/home/lcom/labs/lab5/output.txt");
    
    if (lcf_start(argc, argv)) return 1;

    lcf_cleanup();

    return 0;
}

int (wait_for_ESC)()
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
                        kbc_ih();
                    break;
                default:
                    break;
            }
        }
    }

    if (keyboard_unsubscribe_int() != 0) return 1;

    return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay)
{
	if (set_graphic_mode(mode) != 0) return 1;

	sleep(delay);

	vg_exit();

	return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color)
{
	if (set_frame_buffer(mode) != 0) return 1;

	if (set_graphic_mode(mode) != 0) return 1;

	if (draw_rectangle(x, y, width, height, color) != 0) return 1;

	if (wait_for_ESC() != 0) return 1;

	if (set_text_mode() != 0) return 1;

	return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
	/* To be completed */
	printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
			mode, no_rectangles, first, step);

	return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y)
{
    if (set_frame_buffer(VBE_1024x768_INDEXED) != 0) return 1;

    if (set_graphic_mode(VBE_1024x768_INDEXED) != 0) return 1;

    if (print_XPM(xpm, x, y) != 0) return 1;

    if (wait_for_ESC() != 0) return 1;

    if (set_text_mode() != 0) return 1;

    return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
	/* To be completed */
	printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
			__func__, xpm, xi, yi, xf, yf, speed, fr_rate);

	return 1;
}

int(video_test_controller)() {
	/* This year you do not need to implement this */
	printf("%s(): under construction\n", __func__);

	return 1;
}
