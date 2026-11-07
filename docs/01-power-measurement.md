# Measuring power (and where to write the results)

Goal: turn "it should last weeks" into numbers you measured.

## Average current

```
I_avg = (I_sleep * t_sleep + I_burst * t_burst) / (t_sleep + t_burst)
runtime_hours ~= battery_mAh / I_avg_mA        (then knock ~20% off for reality)
```

## Three ways to get the numbers, cheapest first

1. **Discharge test (best, free).** Run the `battery` build on the real cell, leave `tools/ble_logger.py` running on a laptop, then `tools/plot_discharge.py`. Time to reach ~3.3 V is your measured runtime. Slow, but it is the honest answer.
2. **Multimeter for sleep current.** Put the meter in series with the battery in the µA/mA range. Don't trust it during the advertising burst: the meter's burden voltage can brown out the board. Put a 470 µF capacitor across the board's supply while measuring, and read the sleep value only.
3. **Proper tool for bursts** (optional): a current profiler such as Nordic PPK2, or a small shunt resistor plus a scope. Not required for this project.

Remember a plain USB power meter can't resolve µA, so it will not show deep-sleep current.

## Things to try (one change at a time)

- `ADV_BURST_MS`: 500 / 1500 / 3000
- `SLEEP_SECONDS`: 5 / 10 / 30 / 60
- `TX_POWER`: lower until your phone stops seeing it, then step back up one
- Power LED removed vs. not (this one will surprise you)
- Battery divider values (it leaks current constantly)

## Results table (fill in; copy the best rows into the README)

| Date | Build settings | Hardware mods | Sleep current | Avg current | Est. runtime | Measured runtime | Notes |
|---|---|---|---|---|---|---|---|
| | burst 1500 ms / sleep 10 s / N0 | stock board | | | | | |
| | burst 1500 ms / sleep 10 s / N0 | LED removed | | | | | |
| | | | | | | | |

## What to say in the README

State how you measured (tool, conditions, which cell). Say plainly if a number is an estimate and not a measurement.
