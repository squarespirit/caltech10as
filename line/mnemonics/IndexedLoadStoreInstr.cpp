#include "IndexedLoadStoreInstr.hpp"
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"

IndexedLoadStoreInstr::IndexedLoadStoreInstr(std::string const &opcode,
                                             IncDecRegister const &incDecReg,
                                             Symbol const &dataOffset)
    : Mnemonic(opcode), incDecReg(incDecReg), dataOffset(dataOffset) {}

/**
 * Map of opcode -> high 3 bits of instruction.
 */
const std::unordered_map<std::string, uint8_t> codeMap = {
    {"LD", 0b100}, {"ST", 0b101},
};

bool IndexedLoadStoreInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

std::unique_ptr<IndexedLoadStoreInstr>
IndexedLoadStoreInstr::parseOp(std::string const &opcode,
                               std::vector<std::string> const &operands) {
    if (!isValidOpcode(opcode)) {
        throw ParseExn("Invalid load/store opcode " + opcode);
    }
    if (operands.size() != 1) {
        throw ParseExn(opcode + " requires 1 operand (got " +
                       std::to_string(operands.size()) + ")");
    }
    std::string operand = operands[0];
    size_t commaIndex = operand.find(',');
    if (commaIndex == std::string::npos) {
        throw ParseExn(opcode + " operand " + operand +
                       " must be indexed (contain a ',')");
    }

    return std::make_unique<IndexedLoadStoreInstr>(
        opcode, IncDecRegister::parse(operand.substr(0, commaIndex)),
        Symbol::parse(operand.substr(commaIndex + 1)));
}

uint16_t IndexedLoadStoreInstr::encode(Context const &c) const {
    // isPost and isDec bits
    // Note: for LD/ST without increment/decrement, these two bits are 10.
    uint8_t incDecBits = 0b10;
    if (incDecReg.hasIncDec()) {
        incDecBits = (incDecReg.getIsPost() << 1) + incDecReg.getIsDec();
    }

    // Addressing mode is 10 for indexed with inc/dec, or 11 for regular
    // indexed
    uint8_t addrMode = 0b11;
    if (incDecReg.hasIncDec()) {
        addrMode = 0b10;
    }

    number_t offset = dataOffset.resolve(c);
    if (offset >= DATA_ADDRESS_SIZE) {
        throw RangeExn("Offset " + toHexString(offset) + " is too large");
    }

    return (codeMap.at(getOpcode()) << 13) + (incDecBits << 11) +
           (incDecReg.getRegister().getIsX() << 10) + (addrMode << 8) + offset;
}

bool IndexedLoadStoreInstr::
operator==(const IndexedLoadStoreInstr &other) const {
    return Mnemonic::operator==(other) && incDecReg == other.incDecReg &&
           dataOffset == other.dataOffset;
}
