#include "ethernet/EthernetCommandParser.h"

#include "Arduino.h"
#include <string.h>

#define IDENT_RESPONSE R"({"status":"ok","idn":"NANOSec Crossbar Controller"})"
#define SET_ROW_RESPONSE R"({"status":"ok","row":%d})"
#define SET_COLUMN_RESPONSE R"({"status":"ok","column":%d})"
#define SET_ROW_COLUMN_RESPONSE R"({"status":"ok","row":%d,"column":%d})"

#define PARSE_CMD_ERR_RESPONSE R"({"status":"err","msg":"Could not parse cmd"})"
#define UNKNOWN_CMD_ERR_RESPONSE R"({"status":"err","msg":"Unknown command: %s"})"
#define RESPONSE_JSON_PARSE_ERR R"({"status":"err","msg":"json_parsing_error"})"

#define ROW_IDENTIFIER "row"
#define COLUMN_IDENTIFIER "column"

/**
 * @brief This array contains all commands which are supported by the ethernet interface.
 */
/*static*/ char EthernetCommandParser::cmdList[NR_COMMANDS][MAX_CMD_LEN] = {"*IDN?", "SET_ROW",
                                                                            "SET_COLUMN",
                                                                            "SET_ROW_COLUMN"};

/**
 * @brief This method extracts the value of a json element by its key.
 * @param jsonString a json sting, e.g. {"cmd":"SET_ROW_COLUMN","row":1,"column":2}.
 * @param key the key to filter, e.g. "cmd" or "row".
 * @return The corresponding value of the key, e.g. "SET_ROW_COLUMN" or "1".
 */
void extractJSONValueByKey(const char *jsonString, const char *key, char *extractedKey) {
    const char *cmdValue = nullptr;

    // Find the position of the "key" field
    const char *keyPos = strstr(jsonString, key);

    if (keyPos != nullptr) {
        // Find the starting position of the value (after the colon and any whitespace)
        keyPos = strstr(keyPos, ":");
        if (keyPos != nullptr) {
            keyPos++;
            while (isspace((unsigned char) *keyPos)) {
                keyPos++;
            }

            if (*keyPos == '"') {
                // String value
                cmdValue = keyPos + 1;
                keyPos = strchr(cmdValue, '"');
                if (keyPos != nullptr) {
                    // Calculate the length of the extracted value
                    size_t cmdLength = keyPos - cmdValue;
                    // Allocate memory and copy the value
                    if (extractedKey != nullptr) {
                        strncpy(extractedKey, cmdValue, cmdLength);
                        extractedKey[cmdLength] = '\0';
                    } else {
                        Serial.println(F("Malloc returned nullptr!"));
                    }
                }
            } else if (isdigit((unsigned char) *keyPos) || *keyPos == '-') {
                // Numeric value (integer or float)
                const char *endPos = keyPos;
                while (*endPos &&
                       (isdigit((unsigned char) *endPos) || *endPos == '.' || *endPos == '-' || *endPos == 'e' ||
                        *endPos == 'E')) {
                    endPos++;
                }
                size_t cmdLength = endPos - keyPos;
                // Allocate memory and copy the numeric value
                if (extractedKey != nullptr) {
                    strncpy(extractedKey, keyPos, cmdLength);
                    extractedKey[cmdLength] = '\0';
                }
            }
        }
    }
}

/**
 * @brief This method parses a command in json format received from the ethernet interface.
 * @param command command in json format, e.g. {"cmd":"SET_ROW_COLUMN","row":1,"column":2}.
 * @param response response in json format, e.g. {"status":"ok","row":1,"column":2}.
 * @param row Parsed row returned when the command is SET_ROW or SET_ROW_COLUMN.
 * @param column Parsed column returned when the command is SET_COLUMN or SET_ROW_COLUMN.
 * @return Parsed command.
 */
