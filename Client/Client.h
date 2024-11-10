// Client.h

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <atomic>

#ifdef _WIN32
#include <winsock2.h>
#endif

class Client {
public:
    Client(const std::string& serverIp, int port);

    bool connectToServer();
    bool sendMessage(const std::string& message);
    std::string receiveMessage();
    void disconnect();

private:
    std::string serverIp;
    int serverPort;
    SOCKET clientSocket;
    std::atomic<bool> running;
    std::string username;
    std::string serverUsername;
};

#endif
