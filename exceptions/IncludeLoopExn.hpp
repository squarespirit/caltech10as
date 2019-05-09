#pragma once
#include "AssemblyExn.hpp"
#include <string>

/**
 * IncludeLoopExn is thrown when there is a loop of file inclusions.
 */
class IncludeLoopExn : public AssemblyExn {
public:
    explicit IncludeLoopExn(std::string const &msg);
};