#pragma once
#include <string>

/* Register represents one of the Caltech10 CPU's two registers. */
class Register {
public:
    explicit Register(bool isX);
    bool getIsX() const;

    /**
     * Parse a register.
     * The string must be "S" for the S register, or "X" for the X register.
     * All other inputs are invalid and cause a ParseExn.
     */
    static Register parse(std::string const &);

    /**
     * Constant for the S register.
     */
    static const Register S;

    /**
     * Constant for the X register.
     */
    static const Register X;

    bool operator==(Register const &) const;

private:
    bool isX;
};