#include "ethernet/EthernetCommandParser.h"

#include "Arduino.h"
#include <string.h>

#define IDENT_RESPONSE R"({"status":"ok","idn":"NANOSec Crossbar Controller"})"
#define SET_ROW_RESPONSE R"({"status":"ok","row":"%d"})"
#define SET_COLUMN_RESPONSE R"({"status":"ok","column":"%d"})"
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
const char* extractJSONValueByKey(const char* jsonString, const char* key) {
    const char* cmdValue = nullptr;

    // Find the position of the "key" field
    const char* keyPos = strstr(jsonString, key);

    if (keyPos != nullptr) {
        // Find the starting position of the value (after the colon and any whitespace)
        keyPos = strstr(keyPos, ":");
        if (keyPos != nullptr) {
            keyPos++;
            while (isspace((unsigned char)*keyPos)) {
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
                    char* extractedKey = (char*)malloc(cmdLength + 1);
                    if (extractedKey != nullptr) {
                        strncpy(extractedKey, cmdValue, cmdLength);
                        extractedKey[cmdLength] = '\0';
                        return extractedKey;
                    }
                }
            } else if (isdigit((unsigned char)*keyPos) || *keyPos == '-') {
                // Numeric value (integer or float)
                const char* endPos = keyPos;
                while (*endPos && (isdigit((unsigned char)*endPos) || *endPos == '.' || *endPos == '-' || *endPos == 'e' || *endPos == 'E')) {
                    endPos++;
                }
                size_t cmdLength = endPos - keyPos;
                // Allocate memory and copy the numeric value
                char* extractedKey = (char*)malloc(cmdLength + 1);
                if (extractedKey != nullptr) {
                    strncpy(extractedKey, keyPos, cmdLength);
                    extractedKey[cmdLength] = '\0';
                    return extractedKey;
                }
            }
        }
    }
    return nullptr;
}

/**
 * @brief This method parses a command in json format received from the ethernet interface.
 * @param command command in json format, e.g. {"cmd":"SET_ROW_COLUMN","row":1,"column":2}.
 * @param response response in json format, e.g. {"status":"ok","row":1,"column":2}.
 * @param row Parsed row returned when the command is SET_ROW or SET_ROW_COLUMN.
 * @param column Parsed column returned when the command is SET_COLUMN or SET_ROW_COLUMN.
 * @return Parsed command.
 */
/*static*/ Command EthernetCommandParser::ParseCommand(char *command, char *response, int *row, int *column)
{
    Serial.println(command);
    const char* cmdValue = extractJSONValueByKey(command, "cmd");
    if(!cmdValue){
        strcpy(response, PARSE_CMD_ERR_RESPONSE);
        return ERROR_CODE;
    }

    if(strcmp(cmdValue, cmdList[IDN]) == 0){
        strcpy(response, IDENT_RESPONSE);
        return IDENT;
    } else if(strcmp(cmdValue, cmdList[SET_ROW]) == 0){
        if(ParseRowColumnIdentifier(command, SET_ROW, response, row, nullptr) != NO_ERROR){
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            return ERROR_CODE;
        }
        return SELECT_ROW;
    }else if(strcmp(cmdValue, cmdList[SET_COLUMN]) == 0){
        Serial.println(cmdValue);

        if(ParseRowColumnIdentifier(command, SET_COLUMN, response, nullptr, column) != NO_ERROR){
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            return ERROR_CODE;
        }
        return SELECT_COLUMN;
    }else if(strcmp(cmdValue, cmdList[SET_ROW_COLUMN]) == 0){
        if(ParseRowColumnIdentifier(command, SET_ROW_COLUMN, response, row, column) != NO_ERROR){
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            return ERROR_CODE;
        }
        return SELECT_ROW_COLUMN;
    }
        sprintf(response, UNKNOWN_CMD_ERR_RESPONSE, cmdValue);
        return ERROR_CODE;
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
                                                int *column)
{
    auto StrToInt = [](const char *strToTransform, int* result, char* response) -> ErrorCode {
        char *endPtr;
        Serial.println(strToTransform);
        *result = static_cast<int>(strtol(strToTransform, &endPtr, INT_TRANSFORM_BASE));
        if (*endPtr != '\0' && !isspace((unsigned char)*endPtr)) {
            strcpy(response, RESPONSE_JSON_PARSE_ERR);
            return JSON_PARSING_ERROR;
        }
        return NO_ERROR;
    };

    switch (identifier)
    {
        case SET_ROW:
        {
            const char *rowValue = extractJSONValueByKey(jsonStr, ROW_IDENTIFIER);
            if (!rowValue)
                return JSON_PARSING_ERROR;
            auto ret = StrToInt(rowValue, row, response);
            if (ret == NO_ERROR)
                sprintf(response, SET_ROW_RESPONSE, *row);
            return ret;
        }
        case SET_COLUMN:
        {
            const char *columnValue = extractJSONValueByKey(jsonStr, COLUMN_IDENTIFIER);
            if (!columnValue)
                return JSON_PARSING_ERROR;
            auto ret = StrToInt(columnValue, column, response);
            if (ret == NO_ERROR)
                sprintf(response, SET_COLUMN_RESPONSE, *column);
            return ret;
        }
        case SET_ROW_COLUMN:
        {
            const char *rowValue = extractJSONValueByKey(jsonStr, ROW_IDENTIFIER);
            if (!rowValue)
                return JSON_PARSING_ERROR;
            auto ret = StrToInt(rowValue, row, response);
            if (ret != NO_ERROR)
                return ret;

            const char *columnValue = extractJSONValueByKey(jsonStr, COLUMN_IDENTIFIER);
            if (!columnValue)
                return JSON_PARSING_ERROR;
            ret = StrToInt(columnValue, column, response);
            if (ret == NO_ERROR)
                sprintf(response, SET_ROW_COLUMN_RESPONSE, *row, *column);
            return ret;
        }
    }
}
