#include "model.h"
#include "sprite.h"

// Variáveis externas importantes à construção e manipulação do modelo
SystemState systemState = RUNNING;
MenuState menuState = RUNNING_CLOCK;
ChronoState chronoState = OFF;
ChronoState timerState = OFF;
int chrono_seconds = 0;
int timer_seconds = 0;
int timer_input[6] = {0, 0, 0, 0, 0, 0};
int timer_input_index = 5;

// Objetos a construir e manipular com a mudança de estados
Sprite *mouse;
Sprite *colon;
Sprite *slash;
Sprite *block;
Sprite *days_of_week[7];
Sprite *digits[10];
Sprite *toolbar_buttons[3];
Sprite *chrono_buttons[3];


// Criação dos objetos via XPM e via comum
void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    colon = create_sprite_xpm((xpm_map_t) colon_xpm);
    block = create_sprite_button(50, 70, BLACK);
    slash = create_sprite_xpm((xpm_map_t) slash_xpm);

    digits[0] = create_sprite_xpm((xpm_map_t) digit_0_xpm);
    digits[1] = create_sprite_xpm((xpm_map_t) digit_1_xpm);
    digits[2] = create_sprite_xpm((xpm_map_t) digit_2_xpm);
    digits[3] = create_sprite_xpm((xpm_map_t) digit_3_xpm);
    digits[4] = create_sprite_xpm((xpm_map_t) digit_4_xpm);
    digits[5] = create_sprite_xpm((xpm_map_t) digit_5_xpm);
    digits[6] = create_sprite_xpm((xpm_map_t) digit_6_xpm);
    digits[7] = create_sprite_xpm((xpm_map_t) digit_7_xpm);
    digits[8] = create_sprite_xpm((xpm_map_t) digit_8_xpm);
    digits[9] = create_sprite_xpm((xpm_map_t) digit_9_xpm);

    toolbar_buttons[0] = create_sprite_xpm((xpm_map_t) clock_xpm);
    toolbar_buttons[1] = create_sprite_xpm((xpm_map_t) chrono_xpm);
    toolbar_buttons[2] = create_sprite_xpm((xpm_map_t) timer_xpm);

    toolbar_button_sprites[0] = create_sprite_xpm((xpm_map_t) clock_xpm);
    toolbar_button_sprites[1] = create_sprite_xpm((xpm_map_t) chrono_xpm);
    toolbar_button_sprites[2] = create_sprite_xpm((xpm_map_t) timer_xpm);

    days_of_week[0] = create_sprite_xpm((xpm_map_t) mon_xpm);
    days_of_week[1] = create_sprite_xpm((xpm_map_t) tue_xpm);
    days_of_week[2] = create_sprite_xpm((xpm_map_t) wed_xpm);
    days_of_week[3] = create_sprite_xpm((xpm_map_t) thu_xpm);
    days_of_week[4] = create_sprite_xpm((xpm_map_t) fri_xpm);
    days_of_week[5] = create_sprite_xpm((xpm_map_t) sat_xpm);
    days_of_week[6] = create_sprite_xpm((xpm_map_t) sun_xpm);

    int toolbar_dx = 55;
    int toolbarX = mode_info.XResolution / 4;
    int toolbarY = 4 * mode_info.YResolution / 5;
    for (int i = 0; i < 3; i++) {
        toolbar_buttons[i]->x = (toolbarX + i * toolbarX) - 0.5 * toolbar_dx;
        toolbar_buttons[i]->y = toolbarY;
    }

    chrono_buttons[0] = create_sprite_xpm((xpm_map_t) start_xpm);
    chrono_buttons[1] = create_sprite_xpm((xpm_map_t) pause_xpm);
    chrono_buttons[2] = create_sprite_xpm((xpm_map_t) reset_xpm);

    int chrono_x = mode_info.XResolution / 5;
    int chrono_y = mode_info.YResolution / 2;
    int chrono_dx = 100;

    for (int i = 0; i < 3; i++) {
        chrono_buttons[i]->x = (chrono_x +  2* i * chrono_x) - chrono_dx;
        chrono_buttons[i]->y = chrono_y;
    }
}

