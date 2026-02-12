# Exercise 10 - Store sensor readings into a database (SQLite)
# Proof-of-concept receiver. Reads serial lines (numbers) and stores them.

import sqlite3
import time

# If you later use real serial:
# pip install pyserial
# import serial
# ser = serial.Serial("/dev/tty.usbmodemXXXX", 9600, timeout=1)

DB_FILE = "iot_readings.db"

def init_db():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("""
        CREATE TABLE IF NOT EXISTS readings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ts INTEGER NOT NULL,
            value INTEGER NOT NULL
        )
    """)
    conn.commit()
    return conn

def main():
    conn = init_db()
    cur = conn.cursor()

    print("Starting receiver (demo mode). Insert fake values every 1s.")
    # Replace this loop with real serial read when available.
    fake_value = 0

    while True:
        ts = int(time.time())
        fake_value = (fake_value + 37) % 1024

        cur.execute("INSERT INTO readings (ts, value) VALUES (?, ?)", (ts, fake_value))
        conn.commit()

        print(f"stored: ts={ts} value={fake_value}")
        time.sleep(1)

if __name__ == "__main__":
    main()
