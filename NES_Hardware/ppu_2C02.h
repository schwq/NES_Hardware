#pragma once
#include <cstring>
#include <memory>

#include "olcPixelGameEngine.h"
#include "cartridge.h"

class ppu_2C02
{
public:
	ppu_2C02();
	~ppu_2C02();

private:
	uint8_t		tblName[2][1024];
	uint8_t		tblPattern[2][4096];
	uint8_t		tblPalette[32];

private:
	olc::Pixel  palScreen[0x40];
	olc::Sprite sprScreen = olc::Sprite(256, 240);
	olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
	olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
	// Debugging Utilities
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(uint8_t i);
	olc::Sprite& GetPatternTable(uint8_t i);
	bool frame_complete = false;

private:
	int16_t scanline = 0;
	int16_t cycle = 0;

public:
	uint8_t cpuread(uint16_t address, bool read_only = false);
	void	cpuwrite(uint16_t address, uint8_t data);

	uint8_t ppuread(uint16_t address, bool read_only = false);
	void	ppuwrite(uint16_t address, uint8_t data);

private:
	std::shared_ptr<cartridge> cart;

public:

	void connectcartrigde(const std::shared_ptr<cartridge>& cartridge);
	void clock();
};

