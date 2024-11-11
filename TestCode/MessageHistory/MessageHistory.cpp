#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include "Message.h"

void saveMessageToFile(const Message& message, const std::string& username, const std::string& otherUsername, const std::string& projectType) {
    // 构建 history 文件夹的路径
    std::string folderPath = projectType + "/history";

    // 检查文件夹是否存在，不存在则创建
    namespace fs = std::filesystem;
    fs::create_directories(folderPath);

    // 构建文件路径：history/username_to_otherUsername.txt
    std::ostringstream filename;
    filename << folderPath << "/" << username << "_to_" << otherUsername << ".txt";

    std::ofstream file(filename.str(), std::ios::app); // 以追加模式打开文件
    if (file.is_open()) {
        // 写入发送者、接收者和时间戳
        file << "Sender: " << message.sender << "\n";
        file << "Receiver: " << message.receiver << "\n";

        // 格式化并写入时间戳
        std::tm timeinfo;
        localtime_s(&timeinfo, &message.timestamp); // 使用线程安全的 localtime_s
        file << "Timestamp: " << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S") << "\n";

        // 写入消息内容
        file << "Message: " << message.content << "\n";
        file << "--------------------------\n"; // 分隔符

        file.close();
        std::cout << "Message saved successfully for chat between " << username << " and " << otherUsername << " in folder: " << folderPath << "\n";
    }
    else {
        std::cerr << "Unable to open file for saving message for chat between " << username << " and " << otherUsername << "\n";
    }
}
