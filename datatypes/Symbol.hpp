#pragma once
#include <optional>

#include "Name.hpp"
#include "Number.hpp"
#include "context/Context.hpp"

/**
 * A symbol is either a number or the name of a constant (that stores a
 * number).
 * Given a context, which contains a mapping of constant names, a Symbol can
 * be definitively resolved to a number.
 */
class Symbol {
public:
    /**
     * Create a symbol that represents a name.
     */
    explicit Symbol(Name const &name);

    /**
     * Create a symbol that represents a number.
     */
    explicit Symbol(Number const &number);

    /**
     * Convert a string to a symbol. Throw a ParseExn if the string cannot
     * be converted.
     * If the string starts with $, the portion after the $ is parsed as a
     * constant. Otherwise, it is parsed as a number.
     * Leading or trailing whitespace is not tolerated.
     */
    static Symbol parse(std::string const &);

    /**
     * Resolve the symbol to a number. If it is a literal Number, return
     * its value. Otherwise, if it is a Name, look it up in the context.
     */
    number_t resolve(const Context &) const;

    bool operator==(const Symbol &) const;

private:
    bool isName;
    /*
     * Using a union is a headache because Name is not a "trivial" datatype.
     * It contains a string, which manages an array of chars...
     * Instead, set the unused type to a dummy value.
     */
    Name name;
    Number number;
};