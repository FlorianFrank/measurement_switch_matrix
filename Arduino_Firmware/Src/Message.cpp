#include <string.h>
#include <new>
#include <stdio.h>
#include "Message.h"

/**
 * @brief This array contains the possible commands accepted by the control protocol.
 */
/*static*/ const char *Message::m_CommandsAsStrings[MAX_COMMAND_LEN] =
        {
        /** Connect to the Arduino Nano. */
        "connect",
        /** Disconnect from the Arduino Nano. */
        "disconnect",
        /** Select Row (e.g. r: 10). */
        "r:",
        /** Select Column (e.g. c: 2). */
        "c:",
        /** Acknowledge command. */
        "ack",
        /** Error message. */
        "error:",
        /** Do nothing. */
        "nope"};


Message::Message(unsigned long parameter, Command command): m_CurrentCommand(NOPE)
{
    Initialize(command, parameter, "");
}

Message::Message(ErrorCode errCode): m_CurrentCommand(NOPE)
{
    Initialize(ERROR_CODE, 0, ErrorHandler::ErrorCodeToString(errCode));
}

//
// Created by florianfrank on 02.11.21.
//
void Message::Initialize(Command command, unsigned long parameter, const char *errorMessage)
{
    m_Size = 0;
    m_CurrentCommand = command;
    m_parameter = parameter;
    m_ErrorMessage = errorMessage;
}


unsigned int Message::GetSize() const
{
    return m_Size;
}

/*static*/ Message Message::CharArrayToMessage(const char *byteMessage)
{
    int commandCtr = 0;
    for(const char* command: m_CommandsAsStrings)
    {
        if(strstr(byteMessage, command) != nullptr)
        {
            switch ((Command)commandCtr)
            {
                case CONNECT:
                    return Message(0, CONNECT);
                case DISCONNECT:
                    return Message(0, DISCONNECT);
                case SELECT_ROW:
                    return Message(ParseParameter(byteMessage, command, DELIMITER), SELECT_ROW);
                case SELECT_COLUMN:
                    return Message(ParseParameter(byteMessage, command, DELIMITER), SELECT_COLUMN);
                case ACK:
                    return Message(0, ACK);
                case ERROR_CODE:
                    return Message(ParseParameter(byteMessage, command, DELIMITER), ERROR_CODE);
            }
        }
        commandCtr++;
    }
    return Message(INVALID_COMMAND);
}

unsigned long Message::ParseParameter(const char *inputMessage, const char *searchString, const char *delimiter)
{
    if(!inputMessage || !searchString || !delimiter)
        return -1;

    char* ret = strstr(inputMessage, searchString);
    char* delimiterPos = strstr(inputMessage, "\n");

    char valueBuffer[10];
    unsigned int strlenSearchStr = strlen(searchString)+1;
    strncpy(valueBuffer, &ret[strlenSearchStr], delimiterPos - &ret[strlenSearchStr]);

    char *endPtr = &valueBuffer[strlen(valueBuffer)];
    return strtol(valueBuffer, &endPtr, 10);
}

/*static*/ ErrorCode Message::MessageToCharArray(Message &message, char *buffer, int *len)
{
    if(!buffer || !len)
        return INVALID_ARGUMENT;

    char tempBuffer[MAX_COMMAND_LEN];
    int tempLen;
    if(message.m_CurrentCommand == SELECT_ROW || message.m_CurrentCommand == SELECT_COLUMN)
        tempLen = sprintf(tempBuffer, "%s %d\n", m_CommandsAsStrings[message.m_CurrentCommand], message.m_parameter);
    else if(message.m_CurrentCommand == ERROR_CODE)
        tempLen = sprintf(tempBuffer, "%s %s\n", m_CommandsAsStrings[message.m_CurrentCommand], message.m_ErrorMessage);
    else
        tempLen = sprintf(tempBuffer, "%s\n", m_CommandsAsStrings[message.m_CurrentCommand]);


    if (tempLen > *len)
        return INVALID_BUFFER_LEN;

    *len = tempLen;
    strcpy(buffer, tempBuffer);

    return NO_ERROR;
}

Command Message::GetCurrentCommand() const
{
    return m_CurrentCommand;
}

unsigned long Message::GetParameter() const
{
    return m_parameter;
}





