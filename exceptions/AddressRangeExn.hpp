#pragma once
#include <stdexcept>
#include <string>

/**
 * AddressRangeExn is an exception that indicates an address is out of range
 * of an address space.
 */
class AddressRangeExn : public std::runtime_error {
public:
    AddressRangeExn(std::string msg);
};