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

void onKeyPressedSeries(char theKeys[], unsigned long time) {
  byte keylen = strlen(theKeys);
  for (char i = 1; i < keylen; i += 2) {
    char key = theKeys[i];
    byte delay = theKeys[i+1];
    if (i <= 1) {
      timedKeys.enqueue({time+(delay*(i-1)), true, key});
    } else {
      timedKeys.enqueue({time+(delay*(i-2)), true, key});
    }
    timedKeys.enqueue({time+(delay*(i)), false, key});
  }
}

void onKeyPressedToggle(char theKeys[], byte btnIdx) {
  // TODO: i hope you dont have more keys than 8 >.<*
  static bool toggleStates[NUM_BTNS][8] = {false};
  byte keylen = strlen(theKeys);
  for (char i = 1; i < keylen; i++) {
    char key = theKeys[i];
    toggleStates[btnIdx][i] = !toggleStates[btnIdx][i];
    if (toggleStates[btnIdx][i]) {
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
  }
}

void onKeyPressedMoment(char theKeys[]) {
  byte keylen = strlen(theKeys);
  for (char i = 1; i < keylen; i++) {
    char key = theKeys[i];
    #ifdef DEBUG
      Serial.println("MOMENT PRESS");
      Serial.println((byte)key);
    #else
      Keyboard.press(key);
    #endif
  }
}

void onKeyReleasedMoment(char theKeys[]) {
  byte keylen = strlen(theKeys);
  for (char i = 1; i < keylen; i++) {
    char key = theKeys[i];
    #ifdef DEBUG
      Serial.println("MOMENT RELEASE");
      Serial.println((byte)key);
    #else
      Keyboard.release(key);
    #endif
  }
}

void handleTimedKeys (unsigned long time) {
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
}

void loop() {
  unsigned long time = millis();
  handleTimedKeys(time);

  /* TODO: do we need this? or is it ok in loop below
  for (byte i = 0; i < NUM_BTNS; i++) {
    buttons[i].loop();
  }
  */

  for (byte i = 0; i < NUM_BTNS; i++) {
    buttons[i].loop();
    byte keytype = keys[i][0];
    if (buttons[i].isPressed()) {
      #ifdef DEBUG
        Serial.println("### BUTTON PRESSED ###");
      #endif
      if (keytype == SERIES) {
        onKeyPressedSeries(keys[i], time);
      }
      else if (keytype == TOGGLE) {
        onKeyPressedToggle(keys[i], i);
      }
      else if (keytype = MOMENT) {
        onKeyPressedMoment(keys[i]);
      }
    }
    else if (buttons[i].isReleased()) {
      #ifdef DEBUG
        Serial.println("### BUTTON RELEASED ###");
      #endif
      if (keytype == MOMENT) {
        onKeyReleasedMoment(keys[i]);
      }
    }
  }
}
