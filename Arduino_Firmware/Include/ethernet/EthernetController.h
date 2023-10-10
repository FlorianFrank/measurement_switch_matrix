/**
 * @brief This file contains the functionality to control the ethernet connection to the control computer.
 * @copyright University of Passau - Chair of Computer Engineering
 * @author Florian Frank
 */
#ifndef NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCONTROLLER_HPP
#define NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCONTROLLER_HPP

#include "Commands.h"
#include <UIPEthernet.h>

#define IP_SIZE 4

/**
 * @brief This class is used to receive commands over the ethernet interface via TCP, parses the command,
 * like switching rows and columns or receiving an identification string and sends a response back to the client.
 */
class EthernetController
{
public:
    EthernetController(const byte ip[IP_SIZE], uint16_t port);
    ~EthernetController();
    void Initialize();
    Command ReceiveMessage(int *row, int *column);
private:
    IPAddress *m_IP;
    EthernetServer *m_Server;
    uint8_t* m_Mac;
};
#endif //NANOSEC_CROSSBAR_CONTROLLER_ETHERNETCONTROLLER_HPP
