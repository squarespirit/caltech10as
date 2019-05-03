#include "NameExn.hpp"

NameExn::NameExn(std::string msg) : std::runtime_error(msg) {
}