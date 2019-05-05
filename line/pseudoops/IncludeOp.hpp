#pragma once
#include "PseudoOp.hpp"
#include <memory>
#include <vector>

/**
 * IncludeOp is a directive to read instructions from another assembly file.
 */
class IncludeOp : public PseudoOp {
public:
    /**
     * Construct an IncludeOp with the given filename.
     */
    explicit IncludeOp(std::string const &f);

    /**
     * IncludeOp should not be applied to a context, so this throws an error.
     */
    void apply(Context &c);

    /**
     * Convert the given opcode and operands to a IncludeOp.
     * The only operand should be the filename.
     * Throw a ParseExn if the operation cannot be converted.
     */
    static std::unique_ptr<IncludeOp>
    parseOp(std::string const &opcode,
            std::vector<std::string> const &operands);

    bool operator==(const IncludeOp &) const;

private:
    std::string filename;
};
