#include "Line.hpp"
#include "datatypes/Whitespace.hpp"

Line::Line(std::optional<LabelDef> const &label,
           std::optional<std::unique_ptr<Operation>> operation)
    : label(label), operation(std::move(operation)) {}

const char COMMENT_CHAR = ';';

Line Line::parse(std::string const &line) {
    // Remove the comment
    size_t commentStart = line.find_first_of(COMMENT_CHAR);
    std::string s = line.substr(0, commentStart);

    // Extract label
    std::optional<LabelDef> label;
    size_t labelEnd = s.find_first_of(':');
    if (labelEnd != std::string::npos) { // Label found
        size_t labelStart = s.find_first_not_of(WHITESPACE);
        // Parse label. labelEnd + 1 to include :
        label =
            LabelDef::parse(s.substr(labelStart, labelEnd + 1 - labelStart));

        // Remove the label, including :
        s.erase(0, labelEnd + 1);
    }

    // Extract operation
    std::optional<std::unique_ptr<Operation>> operation;
    trimWhitespace(s);
    if (!s.empty()) {
        operation = Operation::parse(s);
    }
    return Line(label, std::move(operation));
}

bool Line::hasLabel() const { return bool(label); }

LabelDef const &Line::getLabel() const { return *label; }

bool Line::hasOperation() const { return bool(operation); }

Operation const &Line::getOperation() const { return *(*operation); }