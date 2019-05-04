#include "IncDecRegister.hpp"
#include <stdexcept>
#include "exceptions/ParseExn.hpp"

IncDecRegister::IncDecRegister(Register reg)
    : reg(reg), incDec(false), isDec(false), isPost(false) {}

IncDecRegister::IncDecRegister(Register reg, bool isDec, bool isPost) 
    : reg(reg), incDec(true), isDec(isDec), isPost(isPost) {}

Register const &IncDecRegister::getRegister() {
    return reg;
}

bool IncDecRegister::hasIncDec() {
    return incDec;
}

bool IncDecRegister::getIsDec() {
    if (!incDec) {
        throw std::logic_error("Register is not incremented/decremented");
    }
    return isDec;
}

bool IncDecRegister::getIsPost() {
    if (!incDec) {
        throw std::logic_error("Register is not incremented/decremented");
    }
    return isPost;
}

IncDecRegister IncDecRegister::parse(std::string s) {
    if (s.length() == 0) {
        throw ParseExn("Empty register spec");
    }
    if (s.length() == 1) {
        // Register without increment/decrement
        return IncDecRegister(Register::parse(s));
    }
    if (s.length() == 2) {
        // Register with increment/decrement
        if (s[0] == '+' || s[0] == '-') {
            // Pre
            return IncDecRegister(
                Register::parse(s.substr(1, 1)),
                s[0] == '-',
                false
            );
        } else if (s[1] == '+' || s[1] == '-') {
            // Post
            return IncDecRegister(
                Register::parse(s.substr(0, 1)),
                s[1] == '-',
                true
            );
        } else {
            throw ParseExn("Expected +/- in register spec " + s);
        }
    }
    throw ParseExn("Too many characters in register spec " + s);
}

bool IncDecRegister::operator==(const IncDecRegister& other) const {
    bool res = reg == other.reg && incDec == other.incDec;
    if (incDec) {
        res &= isDec == other.isDec && isPost == other.isPost;
    }
    return res;
}
