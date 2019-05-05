#include "ALUDataInstr.hpp"
#include <unordered_map>
#include "exceptions/ParseExn.hpp"
#include "exceptions/RangeExn.hpp"

ALUDataInstr::ALUDataInstr(std::string const &opcode, Symbol const &da)
    : Mnemonic(opcode), reg(std::nullopt), dataAddress(da) {}

ALUDataInstr::ALUDataInstr(std::string const &opcode, Register const &reg,
    Symbol const &da) : Mnemonic(opcode), reg(reg), dataAddress(da) {}


/**
 * Map of opcode -> first 6 bits of ALU instruction.
 */
const std::unordered_map<std::string, uint8_t> codeMap = {
    {"ADC", 0b011000},
    {"ADD", 0b011010},
    {"AND", 0b010001},
    {"CMP", 0b001100},
    {"OR",  0b011101},
    {"SBB", 0b000110},
    {"SUB", 0b000100},
    {"TST", 0b010011},
    {"XOR", 0b001101}
};

bool ALUDataInstr::isValidOpcode(std::string const &opcode) {
    return codeMap.find(opcode) != codeMap.end();
}

std::unique_ptr<ALUDataInstr> ALUDataInstr::parseOp(
        std::string const &opcode, std::vector<std::string> const &operands) {
    if (!isValidOpcode(opcode)) {
        throw ParseExn("Unknown opcode " + opcode 
                       + " for ALU data instruction");
    }
    if (operands.size() != 1) {
        throw ParseExn(opcode + " requires 1 operand (got " 
                       + std::to_string(operands.size()) + ")");
    }
    std::string const &operand = operands[0];
    
    size_t commaIndex = operand.find(',');
    if (commaIndex == std::string::npos) {
        // No register, direct addressing
        return std::make_unique<ALUDataInstr>(opcode, Symbol::parse(operand));
    }
    // Indexed addressing
    return std::make_unique<ALUDataInstr>(
        opcode,
        Register::parse(operand.substr(0, commaIndex)),
        Symbol::parse(operand.substr(commaIndex + 1))
    );
}

uint16_t ALUDataInstr::encode(Context const &c) {
    uint8_t addressMode = 0; // Direct addressing
    if (bool(reg)) {
        if (reg->getIsX()) {
            addressMode = 0b01; // X-indexed
        } else {
            addressMode = 0b10; // S-indexed
        }
    }
    number_t address = dataAddress.resolve(c);
    if (address >= DATA_ADDRESS_SIZE) {
        throw RangeExn("Data address " + toHexString(address) + " out of range");
    }

    return (codeMap.at(getOpcode()) << 10) + (addressMode << 8) + address;
}

bool ALUDataInstr::operator==(ALUDataInstr const &other) const {
    return Mnemonic::operator==(other) && reg == other.reg 
            && dataAddress == other.dataAddress;
}
