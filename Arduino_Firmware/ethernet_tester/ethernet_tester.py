# echo-client.py

import socket
import json
import time

HOST = "192.168.0.2"
PORT = 2000

json_string = ['{"cmd":"*IDN?"}\0', '{"cmd":"SET_ROW","row":"4"}\0', '{"cmd":"SET_COLUMN","column":"10"}\0', '{"cmd":"SET_ROW_COLUMN","row":"1","column":"2"}\0']

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    for i in json_string:
        print("Send " + i)
        s.sendall(i.encode())
        data = s.recv(60)
        print(data)
        time.sleep(1)
