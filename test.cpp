#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include <thread>
#include <chrono>
#include "Client.h"
#include "Server.h"
#include <atomic>
#include <iostream>

extern std::atomic<bool> running;

TEST_CASE("Client-Server Communication with Detailed Dialogue", "[network]") {
    running = true;

    std::thread serverThread([]() {
        Server server(8080);
        REQUIRE(server.start());
        REQUIRE(server.acceptClient());

        std::string clientMessage;

        // First dialogue: user1 greets user2
        clientMessage = server.receiveMessage();
        INFO("user2 received message: " << clientMessage);
        REQUIRE(clientMessage == "Hello, user2! This is user1.");
        std::cout << "user2 received: " << clientMessage << " (Receive Successful)\n";

        server.sendMessage("Hello, user1! How are you?");
        std::cout << "user2 sent: Hello, user1! How are you? (Send Successful)\n";

        // Second dialogue: user1 responds
        clientMessage = server.receiveMessage();
        INFO("user2 received message: " << clientMessage);
        REQUIRE(clientMessage == "I'm good, user2! What about you?");
        std::cout << "user2 received: " << clientMessage << " (Receive Successful)\n";

        server.sendMessage("I'm doing well too! Nice to chat with you.");
        std::cout << "user2 sent: I'm doing well too! Nice to chat with you. (Send Successful)\n";

        // Third dialogue: user1 ends the conversation
        clientMessage = server.receiveMessage();
        INFO("user2 received message: " << clientMessage);
        REQUIRE(clientMessage == "Great to hear, user2! Let's catch up again soon.");
        std::cout << "user2 received: " << clientMessage << " (Receive Successful)\n";

        server.sendMessage("Sure thing! Take care, user1!");
        std::cout << "user2 sent: Sure thing! Take care, user1! (Send Successful)\n";

        running = false;
        });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    Client client("127.0.0.1", 8080);
    REQUIRE(client.connectToServer());

    SECTION("Send and Receive Messages in a Dialogue") {
        // First dialogue: user1 greets user2
        std::cout << "user1: Sending greeting to user2.\n";
        REQUIRE(client.sendMessage("Hello, user2! This is user1."));
        std::cout << "user1 sent: Hello, user2! This is user1. (Send Successful)\n";

        std::string serverMessage = client.receiveMessage();
        INFO("user1 received message: " << serverMessage);
        REQUIRE(serverMessage == "Hello, user1! How are you?");
        std::cout << "user1 received: " << serverMessage << " (Receive Successful)\n\n";

        // Second dialogue: user1 responds
        std::cout << "user1: Responding to user2.\n";
        REQUIRE(client.sendMessage("I'm good, user2! What about you?"));
        std::cout << "user1 sent: I'm good, user2! What about you? (Send Successful)\n";

        serverMessage = client.receiveMessage();
        INFO("user1 received message: " << serverMessage);
        REQUIRE(serverMessage == "I'm doing well too! Nice to chat with you.");
        std::cout << "user1 received: " << serverMessage << " (Receive Successful)\n\n";

        // Third dialogue: user1 ends the conversation
        std::cout << "user1: Ending conversation with user2.\n";
        REQUIRE(client.sendMessage("Great to hear, user2! Let's catch up again soon."));
        std::cout << "user1 sent: Great to hear, user2! Let's catch up again soon. (Send Successful)\n";

        serverMessage = client.receiveMessage();
        INFO("user1 received message: " << serverMessage);
        REQUIRE(serverMessage == "Sure thing! Take care, user1!");
        std::cout << "user1 received: " << serverMessage << " (Receive Successful)\n";
    }

    client.sendMessage("exit");
    client.disconnect();

    serverThread.join();
}
