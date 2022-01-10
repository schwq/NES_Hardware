#include "mapper_000.h"

mapper_000::mapper_000(uint8_t prgBanks, uint8_t chrBanks) : mapper(prgBanks, chrBanks){}

mapper_000::~mapper_000() {}

bool mapper_000::cpuMapRead(uint16_t address, uint32_t& mapped_addr) {

	if (address >= 0x8000 && address <= 0xFFFF) {
		mapped_addr = address & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool mapper_000::cpuMapWrite(uint16_t address, uint32_t& mapped_addr) {
	if (address >= 0x8000 && address <= 0xFFFF) {
		mapped_addr = address & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
} 

bool mapper_000::ppuMapRead(uint16_t address, uint32_t& mapped_addr)
{
	if (address >= 0x0000 && address <= 0x1FFF)
	{
		mapped_addr = address;
		return true;
	}

	return false;
}

bool mapper_000::ppuMapWrite(uint16_t address, uint32_t& mapped_addr) {
	if (address >= 0x0000 && address <= 0x1FFF) {
		if (nCHRBanks == 0) {
			mapped_addr = address;
			return true;
		}
	}

	return false;
}

void mapper_000::reset() {}