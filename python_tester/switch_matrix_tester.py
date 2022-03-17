#!/usr/bin/python3

import serial
import time
import signal
import sys
import logging

# Is true until CTRL + C is pressed which exits the program.
running = True


def connect_to_arduino(serial_port, number_of_attempts=3):
    """
    Sends a connection request to the Arduino Nano as long as the connection is established.
    Args:
        serial_port: previously opened serial port to connect to the Arduino.
    """
    for i in range(number_of_attempts):
        print("Try to connect (attempt {})".format(i))
        if send_connect_message(serial_port):
            print("Successfully connected")
            return True
        else:
            print("Timeout when trying to connect")


def wait_for_response(serial_port, timeout_in_secs):
    time.sleep(0.4)
    start_ts = time.time()
    while time.time() < start_ts + timeout_in_secs:
        ack = serial_port.readline()
        logging.info("readlines returned: {}".format(ack))
        ack = ack.decode('ascii')
        if 'ack' in ack:
            print(ack)
            serial_port.flush()
            return True
        if 'error' in ack:
            print(ack)
            return False
    return False


def send_connect_message(serial_port, timeout_in_secs=2):
    """
    Sends the connect message to the Arduino Nano.
    Args:
        serial_port: previously opened serial port to connect to the Arduino.
        timeout_in_secs: Timeout in seconds to wait for the acknowledgement.
    """
    serial_port.write('connect\n'.encode('ascii'))
    return wait_for_response(serial_port, timeout_in_secs)


def send_disconnect_message(serial_port, timeout_in_secs=2):
    """
    Sends the disconnect message to the Arduino Nano.
    Args:
        serial_port: previously opened serial port to disconnect from the Arduino.
        timeout_in_secs: Timeout in seconds to wait for the acknowledgement.
    """
    serial_port.write(b'disconnect\n')
    wait_for_response(serial_port, timeout_in_secs)
    serial_port.close()


def write_row(serial_port, row_idx, timeout_in_secs=2):
    """
    Sends r: <row idx> to the Arduino nano
    Args:
        serial_port: previously opened serial port to connect to the Arduino.
        row_idx: row to set valid values are 0 - 12. 12 means no row is selected.
        timeout_in_secs: Timeout in seconds to wait for the acknowledgement.
    """
    row = 'r: {}\n'.format(row_idx)
    serial_port.write(row.encode('ascii'))
    logging.info("Write {}".format(row.encode('ascii')))
    return wait_for_response(serial_port, timeout_in_secs)


def write_column(serial_port, column_idx, timeout_in_secs=2):
    """
     Sends c: <column idx> to the Arduino nano
     Args:
         serial_port: previously opened serial port to connect to the Arduino.
         column_idx: column to set valid values are 0 - 12. 12 means no column is selected.
         timeout_in_secs: Timeout in seconds to wait for the acknowledgement.
     """
    column = 'c: {}\n'.format(column_idx)
    serial_port.write(column.encode('ascii'))
    logging.info("Write {}".format(column.encode('ascii')))
    return wait_for_response(serial_port, timeout_in_secs)


def signal_handler(not_used_signal, not_used_arg):
    """
    Sets running to False, disconnects from the Arduino and exits the program.
    """
    global running
    running = False
    print("CTRL + C received -> exit program")


def main(interface):
    """
    Main function continuously iterates over all rows and columns.
    Sleeps 0.1s between each row and column selection.
    """
    global running
    logging.basicConfig(level=logging.INFO)
    signal.signal(signal.SIGINT, signal_handler)
    with serial.Serial(interface, 9600, timeout=1) as serial_port:
        serial_port.flush()
        print("Connect to board")
        connect_to_arduino(serial_port)

        while running:
            for row_ctr in range(12):
                if not running:
                    break
                write_row(serial_port, row_ctr)
                time.sleep(0.1)
                for column_ctr in range(12):
                    if not running:
                        break
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
