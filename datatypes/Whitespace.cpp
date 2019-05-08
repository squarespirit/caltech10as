#include "Whitespace.hpp"

const char *WHITESPACE = " \t";

bool isWhitespace(char c) { return c == ' ' || c == '\t'; }

void trimWhitespace(std::string &s) {
    // Trim left
    s.erase(0, s.find_first_not_of(WHITESPACE));

    // Trim right
    size_t lastNonSpace = s.find_last_not_of(WHITESPACE);
    // lastNonSpace 1= std::string::npos => string contains some non-space
    // chars.
    // lastNonSpace + 1 < s.length() => the string actually has trailing space
    if (lastNonSpace != std::string::npos && lastNonSpace + 1 < s.length()) {
        s.erase(lastNonSpace + 1);
    }
}

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
