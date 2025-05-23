#ifndef _LCOM_GRAPHIC_H_
#define _LCOM_GRAPHIC_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "VBE.h"

int (set_graphic_mode)(uint16_t submode);

int (set_text_mode)();

int (set_frame_buffer)(uint16_t mode);

int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (draw_XPM)(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif /* _LCOM_GRAPHIC_H_ */
