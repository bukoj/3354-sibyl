#include <string>
#include <ctime>

struct Message {
    std::string sender;
    std::string receiver;
    std::string content;
    std::time_t timestamp;
};
