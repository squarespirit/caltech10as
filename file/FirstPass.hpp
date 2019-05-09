#pragma once
#include "FilePass.hpp"

/**
 * The first pass over an assembly file, when labels and constants are defined.
 */
class FirstPass : public FilePass {
public:
    /**
     * Construct a FirstPass, given the context to modify in-place.
     */
    explicit FirstPass(Context &context);

    /**
     * Process a line.
     * Add labels and constants to the context.
     */
    void processLine(std::string const &orig, Line const &line) override;

private:
    Context &context;
};