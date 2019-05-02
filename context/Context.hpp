#pragma once
#include <string>
#include <unordered_map>

#include "datatypes/Addresses.hpp"
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
     * Create an empty context.
     */
    Context();
    /**
     * Get the number of a label. Throw a NameExn if the label is not defined.
     */
    Number lookupLabel(Name);
    /**
     * Get the number of a constant. Throw a NameExn if the constant is not
     * defined.
     */
    Number lookupConstant(Name);
    program_address_t getCurProgramAddress();
    data_address_t getCurDataAddress();
    /**
     * Add label. Throw a NameExn if the label is already defined.
     */
    void addLabel(Name, Number);
    /**
     * Add constant. Throw a NameExn if the constant is already defined.
     */
    void addConstant(Name, Number);
    void setCurProgramAddress(program_address_t);
    void setCurDataAddress(data_address_t);

private:
    std::unordered_map<Name, Number> labelMap;
    std::unordered_map<Name, Number> constantMap;
    program_address_t curProgramAddress;
    data_address_t curDataAddress;
};