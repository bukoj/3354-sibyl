#pragma once
#include <string>

class User {
public:
    User(const std::string& username, const std::string& password);

    std::string getUsername() const;
    bool authenticate(const std::string& password) const;

private:
    std::string username;
    std::string password;
};
