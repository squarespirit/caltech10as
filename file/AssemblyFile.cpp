#include "AssemblyFile.hpp"
#include "FileUtil.hpp"
#include "exceptions/IncludeLoopExn.hpp"
#include "line/pseudoops/IncludeOp.hpp"
#include <iostream>
#include <stdexcept>

AssemblyFile::AssemblyFile(std::string const &filename) : filename(filename) {}

int AssemblyFile::doPass(FilePass &filePass) {
    std::vector<std::string> includes;
    return doPassRec(filePass, includes);
}

/**
 * Print a message for the given filename, line number, and error.
 */
void printErrorMessage(std::string const &filename, size_t row,
                       AssemblyExn const &e) {
    std::cerr << "Error: " << filename << ":" << row << ": " << e.what()
              << std::endl;
}

int AssemblyFile::doPassRec(FilePass &filePass,
                            std::vector<std::string> &includes) {
    // Check if this file is previously included
    for (auto const &prevPath : includes) {
        if (equivalentPaths(prevPath, filename)) {
            throw IncludeLoopExn("Including this file forms a cycle: " +
                                 filename);
        }
    }

    // Add this file to the current stack of files.
    includes.push_back(filename);

    std::ifstream in(filename);
    size_t row = 0;
    for (std::string lineStr; std::getline(in, lineStr); row++) {
        try {
            Line line = Line::parse(lineStr);
            filePass.processLine(lineStr, line);

            // If IncludeOp, recursively process included file
            IncludeOp const *includeOp;
            if (line.hasOperation() &&
                (includeOp = dynamic_cast<IncludeOp const *>(
                     &line.getOperation())) != nullptr) {
                // The include path is relative to this file's directory
                std::string includePath =
                    joinPaths(parentDir(filename), includeOp->getFilename());
                AssemblyFile af(includePath);
                if (af.doPassRec(filePass, includes) == 1) {
                    return 1;
                }
            }
        } catch (AssemblyExn &e) {
            printErrorMessage(filename, row, e);
            return 1;
        }
    }
    in.close();

    // Remove this file from the stack of included files, restoring the original
    // stack
    if (includes.back() != filename) {
        throw std::logic_error("Back of filename stack was " + includes.back() +
                               " (expecting " + filename + ")");
    }
    includes.pop_back();

    return 0;
}
