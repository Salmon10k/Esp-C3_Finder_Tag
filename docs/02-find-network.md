# Phase 4: connecting to a Find network

This phase is research first, coding second. These networks are run by Apple and
Google, the protocols are not designed for hobby hardware, and the open-source
projects that work around that can break whenever the vendor changes something.
I have not verified the current state of any of them for you.

## Candidates to look at

- **Google Find Hub (Find My Device network).** A search turns up
  `leonboe1/GoogleFindMyTools`, which was covered in 2025 (CNX Software,
  Hackster) as a way to use an ESP32 as a Find Hub tag. Check it yourself.
- **Apple Find My via OpenHaystack.** A research project from TU Darmstadt
  (SEEMOO) with an ESP32 firmware folder in its repo. Apple has changed things
  since release, so check the issues before investing time.

## Research checklist (record the answers below)

For each project, write down:

- [ ] Last commit date and whether recent issues get answers
- [ ] Does it support **ESP32-C3** (not just the original ESP32)? Which BLE stack does it use (NimBLE / Bluedroid)?
- [ ] What setup does it need (Google/Apple account, key generation, a Mac or Python tool)?
- [ ] How are keys stored on the device, and what happens if you lose them?
- [ ] Reported location accuracy and update delay
- [ ] Any rules you must follow (terms of service, anti-stalking behaviour)

## Integration plan

1. Get the project's **own** example running on its own terms first, on any supported ESP32 if the C3 isn't supported.
2. Read how it builds the advertisement packet. Find the part of `startAdvertising()` in `firmware/src/main.cpp` marked `TODO(phase 4)` that it replaces.
3. Keep keys out of git: put them in `firmware/include/secrets.h` (already in `.gitignore`) and commit a `secrets.example.h` with fake values.
4. Keep the deep-sleep burst loop. Re-measure power, because the advertisement and burst timing the network needs may differ from what you tuned in phase 2. Update the table in [01-power-measurement.md](01-power-measurement.md).

## Findings (you write this)

| Project | Last active | C3 support | Worked? | Notes |
|---|---|---|---|---|
| | | | | |

## Credits

Add every project and paper you used to the README "Credits" section, with links.
