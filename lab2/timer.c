#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer < 0 || timer > 2 || freq < 19 || freq > TIMER_FREQ) return 1;

  uint16_t newFreq = TIMER_FREQ / freq;
  uint8_t control_word, lsb, msb;

  util_get_LSB(newFreq, &lsb);
  util_get_MSB(newFreq, &msb);

  if(timer_get_conf(timer, &control_word) != 0) return 1;
  control_word = control_word & 0xF;
  control_word = TIMER_LSB_MSB;

  switch(timer){
    case 0:
      control_word |= TIMER_SEL0;
      break;
    case 1:
      control_word |= TIMER_SEL1;
      break;
    case 2:
      control_word |= TIMER_SEL2;
      break;
    default:
      break;
  }

  if(sys_outb(TIMER_CTRL, control_word) != 0) return 1;
  if(sys_outb(TIMER_0 + timer, lsb) != 0) return 1;
  if(sys_outb(TIMER_0 + timer, msb) != 0) return 1;

    
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *config) {
  if(timer < 0 || timer > 2 || config == NULL) return 1;

  uint8_t rbc = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer); 
  if(sys_outb(TIMER_CTRL, rbc) != 0) return 1;
  if(util_sys_inb(TIMER_0 + timer, config) != 0) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t config,
                        enum timer_status_field field) {
  
  union timer_status_field_val data;

  switch(field){
    case tsf_all:
      data.byte = config;
      break;

    case tsf_initial:
      config = (config >> 4) & 0x03;

      if(config == 1) data.in_mode = LSB_only;
      else if(config == 2) data.in_mode = MSB_only;
      else if(config == 3) data.in_mode = MSB_after_LSB;
      else data.in_mode = INVAL_val;

      break;

    case tsf_mode:
      config = (config >> 1) & 0x07;

      if(config == 6) data.count_mode = 2;
      else if(config == 7) data.count_mode = 3;
      else data.count_mode = config;
      
      break;

    case tsf_base:
      data.bcd = config & TIMER_BCD;
      break;

    default:
      return 1;
  }

  if(timer_print_config(timer, field, data) != 0) return 1;

  return 0;
}