#pragma once
#include <vector>
#include <string>
#include <map>

#define LOG
#include <stdio.h>

class Bus_Nes;

class cpu_6502
{
public:
	cpu_6502();
	~cpu_6502();

public:
	uint8_t  a = 0x00;		// Accumulator Register
	uint8_t  x = 0x00;		// X Register
	uint8_t  y = 0x00;		// Y Register
	uint8_t  stkp = 0x00;		// Stack Pointer (points to location on bus)
	uint16_t pc = 0x0000;	// Program Counter
	uint8_t  status = 0x00;		// Status Register

	void reset();
	void irq();
	void nmi();
	void clock();
	bool complete();

	void ConnectBus(Bus_Nes* n) { bus = n; }
	enum FLAGS6502
	{
		C = (1 << 0),	// Carry Bit
		Z = (1 << 1),	// Zero
		I = (1 << 2),	// Disable Interrupts
		D = (1 << 3),	// Decimal Mode (unused in this implementation)
		B = (1 << 4),	// Break
		U = (1 << 5),	// Unused
		V = (1 << 6),	// Overflow
		N = (1 << 7),	// Negative
	};

private:
	uint8_t GetFlag(FLAGS6502 f);
	void	SetFlag(FLAGS6502 f, bool v);

	uint8_t  fetched = 0x00;   // Represents the working input value to the ALU
	uint16_t temp = 0x0000; // A convenience variable used everywhere
	uint16_t addr_abs = 0x0000; // All used memory addresses end up in here
	uint16_t addr_rel = 0x00;   // Represents absolute address following a branch
	uint8_t  opcode = 0x00;   // Is the instruction byte
	uint8_t  cycles = 0;	   // Counts how many cycles the instruction has remaining
	uint32_t clock_count = 0;	   // A global accumulation of the number of clocks

	Bus_Nes *bus = nullptr;
	uint8_t read(uint16_t a);
	void write(uint16_t a, uint8_t d);
	uint8_t fetch();

	struct INSTRUCTION
	{
		std::string name;
		uint8_t(cpu_6502::* operate)(void) = nullptr;
		uint8_t(cpu_6502::* addrmode)(void) = nullptr;
		uint8_t     cycles = 0;
	};

	std::vector<INSTRUCTION> lookup;
};

