#include "AssemblyExn.hpp"
AssemblyExn::AssemblyExn(std::string const &msg) : std::runtime_error(msg) {}
