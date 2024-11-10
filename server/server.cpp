#include "Server.h"
#include <iostream>
#include "winsock_init.h"
#include <ctime>

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

Server::Server(int port)
    : serverPort(port), serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET), running(true) {}

bool Server::start() {
    initializeWinsock();

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Could not create socket.\n";
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(serverPort);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(serverSocket);
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(serverSocket);
        return false;
    }

    std::cout << "Server is listening on port " << serverPort << "...\n";
    return true;
}

bool Server::acceptClient() {
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);

    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept connection.\n";
        closesocket(serverSocket);
        return false;
    }

    std::cout << "Client connected.\n";
    return true;
}

bool Server::sendMessage(const std::string& messageContent) {
    if (send(clientSocket, messageContent.c_str(), messageContent.size(), 0) == SOCKET_ERROR) {
        std::cerr << "Send failed.\n";
        return false;
    }

    return true;
}

std::string Server::receiveMessage() {
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        return std::string(buffer);
    }
    return "";
}

void Server::stop() {
    running = false;
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
    }
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
#ifdef _WIN32
    WSACleanup();
#endif
}
