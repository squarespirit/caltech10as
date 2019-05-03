#pragma once
#include <stdexcept>
#include <string>

class NameExn : public std::runtime_error {
public:
    NameExn(std::string msg);
};