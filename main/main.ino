#include <ezButton.h>
#include <Keyboard.h>
#include <ArduinoQueue.h>
#include "pins.h"
#include "btns.h"
#include "keys.h"

struct TimedKey {
  unsigned long time;
  bool press;
  char key;
};

ArduinoQueue<TimedKey> timedKeys(8);
bool toggleStates[NUM_BTNS] = {false};

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #else
    Keyboard.begin();
  #endif
  for (byte i = 0; i < NUM_BTNS; i++) {
    buttons[i].setDebounceTime(10); // TODO: is 10 enough?
  }
}

void loop() {
  unsigned long time = millis();
  for (byte e = 0; e < timedKeys.itemCount(); e++) {
    TimedKey item = timedKeys.getHead();
    if (time >= item.time) {
      if (item.press) {
        #ifdef DEBUG
          Serial.println("SERIES PRESS");
          Serial.println(item.time);
          Serial.println((byte)item.key);
        #else
          Keyboard.press(item.key);
        #endif
      } else {
        #ifdef DEBUG
          Serial.println("SERIES RELEASE");
          Serial.println(item.time);
          Serial.println((byte)item.key);
        #else
          Keyboard.release(item.key);
        #endif
      }
      timedKeys.dequeue();
    }
  }
  for (byte i = 0; i < NUM_BTNS; i++) {
    buttons[i].loop();
  }
  for (byte i = 0; i < NUM_BTNS; i++) {
    if (buttons[i].isPressed()) {
      #ifdef DEBUG
        Serial.println("### BUTTON PRESSED ###");
      #endif
      byte keylen = strlen(keys[i]);
      byte keytype = keys[i][0];
      for (char j = 1; j < keylen; j += 2) {
        char key = keys[i][j];
        byte delay = keys[i][j+1];
        if (keytype == SERIES) {
          if (j <= 1) {
            timedKeys.enqueue({time+(delay*(j-1)), true, key});
          } else {
            timedKeys.enqueue({time+(delay*(j-2)), true, key});
          }
          timedKeys.enqueue({time+(delay*(j)), false, key});
        } else if (keytype == TOGGLE) {
          toggleStates[i] = !toggleStates[i];
          if (toggleStates[i]) {
            #ifdef DEBUG
              Serial.println("TOGGLE PRESS");
              Serial.println((byte)key);
            #else
              Keyboard.press(key);
            #endif
          } else {
            #ifdef DEBUG
              Serial.println("TOGGLE RELEASE");
              Serial.println((byte)key);
            #else
              Keyboard.release(key);
            #endif
          }
        } else if (keytype == MOMENT) {
          #ifdef DEBUG
            Serial.println("MOMENT PRESS");
            Serial.println((byte)key);
          #else
            Keyboard.press(key);
          #endif
        }
      }
    } else if (buttons[i].isReleased()) {
      char keytype = keys[i][0];
      if (keytype == MOMENT) {
        int keylen = strlen(keys[i]);
        for (char j = 1; j < keylen; j++) {
          char key = keys[i][j];
          #ifdef DEBUG
            Serial.println("MOMENT RELEASE");
            Serial.println((byte)key);
          #else
            Keyboard.release(key);
          #endif
        }
      }
    }
  }
}
