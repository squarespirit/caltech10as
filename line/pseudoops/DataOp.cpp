#include "DataOp.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"
#include <limits>

DataOp::DataOp(Symbol const &da) : dataAddress(da) {}

void DataOp::apply(Context &c) const {
    c.setCurDataAddress(dataAddress.resolve(c));
}

bool DataOp::operator==(const DataOp &other) const {
    return dataAddress == other.dataAddress;
}