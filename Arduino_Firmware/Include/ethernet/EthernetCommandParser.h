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

extern "C" {
#include <tiny-json.h>
}

#define IDENT_STR "NANOSEC Crossbar Controller"
#define NR_COMMANDS 4
#define MAX_CMD_LEN sizeof("SET_ROW_COLUMN")
#define JSON_ELEMENT_POOL_SIZE 3
#define INT_TRANSFORM_BASE 10


class EthernetCommandParser
{
public:
    enum IdentifierCMD{
        /** Returns an identification stirng  */
        IDN = 0,
        SET_ROW = 1,
        SET_COLUMN = 2,
        SET_ROW_COLUMN = 3
    };
    static Command ParseCommand(const char *command, char *response, int *row, int *column);

private:
    static ErrorCode getValueOfJSONElement(json_t const *parent, const char *identifier, char *result, size_t maxLen);
    static ErrorCode
    parseRowColumn(json_t const *parent, char *buffer, EthernetCommandParser::IdentifierCMD identifier, int *row,
                   int *column, char *result);

    static char cmdList[NR_COMMANDS][MAX_CMD_LEN];
};


#endif //NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCOMMANDPARSER_HPP
