/**
 * @file asm_cmd.cpp
 *
 * Implementation of the AsmCmd helpers.
 */

#include "asm_cmd.hpp"
//#include <stdexcept>
//#include <iostream>

namespace srp::asmcmd {

using srp::cfg::UWord;

// Return the already-encoded machine word
UWord AsmCmd::getCode() const {
    return code;
}

// Encode an instruction in XYZ format: op | x | y | z
void AsmCmd::setCodeXYZ(UWord op, UWord x, UWord y, UWord z) {
    code  = op << 27;
    code |= x  << 22;
    code |= y  << 17;
    code |= z  << 12;
}

// Encode an instruction in Const format: op | x | 22-bit constant
void AsmCmd::setCodeConst(UWord op, UWord x, UWord c) {
    code  = op << 27;
    code |= x  << 22;
    code |= c  & 0x3FFFFFu;
}

} // namespace srp::asmcmd
