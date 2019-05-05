#include "LabelDef.hpp"
#include "exceptions/ParseExn.hpp"

LabelDef::LabelDef(Name const &name) : name(name) {}

LabelDef LabelDef::parse(std::string s) {
    if (s.length() == 0) {
        throw ParseExn("Cannot parse empty label");
    }

    if (s[s.length() - 1] != ':') {
        throw ParseExn("Label definition " + s + " does not end in ':'");
    }

    return LabelDef(Name(s.substr(0, s.length() - 1)));
}

void LabelDef::apply(Context &c) {
    c.addLabel(name, Number(c.getCurProgramAddress()));
}

bool LabelDef::operator==(const LabelDef &other) const {
    return name == other.name;
}
