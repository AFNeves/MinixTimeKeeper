#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include "controller/video/graphic.h"

typedef struct {
    uint16_t x, y, height, width;
    uint32_t *colors;
    uint32_t color;
    bool pressed;
} Sprite; 

Sprite *create_sprite_xpm(xpm_map_t sprite);
Sprite *create_sprite_button(uint16_t width, uint16_t height, uint32_t color);
void destroy_sprite(Sprite *sprite);

#endif