/*static*/ Command EthernetCommandParser::ParseCommand(char *command, char *response, int *row, int *column) {
    char *cmdValue = (char *) malloc(14);
    extractJSONValueByKey(command, "cmd", cmdValue);

    Command ret;
    if (!cmdValue) {
        strcpy(response, PARSE_CMD_ERR_RESPONSE);
        ret = ERROR_CODE;
    }

    if (strcmp(cmdValue, cmdList[IDN]) == 0) {
        strcpy(response, IDENT_RESPONSE);
        ret = IDENT;
    } else if (strcmp(cmdValue, cmdList[SET_ROW]) == 0) {
        if (ParseRowColumnIdentifier(command, SET_ROW, response, row, nullptr) != NO_ERROR) {
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            ret = ERROR_CODE;
        } else {
            ret = SELECT_ROW;
        }
    } else if (strcmp(cmdValue, cmdList[SET_COLUMN]) == 0) {
        if (ParseRowColumnIdentifier(command, SET_COLUMN, response, nullptr, column) != NO_ERROR) {
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            ret = ERROR_CODE;
        } else {
            ret = SELECT_COLUMN;
        }
    } else if (strcmp(cmdValue, cmdList[SET_ROW_COLUMN]) == 0) {
        if (ParseRowColumnIdentifier(command, SET_ROW_COLUMN, response, row, column) != NO_ERROR) {
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            ret = ERROR_CODE;
        } else {
            ret = SELECT_ROW_COLUMN;
        }
    } else {
        sprintf(response, UNKNOWN_CMD_ERR_RESPONSE, cmdValue);
        ret = ERROR_CODE;
    }

    free(cmdValue);
    return ret;
}

/**
 * @brief Parses a json element and returns its value.
 * @param jsonStr parent json object which contains the element.
 * @param identifier identifier of the element, e.g. "cmd".
 * @param response value corresponding to the identifier, e.g. "SET_ROW_COLUMN". when the identifier is "cmd".
 * @return ErrorCode::NO_ERROR if no error occurred otherwise return an error code.
 */
/*static*/ ErrorCode
EthernetCommandParser::ParseRowColumnIdentifier(const char *jsonStr, IdentifierCMD identifier, char *response, int *row,
                                                int *column) {
    auto StrToInt = [](const char *strToTransform, int *result, char *response) -> ErrorCode {
        char *endPtr;
        *result = static_cast<int>(strtol(strToTransform, &endPtr, INT_TRANSFORM_BASE));
        if (*endPtr != '\0' && !isspace((unsigned char) *endPtr)) {
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            return JSON_PARSING_ERROR;
        }
        return NO_ERROR;
    };

    switch (identifier) {
        case SET_ROW: {
            char *rowValue = (char*) malloc(2);
            extractJSONValueByKey(jsonStr, ROW_IDENTIFIER, rowValue);

            ErrorCode ret;
            if (!rowValue) {
                ret = JSON_PARSING_ERROR;
            } else {
                ret = StrToInt(rowValue, row, response);
                if (ret == NO_ERROR) {
                    sprintf(response, SET_ROW_RESPONSE, *row);
                }
            }
            free(rowValue);
            return ret;
        }
        case SET_COLUMN: {
            char *columnValue = (char*) malloc(2);
            extractJSONValueByKey(jsonStr, COLUMN_IDENTIFIER, columnValue);
            ErrorCode ret;
            if (!columnValue) {
                ret = JSON_PARSING_ERROR;
            } else {
                ret = StrToInt(columnValue, column, response);
                if (ret == NO_ERROR) {
                    sprintf(response, SET_COLUMN_RESPONSE, *column);
                }
            }
            free(columnValue);
            return ret;
        }
        case SET_ROW_COLUMN: {
            char *rowValue = (char*) malloc(2);
            extractJSONValueByKey(jsonStr, ROW_IDENTIFIER, rowValue);
            ErrorCode ret;
            if (!rowValue) {
                free(rowValue);
                return JSON_PARSING_ERROR;
            } else {
                ret = StrToInt(rowValue, row, response);
                if (ret != NO_ERROR) {
                    free(rowValue);
                    return ret;
                }
            }

            char *columnValue = (char*) malloc(2);
            extractJSONValueByKey(jsonStr, COLUMN_IDENTIFIER, columnValue);
            if (!columnValue) {
                ret = JSON_PARSING_ERROR;
            } else {
                ret = StrToInt(columnValue, column, response);
                if (ret == NO_ERROR) {
                    sprintf(response, SET_ROW_COLUMN_RESPONSE, *row, *column);
                }
            }
            free(rowValue);
            free(columnValue);
            return ret;
        }
    }
}
