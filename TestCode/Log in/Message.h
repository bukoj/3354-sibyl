#pragma once
#include <string>
#include <ctime>

class Message {
public:
    Message(const std::string& sender, const std::string& receiver, const std::string& content);

    std::string getSender() const;
    std::string getReceiver() const;
    std::string getContent() const;
    std::time_t getTimeStamp() const;

private:
    std::string sender;
    std::string receiver;
    std::string content;
    std::time_t timestamp;
};
