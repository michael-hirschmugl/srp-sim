#include "srp.hpp"
#include "assembler.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    // If no command-line argument is given, use the default file “sum10.asm”
    const char* file = (argc == 2) ? argv[1] : "sum10.asm";

    try {
        srp::assm::Assembler asmbl(file);   // parse & assemble the source file

        srp::Srp cpu;

        // Copy the machine code into main memory starting at address 0
        const auto& prog = asmbl.program();
        for (std::size_t i = 0; i < prog.size(); ++i)
            cpu.memory()[i] = static_cast<srp::cfg::Word>(prog[i]);

        cpu.run();                          // execute the program
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 2;
    }
}
