#include "FilePass.hpp"
#include <fstream>
#include <string>

/**
 * An AssemblyFile is an input file containing lines of assembly language.
 */
class AssemblyFile {
public:
    /**
     * Create an AssemblyFile with the given filename.
     */
    explicit AssemblyFile(std::string const &filename);

    /**
     * Do a pass over each line of this AssemblyFile.
     * Return an exit code: 0 = success, 1 = failure.
     */
    int doPass(FilePass &);

private:
    /**
     * Because of file inclusion, doing a pass over assembly files is recursive.
     * So, doPass immediately dispatches to this function.
     *
     * includes is the current stack of included files, *not counting* this
     * file. doPassRec may modify the stack while it runs, but it will return
     * the stack to its original state when it completes.
     *
     * If an error occurs, print an error message and return failure.
     *
     * Return an exit code: 0 = success, 1 = failure.
     */
    int doPassRec(FilePass &filePass, std::vector<std::string> &includes);

    std::string filename;
};