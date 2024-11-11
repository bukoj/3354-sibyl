#include <iostream>
#include <thread>
#include <cstdlib>

void displayMenu() {
    std::cout << "\n--- Message App CLI ---\n";
    std::cout << "1. Start Server and Client in separate windows\n";
    std::cout << "2. Exit\n";
    std::cout << "Please select an option: ";
}

// �����������������ڵĺ���
void startServer() {
#ifdef _WIN32
    system("start cmd /k server.exe");  // Windows: ���µĴ������� server.exe
#else
    system("xterm -hold -e ./server &");  // Linux/macOS: �����ն����� server
#endif
}

// ���������ͻ��˴��ڵĺ���
void startClient() {
#ifdef _WIN32
    system("start cmd /k client.exe");  // Windows: ���µĴ������� client.exe
#else
    system("xterm -hold -e ./client &");  // Linux/macOS: �����ն����� client
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

            // �����߳������������Ϳͻ���
            std::thread serverThread(startServer);
            std::thread clientThread(startClient);

            // �����̣߳�ʹ���ǿ��Զ������У�����������������
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
