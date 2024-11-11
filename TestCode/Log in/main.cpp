#include <iostream>
#include <thread>
#include <cstdlib>

void displayMenu() {
    std::cout << "\n--- Message App CLI ---\n";
    std::cout << "1. Start Server and Client in separate windows\n";
    std::cout << "2. Exit\n";
    std::cout << "Please select an option: ";
}

// 用于启动服务器窗口的函数
void startServer() {
#ifdef _WIN32
    system("start cmd /k server.exe");  // Windows: 打开新的窗口运行 server.exe
#else
    system("xterm -hold -e ./server &");  // Linux/macOS: 在新终端运行 server
#endif
}

// 用于启动客户端窗口的函数
void startClient() {
#ifdef _WIN32
    system("start cmd /k client.exe");  // Windows: 打开新的窗口运行 client.exe
#else
    system("xterm -hold -e ./client &");  // Linux/macOS: 在新终端运行 client
#endif
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Starting server and client in separate windows...\n";

            // 创建线程启动服务器和客户端
            std::thread serverThread(startServer);
            std::thread clientThread(startClient);

            // 分离线程，使它们可以独立运行，而不会阻塞主程序
            serverThread.detach();
            clientThread.detach();

            std::cout << "Server and client started in separate windows.\n";
            std::cout << "You can close the server and client windows to return to this menu.\n";
            break;
        }
        case 2:
            std::cout << "Exiting program\n";
            return 0;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}
