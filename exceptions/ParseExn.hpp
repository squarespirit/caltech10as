#pragma once
#include <exception>
#include <string>

class ParseExn : public std::exception {
public:
    ParseExn(std::string msg);
    const char* what() const noexcept;
private:
    std::string msg;
};