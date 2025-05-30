#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/timer/timer.h"
#include "controller/keyboard/keyboard.h"
#include "controller/mouse/mouse.h"
#include "controller/video/graphic.h"
#include "controller/rtc/rtc.h"
#include "view/view.h"
#include "model/sprite.h"
#include "config.h"

#include "xpm/colon.xpm"
#include "xpm/mouse.xpm"
#include "xpm/num_0.xpm"
#include "xpm/num_1.xpm"
#include "xpm/num_2.xpm"
#include "xpm/num_3.xpm"
#include "xpm/num_4.xpm"
#include "xpm/num_5.xpm"
#include "xpm/num_6.xpm"
#include "xpm/num_7.xpm"
#include "xpm/num_8.xpm"
#include "xpm/num_9.xpm"
#include "xpm/slash.xpm"
#include "xpm/timer.xpm"
#include "xpm/chrono.xpm"
#include "xpm/clock.xpm"


extern Sprite *mouse;
extern Sprite *buttonStart;
extern Sprite *buttonPause;
extern Sprite *buttonReset;
extern Sprite *colon;
extern Sprite *digits[10];
extern Sprite *toolbar_button_sprites[3];
extern Sprite *slash;


typedef enum {
    RUNNING,
    EXIT,
} SystemState;

typedef enum {
    RUNNING_CLOCK,
    CHRONO,
    TIMER
} MenuState;

typedef enum {
    ON,
    OFF
} ChronoState;




void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_rtc_state();
void update_chrono_buttons();
void update_toolbar_buttons();
void setup_sprites();
void destroy_sprites();

// Helper functions
bool is_mouse_over_button(Sprite* button, int x, int y);

#endif
