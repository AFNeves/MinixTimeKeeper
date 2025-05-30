#include "view.h"

// Variáveis externas importantes à visualização do modelo e dos seus estados
uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;

// Mouse Information
extern MouseInfo mouse_info;

// Graphical Information
extern vbe_mode_info_t vbe_info;

// RTC Data Structures
extern time_struct rtc_time;
extern date_struct rtc_date;

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
            draw_timer_menu();
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
    draw_sprite_xpm(colon, x + 2 * dx, y);
    draw_sprite_xpm(digits[seconds / 10], x + 3*dx, y);
    draw_sprite_xpm(digits[seconds % 10], x + 4*dx, y);
}


void draw_chrono_buttons() {
    int spacing = 80; 
    int total_width = 3 * chrono_buttons[0]->width + 2 * spacing;
    int start_x = vbe_info.XResolution / 2 - total_width / 2;
    int y = 250;

    for (int i = 0; i < 3; i++) {
        int x = start_x + i * (chrono_buttons[i]->width + spacing);
        draw_sprite_xpm(chrono_buttons[i], x, y);
        chrono_buttons[i]->x = x; 
        chrono_buttons[i]->y = y;
    }
}




void draw_timer_menu() {
    draw_rectangle(0, 0, vbe_info.XResolution, vbe_info.YResolution, ORANGE, drawing_frame_buffer);
    draw_chrono_buttons();

    if (timerState == OFF) {
        if (timer_input_length > 0) draw_timer_input();
        else draw_blocks();

    }   
    

}




void draw_blocks() {
    int dx = 55;
    int x = vbe_info.XResolution / 2 - 4 * dx;
    int y = 50;

    for (int i = 0; i < 8; i++) {
        if (i == 2 || i == 5)  draw_sprite_xpm(colon, x + i * dx, y);
        else  draw_sprite_button(block, x + i * dx, y);
    }
}


void draw_timer_input() {
    int dx = 55;
    int x = vbe_info.XResolution / 2 - 4 * dx;
    int y = 50;

    for (int i = 0; i < 8 ; i++) {
        int j = i;
        if (i > 2) j = i - 1;
        if (i > 5) j = i - 2;
        
        if (i == 2 || i == 5)  draw_sprite_xpm(colon, x + i * dx, y);
        else  draw_sprite_xpm(digits[timer_input[j - 1]], x + i * dx, y);
    }

}   




void draw_mouse() {
    draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
}




void display_real_time() {
    
    int dx = 55;
    int x = vbe_info.XResolution / 2 - 4 * dx;
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
    
    draw_sprite_xpm(digits[digits_time[0]], x , y);
    draw_sprite_xpm(digits[digits_time[1]], x +  dx, y);
    draw_sprite_xpm(colon, x + 2 * dx, y);
    draw_sprite_xpm(digits[digits_time[2]],x + 3 * dx, y);
    draw_sprite_xpm(digits[digits_time[3]],x + 4 * dx, y);
    draw_sprite_xpm(colon, x + 5 * dx, y);
    draw_sprite_xpm(digits[digits_time[4]], x + 6 * dx, y);
    draw_sprite_xpm(digits[digits_time[5]], x + 7 * dx, y);

    // ---- DIA DA SEMANA ----
    int day_index = (rtc_date.dayNumber + 6) % 7;
    int x_day = x - days_of_week[day_index]->width - 20;
    int y_day = y + 20; 

    draw_sprite_xpm(days_of_week[day_index], x_day, y_day - 10);

}




void draw_toolbar() {
    for (int i = 0; i < 3; i++) {
        draw_sprite_xpm(toolbar_buttons[i], toolbar_buttons[i]->x, toolbar_buttons[i]->y);
    }
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


