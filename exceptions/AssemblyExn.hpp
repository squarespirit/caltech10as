#pragma once
#include <stdexcept>
#include <string>

/**
 * AssemblyExn is the superclass for all runtime exceptions in the assembler.
 */
class AssemblyExn : public std::runtime_error {
public:
    explicit AssemblyExn(std::string const &msg);
};