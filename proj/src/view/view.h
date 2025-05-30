#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "config.h"
#include "controller/video/graphic.h"
#include "controller/mouse/mouse.h"
#include "controller/rtc/rtc.h"
#include "model/sprite.h"
#include "model/model.h"


extern uint8_t *drawing_frame_buffer;
extern uint8_t *main_frame_buffer;
extern int buttonStart_x;
extern int buttonStart_y;
extern int buttonPause_x;
extern int buttonPause_y;
extern int buttonReset_x;
extern int buttonReset_y;
extern int dx;


void draw_new_frame();
void draw_time();
void draw_chrono_menu();
void draw_chrono_buttons();
void draw_toolbar();
void draw_mouse();
void swap_buffers();
void display_real_time();
int draw_sprite_xpm(Sprite *sprite, int x, int y);
int draw_sprite_button(Sprite *sprite, int x, int y);
int set_frame_buffers(uint16_t mode);
void draw_text(const char *text, int x, int y, uint32_t color);


#endif
