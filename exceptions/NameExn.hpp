#pragma once
#include <stdexcept>
#include <string>

/**
 * NameExn is thrown when a name does not exist, or one attempts to define
 * a name that already exists.
 */
class NameExn : public std::runtime_error {
public:
    NameExn(std::string msg);
};