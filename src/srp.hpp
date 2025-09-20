#pragma once
/**
 * @file srp.hpp
 * Main class of the minimal SRP simulator.
 */

#include "srp_config.hpp"
#include <array>

//#define DEBUG_OUT

namespace srp {

class Srp {
public:
    Srp() = default;

    /// Access to main memory; copy your program in and then call run()
    std::array<cfg::Word, cfg::MainMemWords>&       memory() noexcept { return memory_; }
    const std::array<cfg::Word, cfg::MainMemWords>& memory() const noexcept { return memory_; }

    void run();   // execute instructions starting at PC = 0

private:
    cfg::Word pc_{0};   // program counter

    std::array<cfg::Word, cfg::RegisterCount> registers_{};  // general-purpose registers
    std::array<cfg::Word, cfg::MainMemWords>  memory_{};     // main memory (word-addressed)
};

} // namespace srp
