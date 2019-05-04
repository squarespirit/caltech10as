#include "Symbol.hpp"

#include <stdexcept>

#include "exceptions/ParseExn.hpp"

Symbol::Symbol(std::optional<Name> const &name, std::optional<Number> const &number) {
    if (bool(name) == bool(number)) {
        // That is, both are undefined or both are defined
        throw std::invalid_argument("Exactly one of name and number must be defined");
    }

    this->name = name;
    this->number = number;
}

Symbol Symbol::parse(std::string const &s) {
    if (s.length() == 0) {
        throw ParseExn("Cannot parse empty symbol");
    }

    if (s[0] == '$') {
        return Symbol(Name(s.substr(1)), std::nullopt);
    }

    return Symbol(std::nullopt, Number(s));
}

number_t Symbol::resolve(Context const &c) const {
    if (bool(name)) {
        return c.lookupConstant(*name).getNumber();
    }
    return number->getNumber();
}

bool Symbol::operator==(const Symbol &other) const {
    return this->name == other.name && this->number == other.number;
}
