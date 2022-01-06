#pragma once
#include <cstdint>
#include <array>
#include "cpu_6502.h"
#include "ppu_2C02.h"
#include "cartridge.h"

class Bus_Nes
{
public:
	Bus_Nes();
	~Bus_Nes();

public:
	cpu_6502 cpu;
	ppu_2C02 ppu;
	std::shared_ptr<cartridge> cart;
	uint8_t cpuRam[2048];

public:
	void cpuwrite(uint16_t address, uint8_t data);
	uint8_t cpuread(uint16_t address, bool read_only = false);

private:
	uint32_t system_clock_counter = 0;
public:
	void insertCartridge(const std::shared_ptr<cartridge>& cartridge);
	void reset();
	void clock();
};
 
