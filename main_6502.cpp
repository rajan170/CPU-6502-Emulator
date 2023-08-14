#include <iostream>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct Memory {
  static constexpr u32 MAX_MEM = 1024 * 64; // max memory available
  Byte Data[MAX_MEM];

  /*initialise memory*/
  void Initialise() {
    for (u32 i = 0; i < MAX_MEM; i++) {
      Data[i] = 0;
    }
  }

  /*read 1 byte*/
  Byte operator[](u32 Address) const {
    // assert here Address < MAX_MEM
    return Data[Address];
  }
};

struct CPU {

  Word PC; // program counter
  Byte SP; // stack pointer

  Byte A, X, Y; // registers

  // status flags
  Byte C : 1; // carry flag-> used to count overflow and carry-over ops
  Byte Z : 1; // zero flag -> set result to zero
  Byte I : 1; // Interrupt Disable ->
  Byte D : 1; // decimal mode flag
  Byte B : 1; // break command flag
  Byte V : 1; // Overflow flag ->
  Byte N : 1; // negative flag

  /*Reset function to reset CPU to default state*/
  void Reset(Memory &memory) {
    PC = 0xFFFC; // Reset Vector Address
    D = 0;
    SP = 0x0100; // stack pointer init
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    memory.Initialise();
  }

  Byte FetchByte(u32 Cycles, Memory &memory) {
    Byte Data = memory[PC];
    PC++;
    Cycles--;
  }

  void Execute(u32 Cycles, Memory &memory) {
    while (Cycles > 0) {
      Byte Ins = FetchByte(Cycles, memory);
    }
  }
};

int main() {
  Memory memory;
  CPU cpu;
  cpu.Reset(memory);
  cpu.Execute(2, memory);
  return 0;
}