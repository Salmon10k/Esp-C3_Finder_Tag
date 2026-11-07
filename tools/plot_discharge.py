#!/usr/bin/env python3
"""Plot the battery discharge curve from the logger CSV.

    python tools/plot_discharge.py data/discharge_log.csv -o docs/img/discharge.png
"""
import argparse

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402
import pandas as pd  # noqa: E402


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("csv", nargs="?", default="data/discharge_log.csv")
    ap.add_argument("-o", "--out", default="docs/img/discharge.png")
    ap.add_argument("--cutoff", type=float, default=3.3,
                    help="volts you treat as 'empty' (default 3.3)")
    ap.add_argument("--window", type=int, default=15,
                    help="rolling-median window to smooth ADC noise")
    args = ap.parse_args()

    df = pd.read_csv(args.csv, parse_dates=["time_iso"])
    df = df[df["battery_mv"] > 0].copy()
    if df.empty:
        raise SystemExit("No valid battery readings in the CSV.")

    df["hours"] = (df["time_iso"] - df["time_iso"].iloc[0]).dt.total_seconds() / 3600
    df["volts"] = df["battery_mv"] / 1000
    df["smooth"] = df["volts"].rolling(args.window, center=True, min_periods=1).median()

    fig, ax = plt.subplots(figsize=(8, 4.5))
    ax.plot(df["hours"], df["volts"], ".", ms=2, alpha=0.3, label="raw")
    ax.plot(df["hours"], df["smooth"], lw=2, label=f"median ({args.window} pts)")
    ax.axhline(args.cutoff, ls="--", lw=1, color="gray", label=f"{args.cutoff} V cutoff")
    ax.set_xlabel("Hours since start")
    ax.set_ylabel("Battery voltage (V)")
    ax.set_title("C3 Finder Tag: discharge curve")
    ax.grid(alpha=0.3)
    ax.legend()
    fig.tight_layout()
    fig.savefig(args.out, dpi=150)

    below = df[df["smooth"] <= args.cutoff]
    if below.empty:
        print(f"Never reached {args.cutoff} V. Logged {df['hours'].iloc[-1]:.1f} h so far.")
    else:
        print(f"Reached {args.cutoff} V after {below['hours'].iloc[0]:.1f} h.")
    print(f"Saved {args.out}")


if __name__ == "__main__":
    main()
