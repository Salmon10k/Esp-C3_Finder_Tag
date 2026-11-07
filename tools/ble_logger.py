#!/usr/bin/env python3
"""Log the battery voltage the tag broadcasts into a CSV file.

Leave this running on a PC/laptop with Bluetooth near the tag while it runs
on battery. Afterwards, plot it with tools/plot_discharge.py.

    python tools/ble_logger.py --out data/discharge_log.csv
"""
import argparse
import asyncio
import csv
import os
import struct
from datetime import datetime

from bleak import BleakScanner

COMPANY_ID = 0xFFFF  # must match COMPANY_ID in firmware/include/config.h


async def run(out_path: str, name: str) -> None:
    os.makedirs(os.path.dirname(out_path) or ".", exist_ok=True)
    new_file = not os.path.exists(out_path)
    last_seq = None

    with open(out_path, "a", newline="") as f:
        writer = csv.writer(f)
        if new_file:
            writer.writerow(["time_iso", "battery_mv", "seq", "rssi"])
            f.flush()

        def on_adv(device, adv):
            nonlocal last_seq
            if adv.local_name != name:
                return
            data = adv.manufacturer_data.get(COMPANY_ID)
            if not data or len(data) < 4:
                return
            mv, seq = struct.unpack("<HH", data[:4])
            if seq == last_seq:  # one burst = many adverts, log it once
                return
            last_seq = seq
            now = datetime.now().isoformat(timespec="seconds")
            writer.writerow([now, mv, seq, adv.rssi])
            f.flush()
            print(f"{now}  {mv} mV  seq={seq}  rssi={adv.rssi}")

        print(f"Listening for '{name}'... Ctrl+C to stop.")
        async with BleakScanner(on_adv):
            await asyncio.Event().wait()


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", default="data/discharge_log.csv")
    ap.add_argument("--name", default="C3-Finder", help="DEVICE_NAME in config.h")
    args = ap.parse_args()
    try:
        asyncio.run(run(args.out, args.name))
    except KeyboardInterrupt:
        print("\nStopped.")


if __name__ == "__main__":
    main()
