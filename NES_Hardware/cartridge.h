#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include "mapper_000.h"


class cartridge
{
public:
	cartridge(const std::string& sFileName);
	~cartridge();

public:
	bool ImageValid();
	enum MIRROR {
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

private:
	bool bImageValid = false;
	uint8_t nMapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;
	std::shared_ptr<mapper> pMapper;

public:
	bool cpuread(uint16_t address, uint8_t& data);
	bool cpuwrite(uint16_t address, uint8_t data);

	bool ppuread(uint16_t address, uint8_t& data);
	bool ppuwrite(uint16_t address, uint8_t data);
};

