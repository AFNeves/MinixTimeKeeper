#include "model.h"

// Variáveis externas importantes à construção e manipulação do modelo
SystemState systemState = RUNNING;
MenuState menuState = START;
ChronoState chronoState = OFF;
int chrono_seconds = 0;

// Objetos a construir e manipular com a mudança de estados
Sprite *mouse;
Sprite *buttonStart;
Sprite *buttonPause;
Sprite *buttonReset;
Sprite *colon;
Sprite *digit_sprites[10];


// Criação dos objetos via XPM e via comum
void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    colon = create_sprite_xpm((xpm_map_t) colon_xpm);

    digit_sprites[0] = create_sprite_xpm((xpm_map_t) digit_0_xpm);
    digit_sprites[1] = create_sprite_xpm((xpm_map_t) digit_1_xpm);
    digit_sprites[2] = create_sprite_xpm((xpm_map_t) digit_2_xpm);
    digit_sprites[3] = create_sprite_xpm((xpm_map_t) digit_3_xpm);
    digit_sprites[4] = create_sprite_xpm((xpm_map_t) digit_4_xpm);
    digit_sprites[5] = create_sprite_xpm((xpm_map_t) digit_5_xpm);
    digit_sprites[6] = create_sprite_xpm((xpm_map_t) digit_6_xpm);
    digit_sprites[7] = create_sprite_xpm((xpm_map_t) digit_7_xpm);
    digit_sprites[8] = create_sprite_xpm((xpm_map_t) digit_8_xpm);
    digit_sprites[9] = create_sprite_xpm((xpm_map_t) digit_9_xpm);

    buttonStart = create_sprite_button(60, 40, GREEN);
    buttonPause = create_sprite_button(60, 40, YELLOW);
    buttonReset = create_sprite_button(60, 40, RED);

}

// É boa prática antes de acabar o programa libertar a memória alocada
void destroy_sprites() {
    destroy_sprite(mouse);
    destroy_sprite(buttonStart);
    destroy_sprite(buttonPause);
    destroy_sprite(buttonReset);

    for (int i = 0; i < 10; i++)
        destroy_sprite(digit_sprites[i]);
}

// Na altura da interrupção há troca dos buffers e incremento do contador
void update_timer_state() {
    timer_ih();

    if (timer_counter % GAME_FREQUENCY == 0) {  // A cada segundo
        if (chronoState == ON) {
            chrono_seconds++;
        }
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
            menuState = START;
            break;
        case C_KEY:
            menuState = CHRONO;
            break;
        default:
            break;
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
        if (menuState == CHRONO) {
            update_chrono_buttons();
        }
    } 
    
}

void update_chrono_buttons() {
    if (mouse_info.left_click) {
        if (is_mouse_over_button(buttonStart, buttonStart_x, buttonStart_y))
            chronoState = ON;

        else if (is_mouse_over_button(buttonPause, buttonPause_x, buttonPause_y))
            chronoState = OFF; 

        else if (is_mouse_over_button(buttonReset, buttonReset_x, buttonReset_y)) {
            chronoState = OFF;
            chrono_seconds = 0;
        }
    }
}



bool is_mouse_over_button(Sprite* button, int x, int y) {
    return (mouse_info.x >= x &&
            mouse_info.x <= x + button->width &&
            mouse_info.y >= y &&
            mouse_info.y <= y + button->height);
}

 
