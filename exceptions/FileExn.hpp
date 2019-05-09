#pragma once
#include "AssemblyExn.hpp"
#include <string>

/**
 * FileExn is an exception that indicates failure to open a file.
 */
class FileExn : public AssemblyExn {
public:
    explicit FileExn(std::string const &msg);
};