import socket
import json
import time

HOST = "192.168.0.2"
PORT = 2000
TIMEOUT = 5  # 5 seconds

json_strings = [
    {"cmd": "*IDN?"},
    {"cmd": "SET_ROW", "row": "4"},
    {"cmd": "SET_COLUMN", "column": "10"},
    {"cmd": "SET_ROW_COLUMN", "row": "1", "column": "2"},
]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
        s.settimeout(TIMEOUT)  # Set a timeout for socket operations

        for json_data in json_strings:
            json_string = json.dumps(json_data)
            print("Send:", json_string)
            s.sendall(json_string.encode())
            data = s.recv(60)
            print("Received:", data)
            time.sleep(1)
    except (socket.timeout, ConnectionError) as e:
        print("Error:", e)

