# SRP-Sim
A minimal **S**imple **R**ISC **P**rocessor simulator written in modern C++.

---

## 1  Overview
`srp-sim` models a toy 32-bit RISC machine with

* **32 general-purpose registers** (`R0` … `R31`)
* **65 536 word-addressable memory locations** (256 KiB total)
* a compact **18-opcode instruction set** split into two encodings:
  * *XYZ format* – three 5-bit register/shift fields (e.g. `add Rz, Rx, Ry`)
  * *CONST format* – one register + 22-bit immediate (e.g. `const Rx, C`)

The project provides:

| Component  | File(s)                 | Responsibility |
|------------|-------------------------|----------------|
| **Assembler** | `assembler.hpp / .cpp` | Parses human-readable *.asm* files, converts each mnemonic into a 32-bit machine word and exposes the resulting vector via `program()`. |
| **Instruction helpers** | `asm_cmd.hpp / .cpp` | Tiny wrapper classes (`AddCmd`, `ConstCmd`, …) that know how to encode themselves. |
| **Simulator / CPU** | `srp.hpp / .cpp` | Executes the machine words out of main memory, faithfully emulating all 18 opcodes. |
| **Example program** | `sum10.asm` | Adds 1 … 10 and prints 55 – handy for a first smoke test. |

---

## 2  Build instructions
The code is C++17-conformant and uses **CMake**.

```bash
# clone & configure
$ git clone https://github.com/…/srp-sim.git
$ cd srp-sim
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# compile
$ cmake --build build --parallel
```
The resulting executable lives in `build/srp`.

### Tested toolchains
* GCC 11+ / Clang 14+ / MSVC 19.3+
* Linux, macOS, Windows (x64)

---

## 3  Running the simulator
```bash
# run with an explicit source file
$ ./srp sum10.asm

# or simply ./srp               (falls back to "sum10.asm" in cwd)
```
Expected output for the bundled demo program:

```
x: 55
```

### Command-line behaviour
* **1 argument** → that path is assembled & executed.
* **0 arguments** → the simulator looks for `sum10.asm` in the current directory.
* Any error (file not found, syntax error, unknown opcode) throws a `std::runtime_error` and aborts.

---

## 4  Instruction set summary
| Opcode | Mnemonic | Semantics (pseudo-C) |
|:-----:|:---------|:---------------------|
| 1 | `add  x, y, z` | `R[x] = R[y] + R[z]` |
| 2 | `sub  x, y, z` | `R[x] = R[y] - R[z]` |
| 3 | `mul  x, y, z` | `R[x] = R[y] * R[z]` |
| 4 | `div  x, y, z` | `R[x] = R[y] / R[z]` |
| 5 | `mod  x, y, z` | `R[x] = R[y] % R[z]` |
| 6 | `and  x, y, z` | `R[x] = R[y] & R[z]` |
| 7 | `or   x, y, z` | `R[x] = R[y] \| R[z]` |
| 8 | `not  x, y`    | `R[x] = !R[y]` |
| 9 | `const x, C`   | `R[x] = C` |
|10 | `sll  x, y, s` | `R[x] = R[y] << s` |
|11 | `load x, y`    | `R[x] = MEM[R[y]]` |
|12 | `store x, y`   | `MEM[R[y]] = R[x]` |
|13 | `goto x`       | `PC   = R[x]` |
|14 | `ifeq x, y, z` | `PC = (R[y]==R[z]? R[x] : PC+1)` |
|15 | `iflt x, y, z` | `PC = (R[y]< R[z]? R[x] : PC+1)` |
|16 | `halt`         | stop execution |
|17 | `in   x`       | read integer into `R[x]` |
|18 | `out  x`       | `cout << (R[x] & 0xFF)` |

---

## 5  Directory layout
```
├── CMakeLists.txt    # build script
├── src/
│   ├── asm_cmd.hpp   # instruction encoders
│   ├── asm_cmd.cpp
│   ├── assembler.hpp # parser / assembler
│   ├── assembler.cpp
│   ├── srp.hpp       # CPU / simulator
│   └── srp.cpp
└── sum10.asm         # demo program
```

---

## 6  Extending the simulator
* Add new opcodes by extending `asm_cmd.hpp/.cpp` and adding a `case` in `srp.cpp`.
* Enhance the assembler with labels, `.data` sections or macros.
* Swap the console I/O (`in`, `out`) for a memory-mapped device model.

Pull requests are very welcome!

---

## 7  License
SPDX-License-Identifier: MIT
