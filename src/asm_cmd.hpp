#pragma once
/**
 * @file asm_cmd.hpp
 *
 * Instruction-class declarations for the SRP assembler.
 */

#include "srp_config.hpp"

namespace srp::asmcmd {

using srp::cfg::UWord;

/// Common base class for all assembler instructions
class AsmCmd {
public:
    virtual ~AsmCmd() = default;          // ensures the class is polymorphic
    UWord getCode() const;                // returns the encoded machine word

protected:
    // Encode an instruction in XYZ format
    void setCodeXYZ(UWord, UWord, UWord, UWord);

    // Encode an instruction in Const format
    void setCodeConst(UWord, UWord, UWord);

private:
    UWord code {0};
};

// Convenience wrappers for every opcode (1-18)
struct AddCmd   : AsmCmd { AddCmd(UWord x, UWord y, UWord z) { setCodeXYZ( 1, x, y, z); } };
struct SubCmd   : AsmCmd { SubCmd(UWord x, UWord y, UWord z) { setCodeXYZ( 2, x, y, z); } };
struct MulCmd   : AsmCmd { MulCmd(UWord x, UWord y, UWord z) { setCodeXYZ( 3, x, y, z); } };
struct DivCmd   : AsmCmd { DivCmd(UWord x, UWord y, UWord z) { setCodeXYZ( 4, x, y, z); } };
struct ModCmd   : AsmCmd { ModCmd(UWord x, UWord y, UWord z) { setCodeXYZ( 5, x, y, z); } };
struct AndCmd   : AsmCmd { AndCmd(UWord x, UWord y, UWord z) { setCodeXYZ( 6, x, y, z); } };
struct OrCmd    : AsmCmd { OrCmd (UWord x, UWord y, UWord z) { setCodeXYZ( 7, x, y, z); } };
struct NotCmd   : AsmCmd { NotCmd(UWord x, UWord y)          { setCodeXYZ( 8, x, y, 0); } };
struct ConstCmd : AsmCmd { ConstCmd(UWord x, UWord c)        { setCodeConst( 9, x, c);  } };
struct SllCmd   : AsmCmd { SllCmd(UWord x, UWord y, UWord s) { setCodeXYZ(10, x, y, s); } };
struct LoadCmd  : AsmCmd { LoadCmd (UWord x, UWord y)        { setCodeXYZ(11, x, y, 0); } };
struct StoreCmd : AsmCmd { StoreCmd(UWord x, UWord y)        { setCodeXYZ(12, x, y, 0); } };
struct GotoCmd  : AsmCmd { GotoCmd (UWord x)                 { setCodeXYZ(13, x, 0, 0); } };
struct IfeqCmd  : AsmCmd { IfeqCmd(UWord x, UWord y, UWord z){ setCodeXYZ(14, x, y, z); } };
struct IfltCmd  : AsmCmd { IfltCmd(UWord x, UWord y, UWord z){ setCodeXYZ(15, x, y, z); } };
struct HaltCmd  : AsmCmd { HaltCmd()                         { setCodeXYZ(16, 0, 0, 0); } };
struct InCmd    : AsmCmd { InCmd  (UWord x)                  { setCodeXYZ(17, x, 0, 0); } };
struct OutCmd   : AsmCmd { OutCmd (UWord x)                  { setCodeXYZ(18, x, 0, 0); } };

} // namespace srp::asmcmd
