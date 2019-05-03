#include "DataOp.hpp"
#include <limits>
#include "exceptions/RangeExn.hpp"
#include "exceptions/ParseExn.hpp"

DataOp::DataOp(Symbol da) : dataAddress(da) {
}

void DataOp::apply(Context &c) {
    c.setCurDataAddress(dataAddress.resolve(c));
}

bool DataOp::operator==(const DataOp &other) const {
    return dataAddress == other.dataAddress;
}