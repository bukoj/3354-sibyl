#include "winsock_init.h"
#ifdef _WIN32
#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#endif

void initializeWinsock() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock.\n";
        exit(1);
    }
#endif
}
