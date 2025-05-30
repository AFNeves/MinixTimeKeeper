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
#include "xpm/sun.xpm"
#include "xpm/mon.xpm"
#include "xpm/tue.xpm"
#include "xpm/wed.xpm"
#include "xpm/thu.xpm"
#include "xpm/fri.xpm"
#include "xpm/sat.xpm"
#include "xpm/start.xpm"
#include "xpm/pause.xpm"
#include "xpm/reset.xpm"


extern Sprite *mouse;
extern Sprite *colon;
extern Sprite *slash;

extern Sprite *block;

extern Sprite *days_of_week[7];
extern Sprite *digits[10];
extern Sprite *toolbar_buttons[3];
extern Sprite *chrono_buttons[3];
extern int chrono_seconds;
extern int timer_seconds;
extern int timer_input[6];
extern int timer_input_length;


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

extern SystemState systemState;
extern MenuState menuState;
extern ChronoState chronoState;
extern ChronoState timerState;


void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_chrono_buttons();
void update_toolbar_buttons();
void update_timer_buttons();
void setup_sprites();
void destroy_sprites();
void insert_new_input(int new_input);
void delete_last_input();

// Helper functions
bool is_mouse_over_button(Sprite* button);

#endif
