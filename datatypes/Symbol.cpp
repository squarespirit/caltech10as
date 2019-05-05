#include "Symbol.hpp"

#include <stdexcept>

#include "exceptions/ParseExn.hpp"

Symbol::Symbol(Name const &name) : isName(true), name(name), number(0) {}

Symbol::Symbol(Number const &number)
    : isName(false), name("_"), number(number) {}

Symbol Symbol::parse(std::string const &s) {
    if (s.length() == 0) {
        throw ParseExn("Cannot parse empty symbol");
    }

    if (s[0] == '$') {
        return Symbol(Name(s.substr(1)));
    }

    return Symbol(Number(s));
}

number_t Symbol::resolve(Context const &c) const {
    if (isName) {
        return c.lookupConstant(name).getNumber();
    }
    return number.getNumber();
}

bool Symbol::operator==(const Symbol &other) const {
    if (isName != other.isName) {
        return false;
    }
    if (isName) {
        return name == other.name;
    }
    return number == other.number;
}
