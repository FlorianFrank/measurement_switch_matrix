/**
 * @brief This file contains all possible commands, which are connected with a Message object.
 * @author Florian Frank
 * @version 1.0
 */
#ifndef NANOSEC_CROSSBAR_CONTROLLER_COMMANDS_H
#define NANOSEC_CROSSBAR_CONTROLLER_COMMANDS_H

enum Command {
    CONNECT         = 0,
    DISCONNECT      = 1,
    SELECT_ROW      = 2,
    SELECT_COLUMN   = 3,
    ACK             = 4,
    ERROR_CODE      = 5,
    NOPE            = 6
};

#endif //NANOSEC_CROSSBAR_CONTROLLER_COMMANDS_H
