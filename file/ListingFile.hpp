#include "datatypes/NumberTypes.hpp"
#include <fstream>
#include <string>

/**
 * ListingFile represents the listing file, which has one line per line of
 * assembly language source. The machine code translation is next to
 * each line, which makes it easy to inspect the assembly.
 */
class ListingFile {
public:
    /**
     * Create listing file object, given its filename.
     */
    explicit ListingFile(std::string const &filename);

    /**
     * Add a line to the listing file that corresponds to the given line of
     * source.
     */
    void writeLine(std::string const &source);

    /**
     * Add a line to the listing file that corresponds to the given line of
     * source. The source also encodes at the given program address to the
     * given machine code.
     */
    void writeLine(number_t programAddress, uint16_t code,
                   std::string const &source);

private:
    std::ofstream out;
};