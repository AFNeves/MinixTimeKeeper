#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/keyboard/KBC.h"
#include "controller/mouse/mouse.h"
#include "controller/video/graphic.h"
#include "controller/rtc/rtc.h"
//#include "xpm/hand.xpm"
#include "xpm/mouse.xpm"
//#include "xpm/smile.xpm"
#include "view/view.h"
#include "model/sprite.h"
#include "config.h"

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
#include "xpm/colon.xpm"

typedef enum {
    RUNNING,
    EXIT,
} SystemState;

typedef enum {
    START,
    GAME,
    END
} MenuState;

void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_buttons_state();
void update_rtc_state();
void setup_sprites();
void destroy_sprites();

#endif
