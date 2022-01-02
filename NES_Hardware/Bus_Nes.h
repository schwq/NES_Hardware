#pragma once
#include <cstdint>
#include <array>
#include "cpu_6502.h"


class Bus_Nes
{
public:
	Bus_Nes();
	~Bus_Nes();

public:
	cpu_6502 cpu;
	std::array<uint8_t, 64 * 1024> ram; // RAM

public:
	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address, bool read_only = false);
};

