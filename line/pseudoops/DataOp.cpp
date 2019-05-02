#include "DataOp.hpp"
#include <limits>
#include "datatypes/Addresses.hpp"
#include "exceptions/AddressRangeExn.hpp"
#include "exceptions/ParseExn.hpp"

DataOp::DataOp(Symbol da) : dataAddress(da) {
}

void DataOp::apply(Context &c) {
    number_t n = dataAddress.resolve(c);
    if (n < std::numeric_limits<data_address_t>::min() 
            || n > std::numeric_limits<data_address_t>::max()) {
        throw AddressRangeExn(".data address " + std::to_string(n) + " is outside data address space");
    }
    c.setCurDataAddress(n);
}

DataOp DataOp::parseOperation(std::string opcode, std::vector<std::string> const &operands) {
    if (opcode != ".data") {
        throw ParseExn(".data opcode was " + opcode);
    }
    if (operands.size() != 1) {
        throw ParseExn(".data must have one operand (got " + std::to_string(operands.size()) + ")");
    }
    return DataOp(Symbol::parse(operands[0]));
}

bool DataOp::operator==(const DataOp &other) const {
    return dataAddress == other.dataAddress;
}