// É boa prática antes de acabar o programa libertar a memória alocada
void destroy_sprites() {
    destroy_sprite(mouse);
    destroy_sprite(slash);
    destroy_sprite(colon);

    for (int i = 0; i < 10; i++)
        destroy_sprite(digits[i]);
    
    for (int i = 0; i < 3; i++)
        destroy_sprite(toolbar_buttons[i]);

    for (int i = 0; i < 7; i++)
        destroy_sprite(days_of_week[i]);

}

// Na altura da interrupção há troca dos buffers e incremento do contador
void update_timer_state() {
    timer_ih();

    if (timer_counter % GAME_FREQUENCY == 0) {  // A cada segundo
        if (chronoState == ON) chrono_seconds++;
        
        if (timerState == ON) timer_seconds--;

        if (menuState == RUNNING_CLOCK) rtc_update();
    }

    draw_new_frame();
    if (DOUBLE_BUFFER) swap_buffers();
}


// Sempre que uma nova tecla é pressionada há avaliação do scancode.
// No caso do Template o teclado influencia:
// - o systemState: se Q for pressionado, leva ao fim do programa
// - o menuState: se S, C, T forem pressionados, leva a um dos menus (start, chrono, timer) disponíveis
void update_keyboard_state() {
    (kbc_ih)();

    switch (scancode) {
        case Q_KEY:
            systemState = EXIT;
            break;
        case S_KEY:
            menuState = RUNNING_CLOCK;
            break;
        case C_KEY:
            menuState = CHRONO;
            break;
        case T_KEY:
            menuState = TIMER;
            break;

        default:
            break;
    }


    if (menuState == TIMER) {
        switch (scancode) {
            case ONE_KEY:
            case TWO_KEY:
            case THREE_KEY:
            case FOUR_KEY:
            case FIVE_KEY:
            case SIX_KEY:
            case SEVEN_KEY:
            case EIGHT_KEY:
            case NINE_KEY:
            case ZERO_KEY:
                insert_new_input(scancode);
                break;

            case BACKSPACE_KEY: 
                delete_last_input();
                break;

            default:
                break;
        }
    }
}



void insert_new_input(uint8_t new_input) {
    if (timer_input_index > -1) {  // if it's -1, it's full
        for (int i = 0; i < 5; i++) {
            timer_input[i] = timer_input[i + 1];
        }
        timer_input[5] = new_input;
        timer_input_index++;
    }
}


void delete_last_input() {
    if (timer_input_index != 5) { // if it's 5, it's empty
        for (int i = 5; i >= 0 ; i--) {
            timer_input[i] = timer_input[i - 1];
        }
        timer_input[0] = 0; 
        timer_input_index--;
    }
}


// Sempre que há um novo pacote completo do rato
// - muda o seu estado interno (x, y, left_pressed, right_pressed) - mouse_sync_info();
// - pode mudar o estado do botão por baixo dele - update_buttons_state();
void update_mouse_state() {
    (mouse_ih)();
    mouse_sync();

    if (byte_index == 3) {
        mouse_make_packet();
        byte_index = 0;

        if (menuState == CHRONO)  update_chrono_buttons();
        update_toolbar_buttons();
    } 
    
}

void update_chrono_buttons() {
    if (mouse_info.left_click) {
        if (is_mouse_over_button(chrono_buttons[0]))
            chronoState = ON;

        else if (is_mouse_over_button(chrono_buttons[1]))
            chronoState = OFF; 

        else if (is_mouse_over_button(chrono_buttons[2])) {
            chronoState = OFF;
            chrono_seconds = 0;
        }
    }
}

void update_toolbar_buttons() {
    if (mouse_info.left_click) {
        if (is_mouse_over_button(toolbar_buttons[0])) {
            menuState = RUNNING_CLOCK;
        } else if (is_mouse_over_button(toolbar_buttons[1])) {
            menuState = CHRONO;
        } else if (is_mouse_over_button(toolbar_buttons[2])) {
            menuState = TIMER;
        }
    }
}   



bool is_mouse_over_button(Sprite* button) {
    return (mouse_info.x >= button->x &&
            mouse_info.x <= button->x + button->width &&
            mouse_info.y >= button->y &&
            mouse_info.y <= button->y + button->height);
}

 
