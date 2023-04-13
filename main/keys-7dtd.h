// prototype 2 keys for 7 days to die

enum KeyType {
  SO_UMM_DUNNO,
  MOMENT,
  SERIES,
  TOGGLE
};
KeyType keyType;

byte del = 20;

static char keys[][8] {
  // thumb
  /* T1 */ {SERIES, KEY_F7, del, 'g', del}, // inventory
  /* T2 */ {MOMENT, ' '}, // jump
  /* T3 */ {SERIES, KEY_ESC, del, KEY_F7, del}, // escape and hide ui
  // index finger
  /* I1 */ {MOMENT, 'c'},
  /* I2 */ {MOMENT, 'd'},
  /* I3 */ {SERIES, KEY_F7, del, 'e', del}, // open container
  /* I4 */ {MOMENT, 'v'},
  /* I5 */ {SERIES, KEY_F7, del, 'r', del}, // TODO: upstream has to split "reload/takeall"
  /* I6 */ {MOMENT, 'f'},
  // middle finger
  /* M1 */ {MOMENT, 'x'},
  /* M2 */ {MOMENT, 's'},
  /* M3 */ {MOMENT, 'w'},
  // ring finger
  /* R1 */ {MOMENT, 'y'},
  /* R2 */ {MOMENT, 'a'},
  /* R3 */ {SERIES, KEY_F7, del, 'e', del, KEY_F7, del}, // open doors, use bike
  // pinky
  /* P1 */ {MOMENT, KEY_LEFT_CTRL},
  /* P2 */ {MOMENT, KEY_LEFT_SHIFT},
  /* P3 */ {TOGGLE, 'w'} // toggle on press (for auto walk)
};
