#include "SecondPass.hpp"
#include "line/mnemonics/Mnemonic.hpp"
#include "line/pseudoops/ConstOp.hpp"
#include "line/pseudoops/PseudoOp.hpp"

SecondPass::SecondPass(Context &context, ObjectFile &objectFile,
                       ListingFile &listingFile)
    : context(context), objectFile(objectFile), listingFile(listingFile) {}

void SecondPass::processLine(std::string const &orig, Line const &line) {
    bool hasInstruction = false;

    // Ignore label, labels should already be defined

    if (line.hasOperation()) {
        Mnemonic const *mnemonic =
            dynamic_cast<Mnemonic const *>(&line.getOperation());
        if (mnemonic != nullptr) {
            // It's an instruction.
            // Encode
            uint16_t code = mnemonic->encode(context);
            objectFile.writeCode(code);
            listingFile.writeLine(context.getCurProgramAddress(), code, orig);
            // Increment program counter
            context.setCurProgramAddress(context.getCurProgramAddress() + 1);
            hasInstruction = true;
        } else {
            // Apply all pseudo-ops *except* .const, all constants should
            // already be defined.
            PseudoOp const *pseudoOp =
                dynamic_cast<PseudoOp const *>(&line.getOperation());
            if (pseudoOp != nullptr &&
                dynamic_cast<ConstOp const *>(&line.getOperation()) ==
                    nullptr) {
                pseudoOp->apply(context);
            }
        }
    }

    if (!hasInstruction) {
        // Haven't written to the listing file yet.
        // Write a no-instruction line
        listingFile.writeLine(orig);
    }
}
