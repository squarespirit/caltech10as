#include "FilePass.hpp"
#include "ListingFile.hpp"
#include "ObjectFile.hpp"

/**
 * The second pass over an assembly file, when each instruction is encoded
 * and the object and listing files are produced.
 */
class SecondPass : public FilePass {
public:
    /**
     * Construct a SecondPass.
     * context is the current context.
     * objectFile and listingFile are the output files to write to.
     */
    SecondPass(Context &context, ObjectFile &objectFile,
               ListingFile &listingFile);

    /**
     * Process a line.
     * If the line contains an instruction, convert to machine code. Then write
     * the line to both the object and listing files.
     */
    void processLine(std::string const &orig, Line const &line) override;

private:
    Context &context;
    ObjectFile &objectFile;
    ListingFile &listingFile;
};