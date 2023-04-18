enum KeyType {
  NO_ZERO, // we dont want zero cause strings are terminated with 0?
  MOMENT, // press: press. release: release
  SERIES, // press: press and release after milliseconds
  TOGGLE, // press: press or release
  TOGMOM  // TOGGLE (1) or MOMENT (2) keys
};
KeyType keyType;

/* examples
{MOMENT, 'w'} // press 'w' on key press, release 'w' on key release
{MOMENT, KEY_LEFT_SHIFT, e} // press SHIFT and 'e' on key press, release both on key release
{SERIES, 'w', 25, 'e', 25} // press 'w' on key press, release 'w' after 25ms and press 'e' and release 'e' after 25ms
{TOGGLE, 'w'} // press 'w' on key press, release 'w' on key press
{TOGGLE, 'w', 'e'} // press 'w' and 'e' on key press, release both on key press
{TOGMOM, 'w', 1, 'e', 2} // press 'w' and 'e' on key press, release 'w' and press 'e' on key press...
*/

// NOTE: last array size needs to be at least the size of longest entry + 1
static char keys[][3] {
  // thumb
  /* T1 */ {MOMENT, 'g'},
  /* T2 */ {MOMENT, ' '},
  /* T3 */ {MOMENT, 'b'},
  // index finger
  /* I1 */ {MOMENT, 'c'},
  /* I2 */ {MOMENT, 'd'},
  /* I3 */ {MOMENT, 'e'},
  /* I4 */ {MOMENT, 'v'},
  /* I5 */ {MOMENT, 'f'},
  /* I6 */ {MOMENT, 'r'},
  // middle finger
  /* M1 */ {MOMENT, 'x'},
  /* M2 */ {MOMENT, 's'},
  /* M3 */ {MOMENT, 'w'},
  // ring finger
  /* R1 */ {MOMENT, 'y'},
  /* R2 */ {MOMENT, 'a'},
  /* R3 */ {MOMENT, 'q'},
  // pinky
  /* P1 */ {MOMENT, KEY_LEFT_CTRL},
  /* P2 */ {MOMENT, KEY_LEFT_SHIFT},
  /* P3 */ {TOGGLE, 'w'}
};
