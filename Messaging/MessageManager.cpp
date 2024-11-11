#include "MessageManager.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS  // 忽略安全警告

void MessageManager::sendMessage(const std::string& sender, const std::string& receiver, const std::string& content) {
    messages.emplace_back(sender, receiver, content);
}

void MessageManager::viewMessages(const std::string& user) const {
    for (const auto& msg : messages) {
        if (msg.getReceiver() == user || msg.getSender() == user) {
            char timeStr[26];
            std::time_t timestamp = msg.getTimeStamp(); // 使用一个临时变量存储时间戳
            ctime_s(timeStr, sizeof(timeStr), &timestamp); // 传递变量的地址
            std::cout << "From: " << msg.getSender() << " To: " << msg.getReceiver()
                << " Message: " << msg.getContent() << " Time: " << timeStr << "\n";
        }
    }
}

void MessageManager::deleteMessages(const std::string& user) {
    messages.erase(std::remove_if(messages.begin(), messages.end(),
        [&user](const Message& msg) {
            return msg.getReceiver() == user || msg.getSender() == user;
        }),
        messages.end());
}
