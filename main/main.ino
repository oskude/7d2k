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

// TODO: i hope you dont use more than 8 SERIES keys at the same time >.<*
ArduinoQueue<TimedKey> timedKeys(8);
// TODO: i hope you dont have more keys than 8 for a button >.<*
static bool toggleStates[NUM_BTNS][8] = {false};

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
  for (byte i = 1; i < keylen; i += 2) {
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
  byte keylen = strlen(theKeys);
  for (byte i = 1; i < keylen; i++) {
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
  for (byte i = 1; i < keylen; i++) {
    char key = theKeys[i];
    #ifdef DEBUG
      Serial.println("MOMENT PRESS");
      Serial.println((byte)key);
    #else
      Keyboard.press(key);
    #endif
  }
}

void onKeyPressedToggleMoment(char theKeys[], byte btnIdx) {
  byte keylen = (strlen(theKeys) - 1) / 2;
  for (byte i = 1; i <= keylen; i++) {
    byte keytype = theKeys[i*2]; // 1 == TOGGLE, 2 == MOMENT
    char key = theKeys[i+(i-1)];
    if (keytype == 1) {
      toggleStates[btnIdx][i] = !toggleStates[btnIdx][i];
      if (toggleStates[btnIdx][i]) {
        #ifdef DEBUG
          Serial.print("TOGGLE PRESS KEY ");
          Serial.println((byte)key);
        #else
          Keyboard.press(key);
        #endif
      } else {
        #ifdef DEBUG
          Serial.print("TOGGLE RELEASE KEY ");
          Serial.println((byte)key);
        #else
          Keyboard.release(key);
        #endif
      }
    }
    else if (keytype == 2) {
      #ifdef DEBUG
        Serial.print("MOMENT PRESS ");
        Serial.println((byte)key);
      #else
        Keyboard.press(key);
      #endif
    }
  }
}

void onKeyReleasedToggleMoment(char theKeys[]) {
  byte keylen = strlen(theKeys);
  for (byte i = 1; i < keylen; i += 2) {
    byte keytype = theKeys[i+1]; // 1 == TOGGLE, 2 == MOMENT
    char key = theKeys[i];
    if (keytype == 1) {
      #ifdef DEBUG
        Serial.print("MOMENT RELEASE ");
        Serial.println((byte)key);
      #else
        Keyboard.release(key);
      #endif
    }
  }
}

void onKeyReleasedMoment(char theKeys[]) {
  byte keylen = strlen(theKeys);
  for (byte i = 1; i < keylen; i++) {
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
      else if (keytype == MOMENT) {
        onKeyPressedMoment(keys[i]);
      }
      else if (keytype == TOGMOM) {
        onKeyPressedToggleMoment(keys[i], i);
      }
    }
    else if (buttons[i].isReleased()) {
      #ifdef DEBUG
        Serial.println("### BUTTON RELEASED ###");
      #endif
      if (keytype == MOMENT) {
        onKeyReleasedMoment(keys[i]);
      }
      else if (keytype == TOGMOM) {
        onKeyReleasedToggleMoment(keys[i]);
      }
    }
  }
}
