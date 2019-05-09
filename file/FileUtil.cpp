#include "FileUtil.hpp"
#include "exceptions/FileExn.hpp"
#include <libgen.h>
#include <sys/stat.h>
#include <vector>

bool equivalentPaths(std::string const &p1, std::string const &p2) {
    struct stat stat1, stat2;
    if (stat(p1.c_str(), &stat1)) {
        throw FileExn("Couldn't open file " + p1);
    }
    if (stat(p2.c_str(), &stat2)) {
        throw FileExn("Couldn't open file " + p2);
    }
    // Return if device # and inode # are the same
    return stat1.st_dev == stat2.st_dev && stat1.st_ino == stat2.st_ino;
}

std::string parentDir(std::string const &path) {
    // Get a mutable char*
    std::vector<char> pathCopy(path.begin(), path.end());
    char *pathChars = reinterpret_cast<char *>(pathCopy.data());
    pathChars = dirname(pathChars);
    return std::string(pathChars);
}

std::string joinPaths(std::string const &dir, std::string const &tail) {
    if (!tail.empty() && tail[0] == '/') { // tail is absolute
        return tail;
    }
    return dir + "/" + tail;
}
