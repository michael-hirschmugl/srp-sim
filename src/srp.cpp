/**
 * @file srp.cpp
 * Implementation of the Srp class.
 */

#include "srp.hpp"
//#include <stdexcept>
#include <iostream>

namespace srp {

void Srp::run()
{
    // Execute instructions until PC is set to –1 (halt)
    while (pc_ >= 0)
    {
        cfg::UWord instr = static_cast<cfg::UWord>(memory_[pc_]);

        // Decode common fields
        cfg::UWord opCode = (instr >> 27) & 0x1Fu;
        cfg::UWord x      = (instr >> 22) & 0x1Fu;
        cfg::UWord y      = (instr >> 17) & 0x1Fu;
        cfg::UWord z      = (instr >> 12) & 0x1Fu;   // also used as shift amount
        cfg::UWord sc     = (instr >> 12) & 0x1Fu;   // alias for z when used as “s”
        cfg::UWord c      =  instr        & 0x3FFFFFu;

        switch (opCode)
        {
            case 1:  // add  x, y, z
                registers_[x] = registers_[y] + registers_[z];
                ++pc_;
                break;

            case 2:  // sub  x, y, z
                registers_[x] = registers_[y] - registers_[z];
                ++pc_;
                break;

            case 3:  // mul  x, y, z
                registers_[x] = registers_[y] * registers_[z];
                ++pc_;
                break;

            case 4:  // div  x, y, z
                registers_[x] = registers_[y] / registers_[z];
                ++pc_;
                break;

            case 5:  // mod  x, y, z
                registers_[x] = registers_[y] % registers_[z];
                ++pc_;
                break;

            case 6:  // and  x, y, z
                registers_[x] = registers_[y] & registers_[z];
                ++pc_;
                break;

            case 7:  // or   x, y, z
                registers_[x] = registers_[y] | registers_[z];
                ++pc_;
                break;

            case 8:  // not  x, y
                registers_[x] = !registers_[y];
                ++pc_;
                break;

            case 9:  // const x, c
                registers_[x] = c;
                ++pc_;
                break;

            case 10: // sll  x, y, sc
                registers_[x] = registers_[y] << sc;
                ++pc_;
                break;

            case 11: // load x, y   (register indirect)
                registers_[x] = memory_[registers_[y]];
                ++pc_;
                break;

            case 12: // store x, y  (register indirect)
                memory_[registers_[y]] = registers_[x];
                ++pc_;
                break;

            case 13: // goto x
                pc_ = registers_[x];
                break;

            case 14: // ifeq x, y, z   (if R[y] == R[z] jump to R[x])
                pc_ = (registers_[y] == registers_[z] ? registers_[x] : pc_ + 1);
                break;

            case 15: // iflt x, y, z   (if R[y]  < R[z] jump to R[x])
                pc_ = (registers_[y] <  registers_[z] ? registers_[x] : pc_ + 1);
                break;

            case 16: // halt
                pc_ = -1;   // terminate execution loop
                break;

            case 17: // in x
                std::cout << "x: ";
                std::cin  >> registers_[x];
                ++pc_;
                break;

            case 18: // out x
                std::cout << "x: " << (registers_[x] & 0xFFu) << std::endl;
                ++pc_;
                break;

            default: // unknown opcode -> stop the simulator
                [[unlikely]];
                pc_ = -1;
                break;
        }
    }
}

} // namespace srp
