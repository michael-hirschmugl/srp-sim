#pragma once
/**
 * @file srp_config.hpp
 * Compile-time configuration constants and type aliases for the SRP simulator.
 */

#include <cstdint>
#include <cstddef>

namespace srp::cfg {

    inline constexpr std::uint32_t RegisterCount = 32;     // number of general-purpose registers
    inline constexpr std::uint32_t MainMemWords  = 65536;  // size of main memory in 32-bit words

    using Word  = std::int32_t;   // signed 32-bit word
    using UWord = std::uint32_t;  // unsigned 32-bit word

} // namespace srp::cfg
