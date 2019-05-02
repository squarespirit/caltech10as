#pragma once
#include <string>

class Name {
public:
    Name(std::string name);
    std::string getName();
private:
    std::string name;
};