#include <Arduino.h>
#include <cstdint>
#include <limits>

#include "hardware/pwm.h"
#include "hardware/adc.h"

#include "PINOUT.h"
#include "CONSTANTS.h"



void pwm_Init(uint8_t pin)
{
    pwm_config config = pwm_get_default_config();
    config.top = TIMER_TOP_VALUE;

    uint8_t pwm_slice = pwm_gpio_to_slice_num(pin);
    uint8_t pwm_channel = pwm_gpio_to_channel(pin);
    pwm_init(pwm_slice, pwm_channel, &config, true);

    // 50% duty cycle to start
    pwm_set_chan_level(pwm_slice, pwm_channel, config.top / 2);
}

void adc_init(uint8_t pin)
{
  if(pin > 29 || pin < 26){
    return;
  }
  uint8_t adc_channel = pin - 26;
  adc_gpio_init(pin);
  adc_select_input(adc_channel);
  adc_fifo_setup(true, false, 1, false, false);
  adc_run(true);
}

void setup() {
  // set up the pwm pin
  gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
  pwm_Init(PWM_PIN);
  adc_init(AUDIO_IN_PIN);
}

void loop() {
  // steps:
  if(adc_fifo_get_level() > 0){
    // 1. Read the audio signal from the input
    uint16_t input_level = adc_fifo_get();
    // 2. Calculate the corresponding output amplitude
    uint16_t output_level = map(input_level, 0, std::numeric_limits<uint16_t>::max(), 0, TIMER_TOP_VALUE);
    // 3. Write the output amplitude to the PWM signal
    pwm_set_gpio_level(PWM_PIN, output_level);
  }
  // 4. Repeat
}