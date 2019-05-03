#include "DataOp.hpp"
#include <limits>
#include "exceptions/RangeExn.hpp"
#include "exceptions/ParseExn.hpp"

DataOp::DataOp(Symbol da) : dataAddress(da) {
}

void DataOp::apply(Context &c) {
    c.setCurDataAddress(dataAddress.resolve(c));
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