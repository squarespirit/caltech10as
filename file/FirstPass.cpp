#include "FirstPass.hpp"
#include "line/mnemonics/Mnemonic.hpp"
#include "line/pseudoops/IncludeOp.hpp"
#include "line/pseudoops/PseudoOp.hpp"
#include <stdexcept>

FirstPass::FirstPass(Context &context) : context(context) {}

void FirstPass::processLine(std::string const &orig, Line const &line) {
    if (line.hasLabel()) {
        line.getLabel().apply(context);
    }

    if (line.hasOperation()) {
        if (dynamic_cast<Mnemonic const *>(&line.getOperation()) != nullptr) {
            // It's an instruction. Increment program counter
            context.setCurProgramAddress(context.getCurProgramAddress() + 1);
        } else {
            // Apply all pseudo-ops
            PseudoOp const *pseudoOp =
                dynamic_cast<PseudoOp const *>(&line.getOperation());
            if (pseudoOp != nullptr) {
                pseudoOp->apply(context);
            }
        }
    }
}