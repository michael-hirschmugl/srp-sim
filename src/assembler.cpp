/**
 * @file assembler.cpp
 *
 * Implementation of the assembler parser.
 */
#include "assembler.hpp"
#include "asm_cmd.hpp"

#include <fstream>
#include <regex>
//#include <sstream>
#include <stdexcept>

using srp::cfg::UWord;
using namespace srp::asmcmd;   // bring instruction classes into scope

namespace srp::assm {

namespace {

/// Remove the comment part (“// …”) from the given line.
inline void stripComment(std::string& line) {
    auto pos = line.find("//");
    if (pos != std::string::npos) line.erase(pos);
}

/// Return true if the line contains nothing but whitespace.
inline bool isBlank(const std::string& line) {
    return line.find_first_not_of(" \t\r\n") == std::string::npos;
}

/// Convert "R17" → 17; throw if the token is not a valid register name.
UWord toReg(const std::string& tok) {
    if (tok.size() < 2 || tok[0] != 'R')
        throw std::runtime_error("Register expected, found: " + tok);
    return static_cast<UWord>(std::stoul(tok.substr(1)));
}

/// Split a string at spaces, tabs, and commas.
std::vector<std::string> splitTokens(const std::string& line) {
    static const std::regex delim(R"([\t ,]+)");
    std::sregex_token_iterator it(line.begin(), line.end(), delim, -1), end;
    return {it, end};
}

/// Append the encoded machine word produced by an instruction object.
template <class Cmd, class... Args>
inline void emit(std::vector<UWord>& prog, Args&&... args) {
    Cmd cmd(std::forward<Args>(args)...);
    prog.emplace_back(cmd.getCode());
}

} // anonymous namespace

// ────────────────────────────────────────────────────────────────

Assembler::Assembler(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error("Cannot open file: " + filename);

    std::string line;
    while (std::getline(in, line))
    {
        stripComment(line);
        if (isBlank(line)) continue;

        auto tok = splitTokens(line);
        if (tok.empty()) continue;                 // empty line

        // Placeholder initialization
        UWord x = 0, y = 0, z = 0, c = 0, sc = 0;

        // Helper lambda: register token vs. literal constant
        auto isReg = [](const std::string& s){ return !s.empty() && s[0] == 'R'; };

        if (tok.size() > 1) {
            if (isReg(tok[1])) x  = toReg(tok[1]);
            else               c  = std::stoul(tok[1]);   // first literal
        }
        if (tok.size() > 2) {
            if (isReg(tok[2])) y  = toReg(tok[2]);
            else               c  = std::stoul(tok[2]);   // second literal (for const)
        }
        if (tok.size() > 3) {
            if (isReg(tok[3])) z  = toReg(tok[3]);
            else               sc = std::stoul(tok[3]);   // shift amount
        }

        const std::string& op = tok[0];            // mnemonic

        // 1-to-1 mapping of instructions (opcode 1–18)
        if      (op == "add")   emit<AddCmd  >(program_, x, y, z);
        else if (op == "sub")   emit<SubCmd  >(program_, x, y, z);
        else if (op == "mul")   emit<MulCmd  >(program_, x, y, z);
        else if (op == "div")   emit<DivCmd  >(program_, x, y, z);
        else if (op == "mod")   emit<ModCmd  >(program_, x, y, z);
        else if (op == "and")   emit<AndCmd  >(program_, x, y, z);
        else if (op == "or")    emit<OrCmd   >(program_, x, y, z);
        else if (op == "not")   emit<NotCmd  >(program_, x, y);
        else if (op == "const") emit<ConstCmd>(program_, x, c);
        else if (op == "sll")   emit<SllCmd  >(program_, x, y, sc);
        else if (op == "load")  emit<LoadCmd >(program_, x, y);
        else if (op == "store") emit<StoreCmd>(program_, x, y);
        else if (op == "goto")  emit<GotoCmd >(program_, x);
        else if (op == "ifeq")  emit<IfeqCmd >(program_, x, y, z);
        else if (op == "iflt")  emit<IfltCmd >(program_, x, y, z);
        else if (op == "halt")  emit<HaltCmd >(program_);
        else if (op == "in")    emit<InCmd   >(program_, x);
        else if (op == "out")   emit<OutCmd  >(program_, x);
        else {
            throw std::runtime_error("Unknown opcode: " + op);
        }
    }
}

} // namespace srp::assm
