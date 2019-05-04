#include "Register.hpp"

/**
 * A register with optional pre/post increment/decrement. Used with indexed
 * load/store instruction.
 */
class IncDecRegister {
public:
    /**
     * Construct an IncDecRegister without increment/decrement.
     */
    IncDecRegister(Register reg);
    /**
     * Construct an IncDecRegister with increment/decrement.
     */
    IncDecRegister(Register reg, bool isDec, bool isPost);
    /**
     * Get register.
     */
    Register const &getRegister();
    /**
     * Return whether this IncDecRegister has increment/decrement.
     */
    bool hasIncDec();
    /**
     * If the register should be incremented/decremented, return whether
     * it is decremented.
     * Throw an error if the register is not incremented/decremented.
     */
    bool getIsDec();
    /**
     * If the register should be incremented/decremented, return whether
     * it is a post-increment/decrement.
     * Throw an error if the register is not incremented/decremented.
     */
    bool getIsPost();

    /**
     * Convert a string to an IncDecRegister.
     * For a register without increment or decrement, the string should be 
     * "<reg>".
     * For a register with increment or decrement, the string should be
     * "<+/-><reg>" or "<reg><+/->".
     * Throw ParseExn if the string cannot be parsed.
     */
    static IncDecRegister parse(std::string s);

    bool operator==(const IncDecRegister&) const;
private:
    Register reg;
    bool incDec;
    bool isDec;
    bool isPost;
};