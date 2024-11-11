#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 8080

void clientFunction() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    SOCKET client_fd;
    struct sockaddr_in server_address;
    char buffer[1024] = { 0 };

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid address.\n";
        closesocket(client_fd);
        WSACleanup();
        return;
    }

    if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection failed.\n";
        closesocket(client_fd);
        WSACleanup();
        return;
    }

    std::cout << "Connected to the server. You can start chatting:\n";

    while (true) {
        std::string message;
        std::getline(std::cin, message);
        send(client_fd, message.c_str(), message.length(), 0);

        memset(buffer, 0, sizeof(buffer));
        int valread = recv(client_fd, buffer, 1024, 0);
        if (valread > 0) {
            std::cout << "Server: " << buffer << "\n";
        }
        else if (valread == 0) {
            std::cout << "Server disconnected.\n";
            break;
        }
        else {
            std::cerr << "recv failed.\n";
            break;
        }
    }

    closesocket(client_fd);
    WSACleanup();
}

int main() {
    clientFunction();
    return 0;
}
