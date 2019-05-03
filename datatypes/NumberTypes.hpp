#include <cstdint>
#include <string>

/** The type of numbers used internally by the assembler. */
typedef uint16_t number_t;

/** 1 more than the maximum program address. */
#define PROGRAM_ADDRESS_SIZE 0x2000

/** 1 more than the maximum data address. */
#define DATA_ADDRESS_SIZE 0x100

/** 1 more than the maximum value of a data word. */
#define DATA_VALUE_SIZE 0x100

/**
 * Convert a number to a hex string.
 */
std::string toHexString(number_t);