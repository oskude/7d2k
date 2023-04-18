// prototype 2 keys for planetside2
// TODO: need moar buttons...

enum KeyType {
  NO_ZERO,
  MOMENT,
  SERIES,
  TOGGLE,
  TOGMOM
};
KeyType keyType;

byte del = 25;

// TODO: game bug or feature, "aim" uses your tool! (eg. repair tool)
/* other keys
p == change vehicle camera
*/

static char keys[][6] {
  // thumb
  /* T1 */ {MOMENT, 'q'},
  /* T2 */ {MOMENT, ' '},
  /* T3 */ {MOMENT, 'b', 'f'},
  // index finger
  /* I1 */ {MOMENT, '1'},
  /* I2 */ {MOMENT, 'd'},
  /* I3 */ {SERIES, 'e', del, 't', del}, // interact and toggle ui
  /* I4 */ {MOMENT, '4'},
  /* I5 */ {MOMENT, 'r'}, // reload
  /* I6 */ {MOMENT, 'e'}, // use things that dont need ui
  // middle finger
  /* M1 */ {MOMENT, '2'},
  /* M2 */ {MOMENT, 's'},
  /* M3 */ {MOMENT, 'w'},
  // ring finger
  /* R1 */ {MOMENT, '3'},
  /* R2 */ {MOMENT, 'a'},
  /* R3 */ {MOMENT, 'l'},
  // pinky
  /* P1 */ {MOMENT, KEY_LEFT_CTRL},
  /* P2 */ {MOMENT, KEY_LEFT_SHIFT},
  /* P3 */ {MOMENT, KEY_ESC, 't'}, // esc and toggle ui
};
