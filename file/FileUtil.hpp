#include <string>

/**
 * Return whether two paths point to the same file.
 * Throw a FileExn if either of the paths cannot be opened.
 */
bool equivalentPaths(std::string const &p1, std::string const &p2);

/**
 * Return parent directory of a path.
 * Wrapper for dirname().
 */
std::string parentDir(std::string const &path);

/**
 * Join paths "dir" and "tail".
 * If tail is an absolute path, just return tail.
 * Otherwise, return "dir/tail".
 */
std::string joinPaths(std::string const &dir, std::string const &tail);