#!/usr/bin/python3

import serial
import time
import signal
import sys

# Is true until CTRL + C is pressed which exits the program.
running = True


def connect_to_arduino(serial_port):
    """
    Sends a connection request to the Arduino Nano as long as the connection is established.
    Args:
        serial_port: previously opened serial port to connect to the Arduino.
    """
    send_connect_message(serial_port)
    ret = serial_port.readline()
    while len(ret) == 0:
        send_connect_message(serial_port)
        ret = serial_port.readline()


def send_connect_message(serial_port):
    """
    Sends the connect message to the Arduino Nano.
    Args:
        serial_port: previously opened serial port to connect to the Arduino.
    """
    return serial_port.write('connect\n'.encode('ascii'))


def send_disconnect_message(serial_port):
    """
    Sends the disconnect message to the Arduino Nano.
    Args:
        serial_port: previously opened serial port to disconnect from the Arduino.
    """
    return serial_port.write('disconnect\n'.encode('ascii'))


def write_row(serial_port, row_idx):
    """
    Sends r: <row idx> to the Arduino nano
    Args:
        serial_port: previously opened serial port to connect to the Arduino.
        row_idx: row to set valid values are 0 - 12. 12 means no row is selected.
    """
    row = 'r:{}\n'.format(row_idx)
    serial_port.write(row.encode('ascii'))


def write_column(serial_port, column_idx):
    """
     Sends c: <column idx> to the Arduino nano
     Args:
         serial_port: previously opened serial port to connect to the Arduino.
         column_idx: column to set valid values are 0 - 12. 12 means no column is selected.
     """
    column = 'c:{}\n'.format(column_idx)
    serial_port.write(column.encode('ascii'))


def signal_handler():
    """
    Sets running to False, disconnects from the Arduino and exits the program.
    """
    global running
    running = False
    printf("CTRL + C received -> exit program")


def main(interface):
    """
    Main function continuously iterates over all rows and columns.
    Sleeps 0.1s between each row and column selection.
    """
    signal.signal(signal.SIGINT, signal_handler)
    with serial.Serial(interface, 9600, timeout=2, parity=serial.PARITY_NONE) as serial_port:
        print("Connect to board")
        connect_to_arduino(serial_port)

        while running:
            for row_ctr in range(12):
                write_row(serial_port, row_ctr)
                time.sleep(0.1)
                for column_ctr in range(12):
                    print("Select Row: {} Column: {}".format(row_ctr, column_ctr))
                    write_column(serial_port, column_ctr)
                    time.sleep(0.1)
        send_disconnect_message(serial_port)


"""
Execute by command python3 switch_matrix_tester.py <com port>
"""
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Pass COM port as command line argument, e.g. '/dev/ttyUSB0' on Linux or 'COM3' on Windows")
    else:
        print("****Start Switch Matrix Tester****")
        main(sys.argv[1])
