#include "file/AssemblyFile.hpp"
#include "file/FirstPass.hpp"
#include "file/SecondPass.hpp"
#include <iostream>

void printUsage() {
    std::cout << "Usage: caltech10as <assembly-file>" << std::endl;
    std::cout << std::endl;
    std::cout << "caltech10as is an assembler for the Caltech10 CPU."
              << std::endl;
    std::cout << std::endl;
    std::cout << "Given assembly code in <file>.asm, the assembler compiles it "
                 "to the object file '<file>.obj', and"
              << std::endl;
    std::cout << "also writes a listing file at '<file>.lst' with original "
                 "source and assembled code side-by-side."
              << std::endl;
    std::cout << "Error messages are written to stderr." << std::endl;
}

void printFatalError() {
    std::cerr << "Error, did not finish assembly." << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printUsage();
        return 1;
    }

    const std::string ext(".asm");

    std::string asmName(argv[1]);
    std::string basename = asmName;
    // If assembly filename ends in .asm, remove .asm from basename
    if (asmName.length() >= ext.length() &&
        asmName.compare(asmName.length() - ext.length(), ext.length(), ext) ==
            0) {
        basename = asmName.substr(0, asmName.length() - 4);
    }

    Context c;
    AssemblyFile asmFile(asmName);

    FirstPass firstPass(c);
    if (asmFile.doPass(firstPass) != 0) {
        printFatalError();
        return 1;
    }
    // Reset context's program address and data address before the second pass
    c.setCurDataAddress(0);
    c.setCurProgramAddress(0);
    ObjectFile objFile(basename + ".obj");
    ListingFile lstFile(basename + ".lst");
    SecondPass secondPass(c, objFile, lstFile);
    if (asmFile.doPass(secondPass) != 0) {
        printFatalError();
        return 1;
    }

    return 0;
}