#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include "Message.h"

void saveMessageToFile(const Message& message, const std::string& username, const std::string& otherUsername, const std::string& projectType) {
    // ���� history �ļ��е�·��
    std::string folderPath = projectType + "/history";

    // ����ļ����Ƿ���ڣ��������򴴽�
    namespace fs = std::filesystem;
    fs::create_directories(folderPath);

    // �����ļ�·����history/username_to_otherUsername.txt
    std::ostringstream filename;
    filename << folderPath << "/" << username << "_to_" << otherUsername << ".txt";

    std::ofstream file(filename.str(), std::ios::app); // ��׷��ģʽ���ļ�
    if (file.is_open()) {
        // д�뷢���ߡ������ߺ�ʱ���
        file << "Sender: " << message.sender << "\n";
        file << "Receiver: " << message.receiver << "\n";

        // ��ʽ����д��ʱ���
        std::tm timeinfo;
        localtime_s(&timeinfo, &message.timestamp); // ʹ���̰߳�ȫ�� localtime_s
        file << "Timestamp: " << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S") << "\n";

        // д����Ϣ����
        file << "Message: " << message.content << "\n";
        file << "--------------------------\n"; // �ָ���

        file.close();
        std::cout << "Message saved successfully for chat between " << username << " and " << otherUsername << " in folder: " << folderPath << "\n";
    }
    else {
        std::cerr << "Unable to open file for saving message for chat between " << username << " and " << otherUsername << "\n";
    }
}
