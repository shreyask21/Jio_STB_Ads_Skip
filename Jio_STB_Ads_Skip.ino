// Use the RP2040 core by earlephilhower
// IMPORTANT: Set USB Stack to TinyUSB (Arduino>Tools>USB Stack)
// https://github.com/earlephilhower/arduino-pico 
// DEP 1: https://github.com/jpconstantineau/BlueMicro_HID_Arduino_Library
// DEP 2: https://github.com/jpconstantineau/BlueMicro_RP2040_Arduino_Library

#include <bluemicro_hid.h>

// Settings
#define STB_BOOT_DELAY 32000
#define NUM_KEYPRESS_REPEAT 20

// Alt + Escape = Home Button Shortcut
uint8_t ANDROID_HOME_KEYCODE[6] = { HID_KEY_ALT_LEFT, HID_KEY_ESCAPE, 0, 0, 0, 0};

// For clarity
#define STAGE_PRESS_HOME 0
#define STAGE_VOLUME_DOWN 1
#define STAGE_DO_NOTHING 2

// Local vars
int volume_down_count = 0, home_count = 0; 
uint8_t current_stage = STAGE_PRESS_HOME;
uint32_t lastupdate = 0;


void setup() {
  // Start HID driver and wait for STB to boot
  bluemicro_hid.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(STB_BOOT_DELAY);
}

void loop() {

  // Do changes every 200ms
  if ((millis() - lastupdate) > 200) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    // Check what action needs to be performed
    switch (current_stage) {
      // Spam HOME key 'n' times to skip ad
      case STAGE_PRESS_HOME:
        if (home_count < NUM_KEYPRESS_REPEAT) {
          bluemicro_hid.keyboardReport(0, ANDROID_HOME_KEYCODE);
          bluemicro_hid.keyboardRelease();
          home_count++;
        } else {
          current_stage = STAGE_VOLUME_DOWN;
        }
        break;

      // Spam volume down key 'n' times
      // We cant use mute button as the last state is unknown
      case STAGE_VOLUME_DOWN:
        if (volume_down_count < NUM_KEYPRESS_REPEAT) {
          bluemicro_hid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
          bluemicro_hid.consumerKeyRelease();
          volume_down_count++;
        } else {
          current_stage = STAGE_DO_NOTHING;
        }
        break;

      // Twiddle fingers
      default:
        break;
    }
    lastupdate = millis();
  }

  bluemicro_hid.processQueues(CONNECTION_MODE_AUTO);
}
