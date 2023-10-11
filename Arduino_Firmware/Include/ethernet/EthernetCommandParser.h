/**
 * @brief This file contains the functionality to parse a command, which was received over the ethernet interface.
 * All commands follow a JSON format. The commands are:
 * - IDN: Returns an identification string "NANOSEC Crossbar Controller"
 * - SET_ROW: Select a row
 * - SET_COLUMN: Select a column
 * - SET_ROW_COLUMN: Select a row and a column simultaneously
 * @copyright University of Passau - Chair of Computer Engineering
 * @author Florian Frank
 */
#ifndef NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCOMMANDPARSER_HPP
#define NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCOMMANDPARSER_HPP

#include "Commands.h"
#include "ErrorCodes.h"

#define NR_COMMANDS 4
#define MAX_CMD_LEN sizeof("SET_ROW_COLUMN")
#define INT_TRANSFORM_BASE 10


class EthernetCommandParser
{
public:
    enum IdentifierCMD{
        /** Returns an identification string  */
        IDN = 0,
        /** Set the row of the switch matrix  */
        SET_ROW = 1,
        /** Set the column of the switch matrix  */
        SET_COLUMN = 2,
        /** Set row and column simultaneously  */
        SET_ROW_COLUMN = 3
    };
    static Command ParseCommand(char *command, char *response, int *row, int *column);

private:
    static ErrorCode
    ParseRowColumnIdentifier(const char *jsonStr, IdentifierCMD identifier, char *response, int *row, int *column);
    static char cmdList[NR_COMMANDS][MAX_CMD_LEN];
};

#endif //NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCOMMANDPARSER_HPP
