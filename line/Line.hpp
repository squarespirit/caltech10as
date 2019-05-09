#include "LabelDef.hpp"
#include "Operation.hpp"
#include <optional>

/**
 * A parsed line of assembly language.
 * Each line of assembly contains an optional label definition and an optional
 * operation.
 */
class Line {
public:
    /**
     * Construct a Line from a label definition and operation.
     * The Line takes ownership of the unique ptr to the operation.
     */
    Line(std::optional<LabelDef> const &,
         std::optional<std::unique_ptr<Operation>> operation);

    /**
     * Convert a string to a Line.
     * The string contains an optional LabelDef, an optional Operation, and
     * optionally a comment.
     *
     * These three components are separated by optional whitespace. The
     * whitespace can be horizontal whitespace, but not vertical. Thus the
     * string *cannot* end in a \n.
     *
     * Throw ParseExn if the string cannot be converted.
     */
    static Line parse(std::string const &);

    /** Return whether this line has a label. */
    bool hasLabel() const;

    /** Get the line's label. Throw an error if it does not have a label. */
    LabelDef const &getLabel() const;

    /** Return whether this line has an operation. */
    bool hasOperation() const;

    /**
     * Get the line's operation. The Line owns the operation, so the reference
     * will become invalid when the Line is destroyed.
     * Throw an error if the Line does not have an operation.
     */
    Operation const &getOperation() const;

private:
    std::optional<LabelDef> label;
    std::optional<std::unique_ptr<Operation>> operation;
};