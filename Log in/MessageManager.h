#pragma once
#include <vector>
#include "Message.h"

class MessageManager {
public:
    void sendMessage(const std::string& sender, const std::string& receiver, const std::string& content);
    void viewMessages(const std::string& user) const;
    void deleteMessages(const std::string& user);

private:
    std::vector<Message> messages;
};
