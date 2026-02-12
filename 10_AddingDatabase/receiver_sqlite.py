# Exercise 10 - Store sensor readings into SQLite database

import sqlite3
import time

DB_FILE = "iot_readings.db"

def init_db():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("""
        CREATE TABLE IF NOT EXISTS readings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp INTEGER NOT NULL,
            value INTEGER NOT NULL
        )
    """)
    conn.commit()
    return conn

def main():
    conn = init_db()
    cur = conn.cursor()

    print("Database receiver started...")

    fake_value = 0

    while True:
        timestamp = int(time.time())
        fake_value = (fake_value + 37) % 1024

        cur.execute(
            "INSERT INTO readings (timestamp, value) VALUES (?, ?)",
            (timestamp, fake_value)
        )
        conn.commit()

        print(f"Stored: {timestamp} -> {fake_value}")
        time.sleep(1)

if __name__ == "__main__":
    main()
