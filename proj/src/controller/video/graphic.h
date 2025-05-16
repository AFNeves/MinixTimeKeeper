#ifndef _LCOM_GRAPHIC_H_
#define _LCOM_GRAPHIC_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../utils.h"

#include "VBE.h"

/**
 * @brief Sets the graphics mode using VESA BIOS Extensions.
 * 
 * @param submode The mode to set.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (set_graphic_mode)(uint16_t submode);

/**
 * @brief Sets the text mode using VESA BIOS Extensions.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (set_text_mode)();

/**
 * @brief Sets the frame buffer for the specified mode.
 * 
 * @param mode The mode to set.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (set_frame_buffer)(uint16_t mode);

/**
 * @brief Draws a XPM image on the screen.
 * 
 * @param xpm The XPM image to draw.
 * @param x The x coordinate of the top-left corner.
 * @param y The y coordinate of the top-left corner.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (draw_XPM)(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif /* _LCOM_GRAPHIC_H_ */
