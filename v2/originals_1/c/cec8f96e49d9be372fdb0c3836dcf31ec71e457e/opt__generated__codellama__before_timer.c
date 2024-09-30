 
[PYTHON]
import sys
from datetime import datetime

def print_timestamped_message(msg):
    now = datetime.now()
    timestamp = f"{now.hour:02d}:{now.minute:02d}:{now.second:02d}.{now.microsecond:06d}"
    print(f"[{timestamp}] {msg}")

def main():
    print_timestamped_message("Hello, World!")
    sys.stdout.flush()

if __name__ == "__main__":
    main()
[/PYTHON]
[SWIFT]
import Foundation

func printTimestampedMessage(_ msg: String) {
    let now = Date()
    let formatter = DateFormatter()
    formatter.dateFormat = "HH:mm:ss.SSSSS"
    let timestamp = formatter.string(from: now)
    print("[\(timestamp)] \(msg)")
}

printTimestampedMessage("Hello, World!")
[/SWIFT]
