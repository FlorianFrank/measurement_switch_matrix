//
// Created by florianfrank on 02.11.21.
//

#include "../Include/SerialInterfaceHandler.h"
#include "Arduino.h"

SerialInterfaceHandler::SerialInterfaceHandler(uint16_t baudRate): m_Baudrate(baudRate), m_IsSerialInterfaceOpen(false)
{
    InitializeSerialInterface(); // TODO think about error handling
}

SerialInterfaceHandler::~SerialInterfaceHandler()
{
    m_IsSerialInterfaceOpen = false;
}

ErrorCode SerialInterfaceHandler::InitializeSerialInterface()
{
    Serial.begin(9600);
    while(!Serial)
    {
        // TODO implement timeout and error handling
    }

    m_IsSerialInterfaceOpen = true;

    return NO_ERROR;
}

ErrorCode SerialInterfaceHandler::DeInitializeSerialInterface()
{
    return INVALID_LENGTH;
}

/*static*/ ErrorCode SerialInterfaceHandler::WriteMessage(Message &message) const
{
    if(!m_IsSerialInterfaceOpen)
        return INTERFACE_CLOSED;

    char sendBuffer[MAX_LEN_SEND_BUFFER];
    int len = MAX_LEN_SEND_BUFFER;
    Message::MessageToCharArray(message, sendBuffer, &len);
    if(Serial.write(sendBuffer) != message.GetSize())
    {
        return INVALID_LENGTH;
    }

    return NO_ERROR;
}

/*static*/ Message SerialInterfaceHandler::ReadAndParseMessageBlocking(int *len)
{
    if(!len || *len == 0)
        return Message(0, NOPE);

    int pos = 0;
    char tempData[MAX_COMMAND_LEN];
    memset(tempData, 0x00, MAX_COMMAND_LEN);

    // collect data until \n
    int lenToRead = *len;
    *len = 0;
    do
    {
        *len += Serial.readBytes(&tempData[pos], lenToRead);
        lenToRead =- *len;
        pos += *len;
    } while(!strstr(tempData, "\n") && lenToRead > 0);
    Serial.write(tempData);


    if(*len == 0)
        return Message(0, NOPE);

    return Message::CharArrayToMessage(tempData);
}

/*static*/ Message SerialInterfaceHandler::ReadAndParseMessageNonBlocking(int *len)
{
    if(!len || *len == 0)
        return Message(0, NOPE);


    if(DataAvail() > 0)
        return ReadAndParseMessageBlocking(len);
    return Message(0, NOPE);
}

/*static*/ int SerialInterfaceHandler:: DataAvail()
{
    return Serial.available();
}



