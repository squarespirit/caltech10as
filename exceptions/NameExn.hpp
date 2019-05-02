#pragma once
#include <exception>
#include <string>

class NameExn : public std::exception {
public:
    NameExn(std::string msg);
    const char* what() const noexcept;
private:
    std::string msg;
};