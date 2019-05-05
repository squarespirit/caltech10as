#include "Context.hpp"
#include "exceptions/NameExn.hpp"
#include "exceptions/RangeExn.hpp"
#include <stdexcept>

Context::Context()
    : labelMap(), constantMap(), curProgramAddress(0), curDataAddress(0) {}

Number const &Context::lookupLabel(Name const &name) const {
    try {
        return labelMap.at(name);
    } catch (std::out_of_range) {
        throw NameExn("Label " + name.getName() + " is not defined");
    }
}

Number const &Context::lookupConstant(Name const &name) const {
    try {
        return constantMap.at(name);
    } catch (std::out_of_range) {
        throw NameExn("Constant " + name.getName() + " is not defined");
    }
}

number_t Context::getCurProgramAddress() const { return curProgramAddress; }

number_t Context::getCurDataAddress() const { return curDataAddress; }

void Context::addLabel(Name const &name, Number const &number) {
    if (!labelMap.insert({name, number}).second) {
        throw NameExn("Label " + name.getName() + " is already defined");
    }
}

void Context::addConstant(Name const &name, Number const &number) {
    if (!constantMap.insert({name, number}).second) {
        throw NameExn("Constant " + name.getName() + " is already defined");
    }
}

void Context::setCurProgramAddress(number_t p) {
    if (p >= PROGRAM_ADDRESS_SIZE) {
        throw RangeExn("Program address " + toHexString(p) + " out of range");
    }
    curProgramAddress = p;
}

void Context::setCurDataAddress(number_t d) {
    if (d >= DATA_ADDRESS_SIZE) {
        throw RangeExn("Data address " + toHexString(d) + " out of range");
    }
    curDataAddress = d;
}
