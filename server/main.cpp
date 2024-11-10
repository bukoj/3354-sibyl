#include "Server.h"
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

void receiveMessages(Server& server) {
    while (running) {
        std::string receivedMessage = server.receiveMessage();
        if (receivedMessage == "exit" || receivedMessage.empty()) {
            messages.push_back("Client disconnected or requested to exit.");
            running = false;
            printChatInterface();
            break;
        }
        messages.push_back("Client: " + receivedMessage);
        printChatInterface();
    }
}

void sendMessages(Server& server) {
    while (running) {
        printChatInterface();
        std::string message;
        std::getline(std::cin, message);

        if (message == "exit") {
            server.sendMessage("exit");
            running = false;
            break;
        }

        if (!server.sendMessage(message)) {
            messages.push_back("Failed to send message.");
            running = false;
            printChatInterface();
            break;
        }

        messages.push_back("You: " + message);
    }
}

int main() {
    //std::string username;
    //std::cout << "Enter your username: ";
    //std::getline(std::cin, username);

    Server server(8080);

    if (!server.start()) {
        std::cerr << "Server failed to start.\n";
        return 1;
    }

    if (!server.acceptClient()) {
        std::cerr << "Failed to accept client.\n";
        server.stop();
        return 1;
    }

    messages.push_back("Client connected. You can now send and receive messages freely.");
    printChatInterface();

    std::thread receiverThread(receiveMessages, std::ref(server));
    std::thread senderThread(sendMessages, std::ref(server));

    receiverThread.join();
    senderThread.join();

    server.stop();
    return 0;
}
