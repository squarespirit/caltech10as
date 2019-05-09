#pragma once
#include "line/Line.hpp"

/**
 * FilePass is an interface for what to do with each line of assembly
 * during a pass over the assembly file.
 */
class FilePass {
public:
    /**
     * Process a line of assembly.
     * orig is the original line.
     * line is a reference to the parsed line.
     */
    virtual void processLine(std::string const &orig, Line const &line) = 0;
};