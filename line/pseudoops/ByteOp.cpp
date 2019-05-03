#include "ByteOp.hpp"
#include "datatypes/NumberTypes.hpp"
#include "exceptions/RangeExn.hpp"

ByteOp::ByteOp(Symbol val) : dataValue(val) {
}

void ByteOp::apply(Context &c) {
    number_t n = dataValue.resolve(c);
    if (n >= DATA_VALUE_SIZE) {
        throw RangeExn("Data value " + toHexString(n) + " is out of range");
    }
    // Advance data address
    c.setCurDataAddress((c.getCurDataAddress() + 1) % DATA_ADDRESS_SIZE);
}