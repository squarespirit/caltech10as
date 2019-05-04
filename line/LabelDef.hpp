#pragma once

#include <string>
#include "datatypes/Name.hpp"
#include "context/Context.hpp"

/**
 * LabelDef is the definition of a label in a line.
 */
class LabelDef {
public:
    /**
     * Construct a LabelDef from the name of the label.
     */
    explicit LabelDef(Name const &name);
    
    /**
     * Convert a string to a LabelDef. The string should be the label name
     * followed by ":". Throw a ParseExn if the string cannot be converted. 
     */
    static LabelDef parse(std::string s);

    /**
     * Apply this label definition to the given Context. Add a map of this
     * label name -> current address.
     */
    void apply(Context&);

    bool operator==(const LabelDef&) const;
    
private:
    Name name;
};