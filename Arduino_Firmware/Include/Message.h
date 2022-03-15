/**
 * @brief This file contains the functionality to transform messages into binary data and vise versa.
 * This allows to transform data into a readable format and into data, which can be transmitted, for example, over an serial interface.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef ARDUINO_BOARD_CONTROLLER_MESSAGE_H
#define ARDUINO_BOARD_CONTROLLER_MESSAGE_H
#include "ErrorHandler.h"
#include "Commands.h"

#define MAX_COMMAND_LEN 50
#define DELIMITER "\n"


class Message
{
public:
    explicit Message(unsigned long parameter, Command command);
    explicit Message(ErrorCode errCode);

    [[nodiscard]] unsigned int GetSize() const;

    static Message CharArrayToMessage(const char *byteMessage);
    static ErrorCode MessageToCharArray(Message& message, char *buffer, int *len);

    // Getters and Setters
    [[nodiscard]] Command GetCurrentCommand() const;
    [[nodiscard]] unsigned long GetParameter() const;

private:
    void Initialize(Command command, unsigned long parameter, const char* errorMessage);
    static unsigned long ParseParameter(const char *inputMessage, const char *searchString, const char *delimiter);
    unsigned int m_Size{};
    Command m_CurrentCommand;
    unsigned long m_parameter{};
    static const char* m_CommandsAsStrings[MAX_COMMAND_LEN];
    const char* m_ErrorMessage{};
};


#endif //ARDUINO_BOARD_CONTROLLER_MESSAGE_H
