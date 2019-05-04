#pragma once
#include <string>
#include <unordered_map>

#include "datatypes/Name.hpp"
#include "datatypes/Number.hpp"

/**
 * Context is the execution context of the assembler.
 * It represents label and constant names, and the current program and data
 * address.
 */
class Context {
public:
    /**
     * Create an context with empty symbol tables, and both program and data
     * address at 0.
     */
    Context();
    /**
     * Get the number of a label. Throw a NameExn if the label is not defined.
     */
    Number const &lookupLabel(Name const&) const;
    /**
     * Get the number of a constant. Throw a NameExn if the constant is not
     * defined.
     */
    Number const &lookupConstant(Name const&) const;
    /** Get current program address. */
    number_t getCurProgramAddress() const;
    /** Get current data address. */
    number_t getCurDataAddress() const;

    /**
     * Add label. Throw a NameExn if the label is already defined.
     */
    void addLabel(Name const&, Number const&);
    /**
     * Add constant. Throw a NameExn if the constant is already defined.
     */
    void addConstant(Name const&, Number const&);
    /**
     * Set current program address. Throw RangeExn if the new address is out
     * of range.
     */
    void setCurProgramAddress(number_t);
    /**
     * Set current data address. Throw RangeExn if the new address is out
     * of range.
     */
    void setCurDataAddress(number_t);

private:
    std::unordered_map<Name, Number> labelMap;
    std::unordered_map<Name, Number> constantMap;
    number_t curProgramAddress;
    number_t curDataAddress;
};