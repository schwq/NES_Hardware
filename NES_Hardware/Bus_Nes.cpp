#include "Bus_Nes.h"

Bus_Nes::Bus_Nes() {

	cpu.ConnectBus(this);
	for (auto& i : ram) i = 0x00;
}

Bus_Nes::~Bus_Nes() {}

void Bus_Nes::write(uint16_t address, uint8_t data) {
	if (address >= 0x0000 && address <= 0xFFFF)
		ram[address] = data;
}
uint8_t Bus_Nes::read(uint16_t address, bool read_only) {
	if (address >= 0x0000 && address <= 0xFFFF)
		return ram[address];
	return 0x00;
}
