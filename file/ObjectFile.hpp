#include <fstream>
#include <string>

/**
 * ObjectFile represents the object file, which contains the raw machine code
 * of the instructions.
 */
class ObjectFile {
public:
    /**
     * Create object file, given its filename.
     */
    explicit ObjectFile(std::string const &filename);

    /**
     * Write this word of machine code to the object file.
     */
    void writeCode(uint16_t code);

private:
    std::ofstream out;
};