# Start here: what to write, where, and when

This is your build guide. Work top to bottom. Each phase ends with a git tag so
your history reads like a story.

## Repo map

| Path | What it is | Status |
|---|---|---|
| `firmware/src/main.cpp` | BLE advertising, burst/deep-sleep, battery read | Working starter. You extend it (look for `TODO(phase N)`). |
| `firmware/include/config.h` | Every tunable (name, timing, TX power, pins) | Edit this, not magic numbers in code. |
| `firmware/platformio.ini` | Two envs: `debug` (bench) and `battery` (field) | Done. |
| `hardware/README.md` | Wiring, power notes, safety | Read first, then add your photos/notes. |
| `hardware/bom.csv` | Parts list | Add the real parts you bought. |
| `tools/ble_logger.py` | Logs broadcast battery voltage to CSV | Done. You run it. |
| `tools/plot_discharge.py` | Plots the discharge curve | Done. You run it. |
| `docs/01-power-measurement.md` | How to measure + a table to fill | You fill the numbers. |
| `docs/02-find-network.md` | Research checklist for Phase 4 | You do the research, record findings. |
| `README.md` | The front page | Has `<!-- WRITE: ... -->` hints per section. |
| `.github/workflows/build.yml` | CI: compiles both envs on every push | Done. Gives you a green badge. |

## Phases

### Phase 1: beacon (tag `v0.1`)
1. Install PlatformIO (VS Code extension or `pip install platformio`).
2. `cd firmware && pio run -e debug -t upload && pio device monitor`
3. Open **nRF Connect** on your phone and find `C3-Finder`. Open its manufacturer data: bytes 3-4 are the battery mV, 5-6 the sequence.
4. Screenshot it to `docs/img/nrf-connect.png`.
5. **You write:** change `DEVICE_NAME`, then fill the README "Why I built this".
6. Commit: `feat(firmware): BLE beacon with battery+seq payload`

### Phase 2: low power (tag `v0.2`)
1. Flash `-e battery`. It advertises for `ADV_BURST_MS`, then deep-sleeps `SLEEP_SECONDS`.
2. Try 3-4 combinations of burst length / sleep / TX power. Check how reliably your phone sees it.
3. Measure current with [docs/01-power-measurement.md](01-power-measurement.md) and fill the table.
4. **You write:** README "How it works" + the first rows of "Power results".
5. Commit: `feat(firmware): deep-sleep burst mode` and `docs: add power measurements`

### Phase 3: battery hardware (tag `v0.3`)
1. Follow [hardware/README.md](../hardware/README.md): LiPo + TP4056 + switch + divider, remove the power LED.
2. Take a photo, save as `docs/img/build.jpg`.
3. Run `python tools/ble_logger.py` on a laptop next to the tag and leave it for days. This is your discharge test.
4. `python tools/plot_discharge.py` then save the PNG to `docs/img/discharge.png` and embed it in the README.
5. **You write:** README "Hardware" and the measured runtime column.
6. Commit: `docs(hardware): wiring, BOM, photos` and `feat(tools): discharge logging`

### Phase 4: Find network (tag `v0.4`)
Read [02-find-network.md](02-find-network.md) first. It is a research task, not a copy-paste one. Record what you tried (including failures) in that file; it makes the repo better, not worse.

### Phase 5: polish (tag `v1.0`)
3D-printed case, final README pass, fill "Limitations" and "Credits", add repo topics (`esp32`, `esp32-c3`, `ble`, `platformio`, `low-power`, `find-my`), pin the repo on your profile.

## Commit style

Small commits, one idea each, prefix with what changed:
`feat:` new behaviour, `fix:` bug, `docs:` writing, `chore:` tooling.
Tag at the end of each phase: `git tag v0.1 && git push --tags`.

## Hygiene (important)

- **Never commit secrets.** Find Hub tooling uses Google account tokens and keys. `.gitignore` already blocks common names, but check `git status` before every commit.
- Don't commit a photo that shows a home address, plate number, or private account.
- Keep real measured data in `data/` and commit it on purpose; it's part of the story.

## README rule of thumb

If a sentence in the README can't be backed by something in the repo (a photo, a number, a log, a file), cut it or label it as a goal.
