#include "Client.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <vector>

std::atomic<bool> running(true);
std::vector<std::string> messages;

void printChatInterface() {
    system("cls");
    for (const auto& msg : messages) {
        std::cout << msg << "\n";
    }
    std::cout << "\nEnter message: ";
    std::cout.flush();
}

void receiveMessages(Client& client) {
    while (running) {
        std::string receivedMessage = client.receiveMessage();
        if (receivedMessage == "exit" || receivedMessage.empty()) {
            messages.push_back("Server disconnected or requested to exit.");
            running = false;
            printChatInterface();
            break;
        }
        messages.push_back("Server: " + receivedMessage);
        printChatInterface();
    }
}

void sendMessages(Client& client) {
    while (running) {
        printChatInterface();
        std::string message;
        std::getline(std::cin, message);

        if (message == "exit") {
            client.sendMessage("exit");
            running = false;
            break;
        }

        if (!client.sendMessage(message)) {
            messages.push_back("Failed to send message.");
            running = false;
            printChatInterface();
            break;
        }

        messages.push_back("You: " + message);
    }
}

int main() {
    Client client("127.0.0.1", 8080);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server.\n";
        return 1;
    }

    messages.push_back("Connected to server. You can now send and receive messages freely.");
    printChatInterface();

    std::thread receiverThread(receiveMessages, std::ref(client));
    std::thread senderThread(sendMessages, std::ref(client));

    receiverThread.join();
    senderThread.join();

    client.disconnect();
    return 0;
}
