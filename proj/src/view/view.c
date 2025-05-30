#include "view.h"

// Variáveis externas importantes à visualização do modelo e dos seus estados
uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;

extern MenuState menuState;
extern int chrono_seconds;

// Mouse Information
extern MouseInfo mouse_info;

// Graphical Information
extern vbe_mode_info_t vbe_info;

// RTC Data Structures
extern time_struct rtc_time;
extern date_struct rtc_date;

static const uint8_t font8x8_basic[128][8] = {
  ['A'] = {0x18,0x24,0x42,0x7E,0x42,0x42,0x42,0x00},
  ['E'] = {0x7E,0x40,0x40,0x7C,0x40,0x40,0x7E,0x00},
  ['P'] = {0x7C,0x42,0x42,0x7C,0x40,0x40,0x40,0x00},
  ['R'] = {0x7C,0x42,0x42,0x7C,0x48,0x44,0x42,0x00},
  ['S'] = {0x3C,0x40,0x40,0x3C,0x02,0x02,0x7C,0x00},
  ['T'] = {0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00},
  ['U'] = {0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},
};

int set_frame_buffers(uint16_t mode) {
    if (set_frame_buffer(mode, &main_frame_buffer)) return 1;
    frame_buffer_size = vbe_info.XResolution * vbe_info.YResolution * ((vbe_info.BitsPerPixel + 7) / 8);
    if (DOUBLE_BUFFER) {
        secondary_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
        drawing_frame_buffer = secondary_frame_buffer;
    } else {
        drawing_frame_buffer = main_frame_buffer;
    }
    return 0;
}

void swap_buffers() {
    memcpy(main_frame_buffer, secondary_frame_buffer, frame_buffer_size);
}

void draw_new_frame() {
    switch (menuState) {
        case RUNNING_CLOCK:
            draw_time();
            break;
        case CHRONO:
            draw_chrono_menu();
            break;
        case TIMER:
            // draw_timer_menu();
            break;
    }
    draw_toolbar();
    draw_mouse();
}

void draw_time() {
    draw_rectangle(0, 0, vbe_info.XResolution, vbe_info.YResolution, PRESSED, drawing_frame_buffer);
    display_real_time();
}


void draw_chrono_menu() {
    draw_rectangle(0, 0, vbe_info.XResolution, vbe_info.YResolution, DARKBLUE, drawing_frame_buffer);
    draw_chrono_buttons();
    
    int minutes = chrono_seconds / 60;
    int seconds = chrono_seconds % 60;

    int dx = 55;
    int x = vbe_info.XResolution / 2 - 2.5 * dx;
    int y = 100;

    draw_sprite_xpm(digits[minutes / 10], x, y);
    draw_sprite_xpm(digits[minutes % 10], x + dx, y);
    draw_sprite_xpm(digits[minutes / 10], x, y);
    draw_sprite_xpm(digits[minutes % 10], x + dx, y);
    draw_sprite_xpm(colon, x + 2 * dx, y);
    draw_sprite_xpm(digits[seconds / 10], x + 3*dx, y);
    draw_sprite_xpm(digits[seconds % 10], x + 4*dx, y);
    draw_sprite_xpm(digits[seconds / 10], x + 3*dx, y);
    draw_sprite_xpm(digits[seconds % 10], x + 4*dx, y);
}

void draw_chrono_buttons() {
    for (int i = 0; i < 3; i++) {
        draw_sprite_xpm(chrono_buttons[i], chrono_buttons[i]->x, chrono_buttons[i]->y);
    }

}


void draw_mouse() {
    draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
}

int draw_sprite_xpm(Sprite *sprite, int x, int y) {
    if(sprite == NULL){
        printf("Sprite is NULL! (draw_sprite_xpm)\n");
        return 1;
    }
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t current_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        current_color = sprite->colors[w + h*width];
        if (current_color == TRANSPARENT) continue;
        if (draw_pixel(x + w, y + h, current_color, drawing_frame_buffer) != 0) return 1;
      }
    }
    return 0;
}

