/**
 * @brief This file contains all possible commands, which are connected with a Message object.
 * @author Florian Frank
 * @version 1.0
 */
#ifndef NANOSEC_CROSSBAR_CONTROLLER_COMMANDS_H
#define NANOSEC_CROSSBAR_CONTROLLER_COMMANDS_H

enum Command {
    /** Establish a connection to the Arduino Nano. */
    CONNECT         = 0,
    /** Disconnect connection from the Arduino Nano. */
    DISCONNECT      = 1,
    /** Select and switch a ro specified by its ID. */
    SELECT_ROW      = 2,
    /** Select and switch a column specified by its ID. */
    SELECT_COLUMN   = 3,
    /** Send an acknowledgement that a certain command was executed. */
    ACK             = 4,
    /** Send error code if an error occurred. */
    ERROR_CODE      = 5,
    /** No command executed. */
    NOPE            = 6
};

#endif //NANOSEC_CROSSBAR_CONTROLLER_COMMANDS_H
