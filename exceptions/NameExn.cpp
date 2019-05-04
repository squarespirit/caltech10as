#include "NameExn.hpp"

NameExn::NameExn(std::string const &msg) : std::runtime_error(msg) {
}