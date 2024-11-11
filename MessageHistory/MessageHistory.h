#ifndef MESSAGE_HISTORY_H
#define MESSAGE_HISTORY_H

#include "Message.h"
#include <vector>
#include <string>

void saveMessageToFile(const Message& message, const std::string& username, const std::string& otherUsername, const std::string& projectType);
std::vector<Message> loadMessageHistory(const std::string& filename);
void viewMessages(const std::vector<Message>& messages);
void saveMessageToFile(const Message& message, const std::string& filename);

#endif // MESSAGE_HISTORY_H
