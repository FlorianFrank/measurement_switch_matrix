/**
 * @brief This file implements a TCP handler to receive commands by an AZ delivery ENC28J60 Ethernet Adapter.
 * @author Florian Frank
 * @version 1.0
 */
#include "ethernet/EthernetController.h"
#include "ethernet/EthernetDefines.h"
#include "ethernet/EthernetCommandParser.h"

#include "UIPEthernet.h"

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
    m_MessageBuffer = new char[ETH_MAX_MSG_SIZE];
    m_Response = new char[ETH_MAX_RESPONSE_SIZE];
}

/**
 * @brief Frees the allocated memory for the IP, MAC and the server.
 */
EthernetController::~EthernetController()
{
    free(m_IP);
    free(m_Mac);
    free(m_Server);
    free(m_MessageBuffer);
    free(m_Response);
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
        memset(m_Response, '\0', ETH_MAX_RESPONSE_SIZE * sizeof(char));
        while ((readMessageSize = client.available()) > 0)
        {
            if (readMessageSize > ETH_MAX_MSG_SIZE){
                client.stop();
                return ERROR_CODE;
            }

            memset(m_MessageBuffer, '\0', ETH_MAX_MSG_SIZE);
            readMessageSize = client.read(reinterpret_cast<uint8_t *>(m_MessageBuffer), readMessageSize);
            if (readMessageSize > 0)
            {
                cmd = EthernetCommandParser::ParseCommand(m_MessageBuffer, m_Response, row, column);
                if (cmd == ERROR_CODE)
                    Serial.write("ParseCommand returned an Error\n");
                client.write(m_Response, strlen(m_Response));
            } else
            {
                Serial.println("Receive message returns len < 1");
                return ERROR_CODE;
            }
        }
    }
    return cmd;
}
