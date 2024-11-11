#include "Message.h"

Message::Message(const std::string& sender, const std::string& receiver, const std::string& content)
    : sender(sender), receiver(receiver), content(content) {
    timestamp = std::time(nullptr);
}

std::string Message::getSender() const { return sender; }
std::string Message::getReceiver() const { return receiver; }
std::string Message::getContent() const { return content; }
std::time_t Message::getTimeStamp() const { return timestamp; }
