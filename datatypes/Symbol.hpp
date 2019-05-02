#pragma once
#include <optional>

#include "Name.hpp"
#include "Number.hpp"
#include "context/Context.hpp"

/**
 * A symbol is either a number or the name of a constant (that stores a
 * number).
 */
class Symbol {
public:
    /**
     * Create a symbol from a name and a number. Exactly one has to exist.
     */
    Symbol(std::optional<Name> name, std::optional<Number> number);

    /**
     * Convert a string to a symbol. Throw a ParseExn if the string cannot
     * be converted.
     * If the string starts with $, the portion after the $ is parsed as a
     * constant. Otherwise, it is parsed as a number.
     * Leading or trailing whitespace is not tolerated.
     */
    static Symbol parse(std::string);

    /**
     * Resolve the symbol to a number. If it is a literal Number, return
     * its value. Otherwise, if it is a Name, look it up in the context.
     */
    number_t resolve(Context);

    bool operator==(const Symbol&) const;

private:
    std::optional<Name> name;
    std::optional<Number> number;
};