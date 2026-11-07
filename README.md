# C3 Finder Tag

![build](https://github.com/Salmon10k/Esp-C3_Finder_Tag/actions/workflows/build.yml/badge.svg)

<!--
WRITE (after phase 1): one sentence that says WHAT it is and WHY it's interesting.
Good:  "A coin-cell-sized BLE finder tag built on an ESP32-C3 Super Mini, with
        measured battery life and an open-source Find Hub / Find My bridge."
Replace OWNER/REPO in the badge URL above with your GitHub user/repo.
-->

TODO: one-line pitch.

![photo of the build](docs/img/build.jpg)

<!--
WRITE (after phase 3): add a real photo. A phone picture on a plain background
is enough. Save it as docs/img/build.jpg. This is the first thing people see.
-->

## Why I built this

<!--
WRITE (3-4 sentences, first person): what made you want to build it, what you
wanted to learn (BLE, low-power firmware, battery hardware), what you expected
to be hard. Honest > impressive.
-->

TODO

## Status

- [ ] Phase 1: BLE beacon, seen in nRF Connect
- [ ] Phase 2: deep-sleep burst mode, current measured
- [ ] Phase 3: battery + charging hardware, power LED removed
- [ ] Phase 4: Find Hub / Find My integration
- [ ] Phase 5: case, discharge plot, polish

## Hardware

<!--
WRITE (after phase 3): 4-6 lines. Board, battery, charger, divider. Link to
hardware/README.md for wiring and the BOM. Mention the battery safety notes.
-->

TODO. See [hardware/](hardware/).

## How it works

<!--
WRITE (after phase 2): a short diagram (even ASCII) + 1 paragraph:
wake -> read battery -> advertise burst -> deep sleep -> repeat.
Explain the payload layout (battery mV + sequence) in a small table.
Explain WHY bursts instead of continuous advertising.
-->

TODO

## Build and flash

```bash
pip install platformio
cd firmware
pio run -e debug -t upload      # bench build, USB serial logs
pio device monitor
pio run -e battery -t upload    # field build, deep sleep
```

## Power results

<!--
WRITE (after phase 2/3): fill this table with MEASURED numbers from
docs/01-power-measurement.md. Real numbers are the best part of this repo.
Embed docs/img/discharge.png once you have a full discharge test.
-->

| Config | Sleep current | Avg current | Est. runtime (800 mAh) | Measured runtime |
|---|---|---|---|---|
| TODO | | | | |

## Limitations

<!--
WRITE (honestly): what does NOT work or is not proven.
Examples: not an official AirTag, no UWB precision finding, battery life
numbers are for one board and one cell, Find network coverage depends on
nearby phones, project X may break if the vendor changes their protocol.
-->

TODO

## Responsible use

This is for finding **your own** belongings. Do not use it to track people or
property that isn't yours. Phones will alert people to unknown trackers, and
tracking someone without consent is illegal in many places.

## Credits

<!--
WRITE (phase 4): link every project/paper you build on, e.g. OpenHaystack and
whichever Find Hub project you use. See docs/02-find-network.md.
-->

TODO

## License

MIT, see [LICENSE](LICENSE).
