#include "Client.h"
#include <iostream>
#include "winsock_init.h"
#include <ctime>

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

Client::Client(const std::string& serverIp, int port)
    : serverIp(serverIp), serverPort(port), clientSocket(INVALID_SOCKET), running(true) {}

bool Client::connectToServer() {
    initializeWinsock();

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Could not create socket.\n";
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

    std::cout << "Connecting to server...\n";
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed.\n";
        closesocket(clientSocket);
        return false;
    }

    std::cout << "Connected to server.\n";
    return true;
}

bool Client::sendMessage(const std::string& messageContent) {
    if (send(clientSocket, messageContent.c_str(), messageContent.size(), 0) == SOCKET_ERROR) {
        std::cerr << "Send failed.\n";
        return false;
    }

    return true;
}

std::string Client::receiveMessage() {
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        return std::string(buffer);
    }
    return "";
}

void Client::disconnect() {
    running = false;
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
    }
#ifdef _WIN32
    WSACleanup();
#endif
}
