#include "Context.hpp"
#include <stdexcept>
#include "exceptions/NameExn.hpp"

Context::Context() {
    labelMap = std::unordered_map<Name, Number>();
    constantMap = std::unordered_map<Name, Number>();
    curProgramAddress = 0;
    curDataAddress = 0;
}

Number Context::lookupLabel(Name name) {
    try {
        return labelMap.at(name);
    } catch (std::out_of_range) {
        throw NameExn("Label " + name.getName() + " is not defined");
    }
}

Number Context::lookupConstant(Name name) {
    try {
        return constantMap.at(name);
    } catch (std::out_of_range) {
        throw NameExn("Constant " + name.getName() + " is not defined");
    }
}

program_address_t Context::getCurProgramAddress() {
    return curProgramAddress;
}

data_address_t Context::getCurDataAddress() {
    return curDataAddress;
}

void Context::addLabel(Name name, Number number) {
    if (!labelMap.insert({name, number}).second) {
        throw NameExn("Label " + name.getName() + " is already defined");
    }
}

void Context::addConstant(Name name, Number number) {
    if (!constantMap.insert({name, number}).second) {
        throw NameExn("Constant " + name.getName() + " is already defined");
    }
}

void Context::setCurProgramAddress(program_address_t p) {
    curProgramAddress = p;
}

void Context::setCurDataAddress(data_address_t d) {
    curDataAddress = d;
}

