#pragma once
#include <exception>
#include <string>

/**
 * AddressRangeExn is an exception that indicates an address is out of range
 * of an address space.
 */
class AddressRangeExn : public std::exception {
public:
    AddressRangeExn(std::string msg);
    const char* what() const noexcept;
private:
    std::string msg;
};