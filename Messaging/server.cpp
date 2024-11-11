#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 8080

void serverFunction() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    std::cout << "Server is listening on port " << PORT << "\nWaiting for a client to connect...\n";

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) == INVALID_SOCKET) {
        std::cerr << "Accept failed.\n";
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    std::cout << "Client connected. You can start chatting:\n";

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = recv(new_socket, buffer, 1024, 0);
        if (valread > 0) {
            std::cout << "Client: " << buffer << "\n";
        }
        else if (valread == 0) {
            std::cout << "Client disconnected.\n";
            break;
        }
        else {
            std::cerr << "recv failed.\n";
            break;
        }

        std::string message;
        std::getline(std::cin, message);
        send(new_socket, message.c_str(), message.length(), 0);
    }

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
}

int main() {
    serverFunction();
    return 0;
}
