#pragma once
#include <string>
#include "AssemblyExn.hpp"

/**
 * NameExn is thrown when a name does not exist, or one attempts to define
 * a name that already exists.
 */
class NameExn : public AssemblyExn {
public:
    explicit NameExn(std::string const &msg);
};