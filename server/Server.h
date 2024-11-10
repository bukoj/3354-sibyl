#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:

    Server(int port);

    bool start();
    bool acceptClient();
    bool sendMessage(const std::string& messageContent);
    std::string receiveMessage();
    void stop();

private:
    int serverPort;
    int serverSocket;
    int clientSocket;
    bool running;
    std::string username;
    std::string clientUsername;
};

#endif // SERVER_H
