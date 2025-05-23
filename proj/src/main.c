#include <lcom/lcf.h>
#include "controller/mouse/i8042.h"
#include "controller/timer/timer.h"
#include "controller/keyboard/keyboard.h"
#include "controller/mouse/mouse.h"
#include "controller/video/graphic.h"
#include "controller/rtc/rtc.h"
#include "model/model.h"
#include "view/view.h"
#include "config.h"

extern SystemState systemState;

int (main)(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/proj/src/debug/trace.txt");

    lcf_log_output("/home/lcom/labs/proj/src/debug/output.txt");
    
    if (lcf_start(argc, argv))
        return 1;

    lcf_cleanup();

    return 0;
}

int setup(uint8_t *irq_set_timer, uint8_t *irq_set_keyboard, uint8_t *irq_set_mouse, uint8_t *irq_set_rtc) {

  // Atualização da frequência
  if (timer_set_frequency(TIMER_0, GAME_FREQUENCY) != 0) return 1;

  // Inicialização dos buffers de vídeo (double buffering)
  if (set_frame_buffers(VIDEO_MODE) != 0) return 1;

  // Inicialização do modo gráfico
  if (set_graphic_mode(VIDEO_MODE) != 0) return 1;

  // Inicialização dos sprites
  setup_sprites();

  // Ativação das interrupções dos dispositivos
  if (timer_subscribe_int(irq_set_timer) != 0) return 1;
  if (keyboard_subscribe_int(irq_set_keyboard) != 0) return 1;
  if (mouse_subscribe_int(irq_set_mouse) != 0) return 1;
  if (rtc_subscribe_int(irq_set_rtc) != 0) return 1;

  // Ativar stream-mode e report de dados do rato
  if (mouse_write_command(MOUSE_DATA_STREAM_MODE) != 0) return 1;
  if (mouse_write_command(MOUSE_DATA_REPORT_ENABLE) != 0) return 1;

  // Setup do Real Time Clock
  rtc_start();

  return 0;
}

int teardown() {

  // Volta ao modo de texto
  if (vg_exit() != 0) return 1;

  // Destruição dos sprites
  destroy_sprites();

  // Desativa todas as interrupções
  if (timer_unsubscribe_int() != 0) return 1;
  if (keyboard_unsubscribe_int() != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;
  if (rtc_unsubscribe_int() != 0) return 1;

  // Desativar o report de dados do rato
  if (mouse_write_command(MOUSE_DATA_REPORT_DISABLE) != 0) return 1;

  return 0;
}

int (proj_main_loop)(int argc, char *argv[]) {
 
  uint8_t irq_set_timer, irq_set_keyboard, irq_set_mouse, irq_set_rtc;

  // Setup do Minix
  if (setup(&irq_set_timer, &irq_set_keyboard, &irq_set_mouse, &irq_set_rtc) != 0) return teardown();

  // Desenha a primeira frame
  draw_new_frame();

  // Tratamento das interrupções
  int ipc_status;
  message msg;


  while (systemState == RUNNING) {
    
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set_timer)    update_timer_state();
          if (msg.m_notify.interrupts & irq_set_keyboard) update_keyboard_state();
          if (msg.m_notify.interrupts & irq_set_mouse)    update_mouse_state();
          if (msg.m_notify.interrupts & irq_set_rtc)      update_rtc_state();
        }
    }
  }
  
  // Tear-down do Minix
  if (teardown() != 0) return 1;

  return 0;
}
