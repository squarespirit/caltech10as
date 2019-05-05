#pragma once
#include <functional>
#include <string>

class Name {
public:
    /**
     * Convert a string to a name. Throw a ParseExn if it cannot be converted.
     * The first character must be alphabetic or underscore. Subsequent
     * characters must be alphanumeric or underscore.
     */
    explicit Name(std::string name);

    std::string getName() const;

    bool operator==(const Name &) const;

private:
    std::string name;
};

namespace std {
/**
 * Name will be the key of a hash-map, so it needs to be hashable.
 */
template <> struct hash<Name> {
    std::size_t operator()(const Name &n) const {
        return std::hash<string>()(n.getName());
    }
};
}