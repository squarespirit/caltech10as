#pragma once
#include <stdexcept>
#include <string>

class ParseExn : public std::runtime_error {
public:
    ParseExn(std::string msg);
};