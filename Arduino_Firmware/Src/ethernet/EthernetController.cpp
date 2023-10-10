#include "ethernet/EthernetController.h"
#include "ethernet/EthernetDefines.h"
#include "ethernet/EthernetCommandParser.h"

#include "UIPEthernet.h"
#include "unistd.h"

#define MAX_MSG_SIZE 128
#define MAX_RESPONSE_SIZE 128

/**
 * @brief Sets the MAC address and IP and port of the Ethernet Adapter
 * @param ip IP address to bind the network interface to.
 * @param port Port on which the server should listen.
 */
EthernetController::EthernetController(const byte ip[IP_SIZE], const uint16_t port)
{
    m_IP = new IPAddress(ip);
    m_Server = new EthernetServer(port);
    m_Mac = new uint8_t[MAC_ADDRESS];
}

/**
 * @brief Frees the allocated memory for the IP, MAC and the server.
 */
EthernetController::~EthernetController()
{
    free(m_IP);
    free(m_Mac);
    free(m_Server);
}

/**
 * @brief Initializes the Ethernet Adapter with the given IP and port.
 */
void EthernetController::Initialize()
{
    Ethernet.begin(m_Mac, *m_IP);
    m_Server->begin();
}

/**
 * @brief Must be executed in a loop. It receives a message from the client and parses it.
 * @param row Row which is returned to switch to.
 * @param column Column which is returned to switch to.
 * @return Command which is parsed from the message.
 */
Command EthernetController::ReceiveMessage(int *row, int *column)
{
    Command cmd = NOPE;
    if (EthernetClient client = m_Server->available())
    {
        size_t readMessageSize;
        char *response = (char *) malloc(MAX_RESPONSE_SIZE * sizeof(char));
        memset(response, '\0', MAX_RESPONSE_SIZE * sizeof(char));
        while ((readMessageSize = client.available()) > 0)
        {
            size_t allocSize = ((readMessageSize < MAX_MSG_SIZE) ? readMessageSize : MAX_MSG_SIZE)*sizeof(char);
            char *inputMsg = (char *) malloc(allocSize);
            memset(inputMsg, '\0', allocSize);
            readMessageSize = client.read(reinterpret_cast<uint8_t *>(inputMsg), allocSize);
            if (readMessageSize > 0)
            {
               cmd = EthernetCommandParser::ParseCommand(inputMsg, response, row, column);
               if (cmd == ERROR_CODE)
                    Serial.write("ParseCommand returned an Error\n");
                client.write(response, strlen(response));
            } else
                Serial.println("Receive message returns len < 1");
            free(inputMsg);
        }
        free(response);
    }
    return cmd;
}
