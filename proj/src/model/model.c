#include "model.h"
#include "../view/view.h"

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;
extern real_time_info time_info;
int prev_mouse_x = -1, prev_mouse_y = -1;

// Objetos a construir e manipular com a mudança de estados
Sprite *mouse;
Sprite *button1;
Sprite *button2;
Sprite *button3;
Sprite *button4;
Sprite *digit_sprites[10];
Sprite *colon_sprite;

// Contador de interrupções do timer
int timer_interrupts = 0;

// Criação dos objetos via XPM e via comum
void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    //hand = create_sprite_xpm((xpm_map_t) hand_xpm);
    //smile = create_sprite_xpm((xpm_map_t) smile_xpm);
    button1 = create_sprite_button(mode_info.XResolution/2, mode_info.YResolution/2, ORANGE);
    button2 = create_sprite_button(mode_info.XResolution/2, mode_info.YResolution/2, BLUE);
    button3 = create_sprite_button(mode_info.XResolution/2, mode_info.YResolution/2, GREEN);
    button4 = create_sprite_button(mode_info.XResolution/2, mode_info.YResolution/2, YELLOW);

        printf("Loading digit 0\n");
        digit_sprites[0] = create_sprite_xpm((xpm_map_t) digit_0_xpm);
        if (!digit_sprites[0]) printf("Failed to load digit 0\n");

        printf("Loading digit 1\n");
        digit_sprites[1] = create_sprite_xpm((xpm_map_t) digit_1_xpm);
        if (!digit_sprites[1]) printf("Failed to load digit 1\n");

        digit_sprites[2] = create_sprite_xpm((xpm_map_t) digit_2_xpm);
        digit_sprites[3] = create_sprite_xpm((xpm_map_t) digit_3_xpm);
        digit_sprites[4] = create_sprite_xpm((xpm_map_t) digit_4_xpm);
        digit_sprites[5] = create_sprite_xpm((xpm_map_t) digit_5_xpm);
        digit_sprites[6] = create_sprite_xpm((xpm_map_t) digit_6_xpm);
        digit_sprites[7] = create_sprite_xpm((xpm_map_t) digit_7_xpm);
        digit_sprites[8] = create_sprite_xpm((xpm_map_t) digit_8_xpm);
        digit_sprites[9] = create_sprite_xpm((xpm_map_t) digit_9_xpm);
        colon_sprite = create_sprite_xpm((xpm_map_t) colon_xpm);
}

// É boa prática antes de acabar o programa libertar a memória alocada
void destroy_sprites() {
    destroy_sprite(mouse);
    destroy_sprite(button1);
    destroy_sprite(button2);
    destroy_sprite(button3);
    destroy_sprite(button4);

    for (int i = 0; i < 10; i++)
        destroy_sprite(digit_sprites[i]);
    destroy_sprite(colon_sprite);
}

// Na altura da interrupção há troca dos buffers e incremento do contador
void update_timer_state() {
    timer_interrupts++;

    // Apenas a cada segundo (ou seja, 60 vezes por segundo -> 1 vez por segundo)
    if (timer_interrupts % GAME_FREQUENCY == 0) {
        rtc_update();        
        draw_new_frame();     
    }

    if (DOUBLE_BUFFER) swap_buffers();
}

// Como o Real Time Clock é um módulo mais pesado, 
// devemos só atualizar os valores quando passa um segundo
void update_rtc_state() {
    if (timer_interrupts % GAME_FREQUENCY == 0) {
        rtc_update();
    }
}

// Sempre que uma nova tecla é pressionada há avaliação do scancode.
// No caso do Template o teclado influencia:
// - o systemState: se Q for pressionado, leva ao fim do programa
// - o menuState: se S, G, E forem pressionados, leva a um dos menus (start, game, end) disponíveis
void update_keyboard_state() {
    (kbc_ih)();
    switch (scancode) {
        case Q_KEY:
            systemState = EXIT;
            break;
        case S_KEY:
            menuState = START;
            break;
        case G_KEY:
            menuState = GAME;
            break;
        case E_KEY:
            menuState = END;
        default:
            break;
    }
    draw_new_frame();
}

// Sempre que há um novo pacote completo do rato
// - muda o seu estado interno (x, y, left_pressed, right_pressed) - mouse_sync_info();
// - pode mudar o estado do botão por baixo dele - update_buttons_state();
void update_mouse_state() {
    (mouse_ih)();
    mouse_sync();

    if (byte_index == 3) {
        mouse_make_packet();
        update_buttons_state();

        draw_new_frame();
        if (DOUBLE_BUFFER) swap_buffers();
        byte_index = 0;
    }
}

// Se o rato tiver o botão esquerdo pressionado (mouse_info.left_click) então
// muda o estado do botão no mesmo quadrante
// Senão, todos os botões voltam a não estar pressionados (buttonX->pressed = 0;)
void update_buttons_state() {

    if (mouse_info.left_click) {

        if (mouse_info.x < mode_info.XResolution/2 && mouse_info.y < mode_info.YResolution/2)
            button1->pressed = 1;

        if (mouse_info.x >= mode_info.XResolution/2 && mouse_info.y <= mode_info.YResolution/2)
            button2->pressed = 1;

        if (mouse_info.x < mode_info.XResolution/2 && mouse_info.y >= mode_info.YResolution/2)
            button3->pressed = 1;

        if (mouse_info.x >= mode_info.XResolution/2 && mouse_info.y > mode_info.YResolution/2)
            button4->pressed = 1;

    } else {
        button1->pressed = 0;
        button2->pressed = 0;
        button3->pressed = 0;
        button4->pressed = 0;
    }
}
