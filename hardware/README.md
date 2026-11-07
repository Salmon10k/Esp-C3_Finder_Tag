# Hardware

Read the safety notes before you connect a LiPo. Verify everything against your
own board with a multimeter; Super Mini clones differ.

## Wiring (simple version)

```
                      +--------------+
 USB-C (charging) --> |  TP4056      |  B+ / B-
                      |  module with | <------------> LiPo 800 mAh (protected cell)
                      |  protection  |
                      +--+--------+--+
                      OUT+        OUT-
                       |            |
                   [slide switch]   |
                       |            |
                       +--+---------+----------------> Super Mini GND
                       |  |
                       |  +--> Super Mini 5V pin
                       |
                       +--[ R1 470k ]--+--> GPIO3 (battery sense)
                                       |
                                       +--[ C 100 nF ]--> GND
                                       |
                                       +--[ R2 470k ]---> GND
```

The divider halves the battery voltage into the ADC range; firmware multiplies
it back (`BATT_DIVIDER_RATIO = 2.0`). The 100 nF cap steadies the reading
because the resistors are high value.

## Safety notes (please read)

- **Do not plug the Super Mini into USB while the battery switch is ON.** On most Super Mini boards the 5V pin is tied to USB VBUS. A host feeding 5V into the same node as the battery can push current toward the cell. Switch the battery OFF when flashing. (A diode could prevent this, but it costs battery voltage you can't spare; verify on your board before relying on one.)
- Use a **protected** cell, or a TP4056 module that has the protection chip (the version with an extra DW01-type IC). Check polarity on the battery connector yourself; unmarked cells and mismatched JST wiring are a common way to kill a board.
- A stock TP4056 module charges at about 1 A, which is too high for an 800 mAh cell. Replace its programming resistor to bring the charge current to roughly 0.5C or lower (about 400 mA). Charge current is about `1200 / R(kOhm)` amps, so around 3 kOhm. Check the datasheet for your module.
- Charge where you can watch it, never on a flammable surface, and stop using any cell that swells, gets hot, or has been punctured.
- A fully charged LiPo (4.2 V) is above the ESP32-C3's 3.6 V maximum. **Do not connect the cell straight to the 3V3 pin.** Go through the board regulator via the 5V pin, or through a low-quiescent-current external regulator.

## Power mods (for runtime)

1. **Remove the power LED** (the always-on one). Desolder it or cut the trace. On many boards it draws more current than the whole chip does in deep sleep. The user LED on GPIO8 is separate and stays off unless you drive it.
2. Check the onboard regulator's quiescent current in its datasheet. If it dominates, a low-Iq regulator is the next upgrade, but it means modifying the board; start without it.
3. The divider leaks current all the time (about `Vbat / 940k`, a few µA at 4.2 V). Fine to start with. Later you can power it only during the ADC read (switch it with a GPIO and a small MOSFET) if the numbers show it matters.

## Pins used

| Pin | Use |
|---|---|
| 5V | Battery+ after the switch |
| GND | Battery- |
| GPIO3 | Battery sense (ADC1) |
| GPIO9 | BOOT button (hold during RESET for download mode) |

## What to add here (you write)

- A photo of the finished wiring
- Which exact Super Mini and TP4056 modules you got
- Anything that surprised you (LED current, voltage readings, a board that behaved differently)
