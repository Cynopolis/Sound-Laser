#include <Arduino.h>
#include <cstdint>
#include <limits>

#include "PINOUT.h"
#include "CONSTANTS.h"

#include "USB_STREAM.h"

USB_STREAM usbAudio{};

void pwm_Init(uint8_t pin)
{
}

void setup() {
  Serial.begin(115200);
  delay(2000); // wait for serial monitor to open

  Serial.println("Beginning setup");

  // set up the pwm pin
  pwm_Init(PWM_PIN);

  Serial.println("Setup complete");
}

void loop() {
  // steps:
  // 1. Read the audio signal from the input
  // 2. Calculate the corresponding output amplitude
  // 3. Write the output amplitude to the PWM signal
  // 4. Repeat
}