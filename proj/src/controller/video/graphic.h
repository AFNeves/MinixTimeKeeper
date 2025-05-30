#ifndef _LCOM_GRAPHIC_H_
#define _LCOM_GRAPHIC_H_

#include <lcom/lcf.h>

#include <stdint.h>

#include "../utils.h"

/* ----------- VBE Macros ---------- */

#define VBE_1024x768_INDEXED 0x105 /**< @brief VBE mode for 1024x768 resolution */
#define VBE_640x480          0x110 /**< @brief VBE mode for 640x480 resolution */
#define VBE_800x600          0x115 /**< @brief VBE mode for 800x600 resolution */
#define VBE_1280x1024        0x11A /**< @brief VBE mode for 1280x1024 resolution */
#define VBE_1152x864         0x14C /**< @brief VBE mode for 1152x864 resolution */

/* ----------- Functions ----------- */

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
 * @param frame_buffer The frame buffer pointer to be used.
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (set_frame_buffer)(uint16_t mode, uint8_t **frame_buffer);

/**
 * @brief Draws a pixel on a buffer.
 *
 * @param x The X coordinate of the pixel.
 * @param y The Y coordinate of the pixel.
 * @param color The color of the pixel.
 * @param buffer The buffer where the pixel will be drawn.
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color, uint8_t *buffer);

/**
 * @brief Draws a line of pixels on a buffer.
 *
 * @param x The X coordinate of the starting pixel.
 * @param y The Y coordinate of the starting pixel.
 * @param len The length of the line in pixels.
 * @param color The color of the line.
 * @param buffer The buffer where the line will be drawn.
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int (draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint8_t *buffer);

/**
 * @brief Draws a rectangle on a buffer.
 *
 * @param x The X coordinate of the top-left corner.
 * @param y The Y coordinate of the top-left corner.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 * @param buffer The buffer where the rectangle will be drawn.
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint8_t *buffer);

/**
 * @brief Draws a XPM image on the screen.
 *
 * @param xpm The XPM image to draw.
 * @param x The x coordinate of the top-left corner.
 * @param y The y coordinate of the top-left corner.
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int (draw_XPM)(xpm_map_t xpm, uint16_t x, uint16_t y, uint8_t *buffer);

#endif /* _LCOM_GRAPHIC_H_ */
