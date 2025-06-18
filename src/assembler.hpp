#pragma once
/**
 * @file assembler.hpp
 *
 * Assembler class: reads a *.asm source file and converts it to machine words.
 */

#include <vector>
#include <string>
#include "srp_config.hpp"

namespace srp::assm {

/// Reads an *.asm file and produces the corresponding machine code.
class Assembler {
public:
    /// Constructs the assembler and immediately parses @p filename.
    /// Throws std::runtime_error on any error (file not found, syntax error, …).
    explicit Assembler(const std::string& filename);

    /// Finished machine program (index 0 ≙ PC 0).
    const std::vector<cfg::UWord>& program() const noexcept { return program_; }

private:
    std::vector<cfg::UWord> program_;
};

} // namespace srp::assm