int draw_sprite_button(Sprite *sprite, int x, int y) {
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color = sprite->pressed ? PRESSED : sprite->color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        if (draw_pixel(x + w, y + h, color, drawing_frame_buffer) != 0) return 1;
      }
    }
    return 0;
}

void display_real_time() {
    
    int dx = 55;
    int x = vbe_info.XResolution / 2 - 5 * dx;
    int y = 50;
    int midX = vbe_info.XResolution / 2;
    int y_date = y + 75;

    // ---- DATA ---- (DIA/MÊS/ANO)
    int year = rtc_date.year;
    int digits_date[8] = {
        rtc_date.day / 10, rtc_date.day % 10,
        rtc_date.month / 10, rtc_date.month % 10,
        (year / 1000) % 10, (year / 100) % 10, (year / 10) % 10, year % 10
    };


    // desenhar dia
    draw_sprite_xpm(digits[digits_date[0]], midX - 6 * dx, y_date);
    draw_sprite_xpm(digits[digits_date[1]], midX - 5 * dx, y_date);
    draw_sprite_xpm(slash, midX - 4 * dx, y_date);

    // desenhar mês
    draw_sprite_xpm(digits[digits_date[2]], midX - 3 * dx, y_date);
    draw_sprite_xpm(digits[digits_date[3]], midX - 2 * dx, y_date);
    draw_sprite_xpm(slash, midX - dx, y_date);

    // desenhar ano completo (YYYY)
    draw_sprite_xpm(digits[digits_date[4]], midX, y_date);
    draw_sprite_xpm(digits[digits_date[5]], midX + dx, y_date);
    draw_sprite_xpm(digits[digits_date[6]], midX + 2 * dx, y_date);
    draw_sprite_xpm(digits[digits_date[7]], midX + 3 * dx, y_date);

    // ---- HORA ---- (HH:MM:SS)
    int digits_time[6] = {
        rtc_time.hours / 10, rtc_time.hours % 10,
        rtc_time.minutes / 10, rtc_time.minutes % 10,
        rtc_time.seconds / 10, rtc_time.seconds % 10
    };

    draw_sprite_xpm(digits[digits_time[0]], x +  dx, y);
    draw_sprite_xpm(digits[digits_time[1]], x + 2 * dx, y);
    draw_sprite_xpm(digits[digits_time[0]], x +  dx, y);
    draw_sprite_xpm(digits[digits_time[1]], x + 2 * dx, y);
    draw_sprite_xpm(colon, x + 3 * dx, y);
    draw_sprite_xpm(digits[digits_time[2]],x + 4 * dx, y);
    draw_sprite_xpm(digits[digits_time[3]],x + 5 * dx, y);
    draw_sprite_xpm(digits[digits_time[2]],x + 4 * dx, y);
    draw_sprite_xpm(digits[digits_time[3]],x + 5 * dx, y);
    draw_sprite_xpm(colon, x + 6 * dx, y);
    draw_sprite_xpm(digits[digits_time[4]], x + 7 * dx, y);
    draw_sprite_xpm(digits[digits_time[5]], x + 8 * dx, y);
    draw_sprite_xpm(digits[digits_time[4]], x + 7 * dx, y);
    draw_sprite_xpm(digits[digits_time[5]], x + 8 * dx, y);
}

void draw_toolbar() {
    for (int i = 0; i < 3; i++) {
        draw_sprite_xpm(toolbar_buttons[i], toolbar_buttons[i]->x, toolbar_buttons[i]->y);
    }
}

void draw_text(const char *text, int x, int y, uint32_t color) {
    for (int i = 0; text[i] != '\0'; i++) {
        for (int dy = 0; dy < 8; dy++) {
            for (int dx = 0; dx < 6; dx++) {
                if ((font8x8_basic[(unsigned char)text[i]][dy] >> dx) & 1) {
                    draw_pixel(x + i * 8 + dx, y + dy, color, drawing_frame_buffer);
                }
            }
        }
    }
}
