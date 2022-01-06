#include "cartridge.h"

cartridge::cartridge(const std::string& sFileName) {
	struct Header {
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;

	bImageValid = false;
	std::ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open()) {
		ifs.read((char*)&header, sizeof(Header));

		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		uint8_t nFileType = 1;

		if (nFileType == 0) {

		}

		if (nFileType == 1) {
			nPRGBanks = header.prg_rom_chunks;
			vPRGMemory.resize(nPRGBanks * 16384);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			nCHRBanks = header.chr_rom_chunks;
			vCHRMemory.resize(nCHRBanks * 8192);
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}

		if (nFileType == 2) {

		}

		switch (nMapperID) {
		case 0: pMapper = std::make_shared<mapper_000>(nPRGBanks, nCHRBanks); break;
		}

		bImageValid = true;
		ifs.close();
	}
}

cartridge::~cartridge() {

}

bool cartridge::ImageValid() {
	return bImageValid;
}

bool cartridge::cpuread(uint16_t address, uint8_t& data) {
	uint32_t mapped_address = 0;
	if (pMapper->cpuMapRead(address, mapped_address)) {
		data = vPRGMemory[mapped_address];
		return true;
	} 
	else {
		return false;
	}
}

bool cartridge::ppuread(uint16_t address, uint8_t& data) {
	uint32_t mapped_address = 0;
	if (pMapper->ppuMapRead(address, mapped_address)) {
		data = vCHRMemory[mapped_address];
		return true;
	}
	else {
		return false;
	}
}

bool cartridge::ppuwrite(uint16_t address, uint8_t data) {
	uint32_t mapped_address = 0;
	if (pMapper->ppuMapRead(address, mapped_address)) {
		vCHRMemory[mapped_address] = data;
		return true;
	}
	else {
		return false;
	}
}