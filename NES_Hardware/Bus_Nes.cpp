#include "Bus_Nes.h"

Bus_Nes::Bus_Nes() {

	cpu.ConnectBus(this);
}

Bus_Nes::~Bus_Nes() {}

void Bus_Nes::cpuwrite(uint16_t address, uint8_t data) {
	
	if (cart->cpuwrite(address, data)) {

	}
	else if (address >= 0x0000 && address <= 0x1FFF) {
		cpuRam[address & 0x07FF] = data;
	} 
	else if (address >= 0x2000 && address <= 0x3FFF) {
		ppu.cpuwrite(address & 0x0007, data);
	}
}
uint8_t Bus_Nes::cpuread(uint16_t address, bool read_only) {
	uint8_t data = 0x00;
	if (cart->cpuread(address, data)) {

	}
	else if (address >= 0x0000 && address <= 0x1FFF) {
		data = cpuRam[address & 0x07FF];
	}
	else if (address <= 0x2000 && address <= 0x3FFF) {
		data = ppu.cpuread(address & 0x0007, read_only);
	}

	return data;
}

void Bus_Nes::insertCartridge(const std::shared_ptr<cartridge>&cartridge) {
	this->cart = cartridge;
	ppu.connectcartrigde(cartridge);
}

void Bus_Nes::reset() {
	cpu.reset();
	system_clock_counter = 0;
}

void Bus_Nes::clock() {
	ppu.clock();
	if (system_clock_counter % 3 == 0) {
		cpu.clock();
	}

	system_clock_counter++;
}


 