# 7D2K

Arduino ["WASD"](https://en.wikipedia.org/wiki/Arrow_keys#WASD_keys) keyboard with macros.

## Dependencies

- [ezButton](https://www.arduinolibraries.info/libraries/ez-button)
- [Keyboard](https://www.arduinolibraries.info/libraries/keyboard) (check for [compatibility](https://www.arduino.cc/reference/en/libraries/keyboard/))
- [ArduinoQueue](https://www.arduinolibraries.info/libraries/arduino-queue)

## Usage

1. Wire your buttons (one button per pin)
1. Modify [main/pins.h](main/pins.h) to what you wired
1. Modify [main/btns.h](main/btns.h) if you added/removed pins
1. Modify [main/keys.h](main/keys.h) to what you want to send (see [this](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/) for special keys)

> DEV TIP: add `#define DEBUG` to [`main.ino`](main/main.ino) and the code does not send keyboard keys, but instead prints debug info over serial. (listen with eg. `minicom -b 9600 -o -D /dev/ttyACM0`)

## Prototype 2 : Laser Cut Case

![proto2](proto2front.jpg?raw=true "front photo of prototype 2")

![proto2](proto2back.jpg?raw=true "back photo of prototype 2")

```
          ┌────┐┌────┐┌────┐┌────┐
          │ R3 ││ M3 ││ I3 ││ I6 │
          └────┘└────┘└────┘└────┘
┌────┐    ┌────┐┌────┐┌────┐┌────┐
│ P3 │    │ R2 ││ M2 ││ I2 ││ I5 │
└────┘    └────┘└────┘└────┘└────┘
  ┌────┐  ┌────┐┌────┐┌────┐┌────┐
  │ P2 │  │ R1 ││ M1 ││ I1 ││ I4 │
  └────┘  └────┘└────┘└────┘└────┘
    ┌────┐                  ┌────┐
    │ P1 │                  │ T1 │┌────┐
    └────┘                  └────┘│ T2 │┌────┐
                                  └────┘│ T3 │
                                        └────┘
```

Todo
- Move pinky and thumb keys slight to the left
- Add esc key
- T2 has to be a bigger key? (jump)
- Would horizontal keys for pinky be better?

### Parts

If you want to build this 1:1, you need

- (Propably same size hand as i. 9.5cm middle finger)
- Some old (1988) Apple keyboard keys (16 x 12.8mm)
- Arduino Micro (optionally another one for easier upload)
- 1 x A4 sheet of 4mm material your laser can cut
- LightBurn software (or something else)
- 54 x Dupont plugs (or you solder the cables)
- 54 x Heat shrink tube (or something else)
- Some amount of cable
- Wood glue

### Build

1. Possibly adapt [prototype2/keyboard.FCStd](prototype2/keyboard.FCStd) with [FreeCAD](https://www.freecad.org/)
2. Print [prototype2/keyboard.lbrn2](prototype2/keyboard.lbrn2) with [LightBurn](https://lightburnsoftware.com/) (or import your exported SVG from FreeCAD)
3. Glue the laser cut parts together
4. Add Arduino Micro, buttons and wire them

## Prototype 1 : Breadboard

![proto1](proto1.jpg?raw=true "front photo of prototype 1 (some keys already taken for prototype 2)")

```
    ┌────┐┌────┐┌────┐┌────┐┌────┐
    │ R4 ││ R2 ││ M2 ││ I2 ││ I4 │
    └────┘└────┘└────┘└────┘└────┘
    ┌────┐┌────┐┌────┐┌────┐┌────┐
    │ R3 ││ R1 ││ M1 ││ I1 ││ I3 │
    └────┘└────┘└────┘└────┘└────┘
┌────┐┌────┐
│ P1 ││ P2 │
└────┘└────┘
                         ┌────┐┌────┐
                         │ T2 ││ T1 │
                         └────┘└────┘
```
