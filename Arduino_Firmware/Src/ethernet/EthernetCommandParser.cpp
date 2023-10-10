#include "ethernet/EthernetCommandParser.h"

#include "Arduino.h"
#include <string.h>
extern "C" {
#include <tiny-json.h>
}

/**
 * @brief This array contains all commands which are supported by the ethernet interface.
 */
/*static*/ char EthernetCommandParser::cmdList[NR_COMMANDS][MAX_CMD_LEN] = {"*IDN?", "SET_ROW",
                                                                                         "SET_COLUMN",
                                                                                         "SET_ROW_COLUMN"};

/**
 * @brief This method parses a command in json format received from the ethernet interface.
 * @param command command in json format, e.g. {"cmd":"SET_ROW_COLUMN","row":1,"column":2}.
 * @param response response in json format, e.g. {"status":"ok","row":1,"column":2}.
 * @param row Parsed row returned when the command is SET_ROW or SET_ROW_COLUMN.
 * @param column Parsed column returned when the command is SET_COLUMN or SET_ROW_COLUMN.
 * @return Parsed command.
 */
/*static*/ Command EthernetCommandParser::ParseCommand(const char *command, char *response, int *row, int *column)
{
    Serial.println(command);
    json_t pool[JSON_ELEMENT_POOL_SIZE];
    json_t const *parent = json_create((char *) command, pool, JSON_ELEMENT_POOL_SIZE);
    if (!parent)
    {
        sprintf(response, R"({"status":"err","msg":"json_create returned null"})");
        Serial.println("json_create returned null\n");
        return ERROR_CODE;
    }
    char cmdIdentifier[MAX_CMD_LEN];
    memset(cmdIdentifier, '\0', MAX_CMD_LEN);
    if (getValueOfJSONElement(parent, "cmd", cmdIdentifier, MAX_CMD_LEN) != NO_ERROR)
    {
        sprintf(response, R"({"status":"err","msg":"Could not parse cmd"})");
        Serial.println("getValueOfJSONElement returned -1\n");
        return ERROR_CODE;
    }
    Serial.println(cmdIdentifier);

    if (strncmp(cmdIdentifier, "*IDN?", MAX_CMD_LEN) == 0)
    {
        sprintf(response, R"({"status":"ok","idn":"NANOSec Crossbar Controller"})");
        return IDENT;
    }
    else if (strncmp(cmdIdentifier, cmdList[SET_COLUMN], MAX_CMD_LEN) == 0)
    {
        memset(cmdIdentifier, '\0', MAX_CMD_LEN);
        if(EthernetCommandParser::parseRowColumn(parent, cmdIdentifier, SET_COLUMN, nullptr, column, response) != NO_ERROR){
            sprintf(response, R"({"status":"err","msg":"parseRowColumn returned an error"})");
            return ERROR_CODE;
        }
        return SELECT_ROW;
    }
    else if (strcmp(cmdIdentifier, cmdList[SET_ROW]) == 0)
    {
        memset(cmdIdentifier, '\0', MAX_CMD_LEN);
        if(EthernetCommandParser::parseRowColumn(parent, cmdIdentifier, SET_ROW, row, nullptr, response) != NO_ERROR){
            sprintf(response, R"({"status":"err","msg":"parseRowColumn returned an error"})");
            return ERROR_CODE;
        }
        return SELECT_ROW;
    }

    else if (strcmp(cmdIdentifier, cmdList[SET_ROW_COLUMN]) == 0)
    {
     /*   memset(cmdIdentifier, '\0', MAX_CMD_LEN);
        if(EthernetCommandParser::parseRowColumn(parent, cmdIdentifier, SET_ROW_COLUMN, row, column, response) != NO_ERROR){
            sprintf(response, R"({"status":"err","msg":"parseRowColumn returned an error"})");
            return ERROR_CODE;
        }
        return SELECT_ROW_COLUMN;*/
    }
 //   sprintf(response, R"({"status":"err","msg":"Invalid cmd"})");
   // return ERROR_CODE;
}

/**
 * @brief Parses a json element and returns its value.
 * @param parent parent json object which contains the element.
 * @param identifier identifier of the element, e.g. "cmd".
 * @param result value corresponding to the identifier, e.g. "SET_ROW_COLUMN". when the identifier is "cmd".
 * @return ErrorCode::NO_ERROR if no error occurred otherwise return an error code.
 */
/*static*/ ErrorCode
EthernetCommandParser::getValueOfJSONElement(json_t const *parent, const char *identifier, char *result, size_t maxLen)
{
    json_t const *command_property = json_getProperty(parent, identifier);
    if (!command_property)
        return ErrorCode::RETURNED_NULLPTR;

    if (json_getType(command_property) != JSON_TEXT)
        return ErrorCode::JSON_PARSING_ERROR;

    char const *parsedValue = json_getValue(command_property);
    if (!parsedValue)
        return ErrorCode::RETURNED_NULLPTR;

    if(strlen(parsedValue) > maxLen)
        return ErrorCode::JSON_PARSING_ERROR;
    strncpy(result, parsedValue, strlen(parsedValue));
    return ErrorCode::NO_ERROR;
}


/*static*/ ErrorCode
EthernetCommandParser::parseRowColumn(json_t const *parent, char *buffer, IdentifierCMD identifier, int *row,
                    int *column, char *result)
{
/*    auto StrToInt = [](char *strToTransform, int* result) -> ErrorCode {
        *result = atoi(strToTransform);
        return NO_ERROR;
       *//* char *endPtr;
        *result = static_cast<int>(strtol(strToTransform, &endPtr, INT_TRANSFORM_BASE));
        if (*endPtr != '\0' && !isspace((unsigned char)*endPtr)) {
            return JSON_PARSING_ERROR;
        } else {
            return NO_ERROR;
        }*//*
    };*/

    switch (identifier)
    {
        case EthernetCommandParser::SET_ROW:
        {
            auto ret = getValueOfJSONElement(parent, "row", buffer, MAX_CMD_LEN);

           // if(ret != NO_ERROR)
             //   return ret;
//            *auto errCode = StrToInt(buffer, row);
  //          if(errCode != NO_ERROR)
    //            return errCode;

            *row = atoi(buffer);
            sprintf(result, R"({"status":"ok","row": %d})", *row);
            return NO_ERROR;
        }
       case EthernetCommandParser::SET_COLUMN:
        {
            auto ret = getValueOfJSONElement(parent, "column", buffer, MAX_CMD_LEN);

            // if(ret != NO_ERROR)
            //   return ret;
//            *auto errCode = StrToInt(buffer, row);
           //          if(errCode != NO_ERROR)
           //            return errCode;

           *column = atoi(buffer);
           sprintf(result, R"({"status":"ok","column": %d})", *column);
           return NO_ERROR;
        }
    //   case EthernetCommandParser::SET_ROW_COLUMN:
      /*  {
            auto ret = getValueOfJSONElement(parent, "column", buffer, MAX_CMD_LEN);
            *column = atoi(buffer);
            memset(buffer, '\0', MAX_CMD_LEN);
            ret = getValueOfJSONElement(parent, "row", buffer, MAX_CMD_LEN);
            *row = atoi(buffer);

            sprintf(result, R"({"status":"ok","column":%d,"row":%d})", *column, *row);
            return NO_ERROR;
        }*/
    }
}
