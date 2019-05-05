#include "Whitespace.hpp"

bool isWhitespace(char c) { return c == ' ' || c == '\t'; }

std::vector<std::string> splitWhitespace(std::string const &s) {
    std::vector<std::string> out;
    std::string cur = "";
    // Whether the previous character was whitespace
    bool prevWhitespace = false;

    for (size_t i = 0; i < s.size(); i++) {
        if (isWhitespace(s[i])) {
            if (!prevWhitespace) { // End of token
                out.push_back(cur);
                cur.erase();
            }
            prevWhitespace = true;
        } else {
            cur.push_back(s[i]);
            prevWhitespace = false;
        }
    }

    // Add last token
    out.push_back(cur);
    return out;
}
