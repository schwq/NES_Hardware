#include "ppu_2C02.h"

ppu_2C02::ppu_2C02()
{
	palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);

}

ppu_2C02::~ppu_2C02() {

}

olc::Sprite& ppu_2C02::GetScreen() {
	return sprScreen;
}

olc::Sprite& ppu_2C02::GetNameTable(uint8_t i) {
	return sprNameTable[i];
}

olc::Sprite& ppu_2C02::GetPatternTable(uint8_t i, uint8_t palette) {
	
	for (uint16_t nTileY = 0; nTileY < 16; nTileY++) {
		for (uint16_t nTileX = 0; nTileX < 16; nTileX++) {

			uint16_t nOffset = nTileY * 256 + nTileX * 16;

			for (uint16_t row = 0; row < 8; row++) {

				uint8_t tile_lsb = ppuread(i * 0x1000 + nOffset + row + 0x0000);
				uint8_t tile_msb = ppuread(i * 0x1000 + nOffset + row + 0x0008);

				for (uint16_t col = 0; col < 8; col++) {
					uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01);
					tile_lsb >>= 1;
					tile_msb >>= 1;

					sprPatternTable[i].SetPixel{
						nTileX * 8 + (7 - col),
						nTileY * 8 + row,
						GetColourFromPaletteRam(palette, pixel)
					};
				}

			}
		}
	}
	
	return  sprPatternTable[i];
}

olc::Pixel& ppu_2C02::GetColourFromPaletteRam(uint8_t palette, uint8_t pixel) {
	return palScreen[ppuread(0x3F00 + (palette << 2) + pixel) & 0x3F];
}


uint8_t ppu_2C02::cpuread(uint16_t address, bool read_only)
{
	uint8_t data = 0x00;

	if(read_only) {
		switch (address)
		{
		case 0x0000: // Control
			data = control.reg;
			break;
		case 0x0001: // Mask
			data = mask.reg;
			break;
		case 0x0002: // Status
			data = status.reg;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
		}

		
	}
	else {
		switch (address) {
		case 0x0000: break;
		case 0x0001: break;
		case 0x0002:
			data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
			status.vertical_blank = 0;
			address_latch = 0;
			break;
		case 0x0003: break;
		case 0x0004: break;
		case 0x0005: break;
		case 0x0006: break;
		case 0x0007:
			data = ppu_data_buffer;
			ppu_data_buffer = ppuread(vram_addr.reg);

			if (vram_addr.reg >= 0x3F00) data = ppu_data_buffer;
			vram_addr.reg += (control.increment_mode ? 32 : 1);
			break;
		}
	}

	return data;
}
void ppu_2C02::cpuwrite(uint16_t address, uint8_t data)
{
	switch (address)
	{
	case 0x0000: // Control
		control.reg = data;
		tram_addr.nametable_x = control.nametable_x;
		tram_addr.nametable_y = control.nametable_y;
		break;
	case 0x0001: // Mask
		mask.reg = data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		if (address_latch == 0) {
			fine_x = data & 0x07;
			tram_addr.coarse_x = data >> 3;
			address_latch = 1;

		}
		else {
			tram_addr.fine_y = data & 0x07;
			tram_addr.coarse_y = data >> 3;
			address_latch = 0;
		}
		break;
	case 0x0006: // PPU Address
		
		if (address_latch == 0) {
			tram_addr.reg = (uint16_t)((data & 0x3F) << 8) | (tram_addr.reg & 0x00FF);
			address_latch = 1;
		}
		else {
			tram_addr.reg = (tram_addr.reg & 0xFF00) | data;
			vram_addr = tram_addr;
			address_latch = 0;
		}
		break;
	case 0x0007: // PPU Data
		ppuwrite(vram_addr.reg, data);
		vram_addr.reg += (control.increment_mode ? 32 : 1);
		break;
	}
}

uint8_t ppu_2C02::ppuread(uint16_t address, bool read_only) {
	uint8_t data = 0x00;
	address &= 0x3FFF;
	if (cart->ppuread(address, data)){}
	else if (address >= 0x0000 && address <= 0x1FFF) {
		data = tblPattern[(address & 0x1000) >> 12][address & 0x0FFF];
	}
	else if (address >= 0x2000 && address <= 0x3EFF) {
		address &= 0x0FFF;

		if (cart->mirror == cartridge::MIRROR::VERTICAL) {
			if (address >= 0x0000 && address <= 0x03FF)
				data = tblName[0][address & 0x03FF];
			if (address >= 0x0400 && address <= 0x07FF)
				data = tblName[1][address & 0x03FF];
			if (address >= 0x0800 && address <= 0x0BFF)
				data = tblName[0][address & 0x03FF];
			if (address >= 0x0C00 && address <= 0x0FFF)
				data = tblName[1][address & 0x03FF];
		}
		else if (cart->mirror == cartridge::MIRROR::HORIZONTAL) {
			if (address >= 0x0000 && address <= 0x03FF)
				data = tblName[0][address & 0x03FF];
			if (address >= 0x0400 && address <= 0x07FF)
				data = tblName[0][address & 0x03FF];
			if (address >= 0x0800 && address <= 0x0BFF)
				data = tblName[1][address & 0x03FF];
			if (address >= 0x0C00 && address <= 0x0FFF)
				data = tblName[1][address & 0x03FF];
		}
	}

	else if (address >= 0x3F00 && address <= 0x3FFF) {
		address &= 0x001F;
		if (address == 0x0010) address = 0x0000;
		if (address == 0x0014) address = 0x0004;
		if (address == 0x0018) address = 0x0008;
		if (address == 0x001C) address = 0x000C;
		data = tblPalette[address] & (mask.grayscale ? 0x30 : 0x3F);
	}

	return data;
}

void ppu_2C02::ppuwrite(uint16_t address, uint8_t data) {
	address &= 0x3FFF;
	if (cart->ppuwrite(address, data)) {}
	else if (address >= 0x0000 && address <= 0x1FFF) {
		tblPattern[(address & 0x1000) >> 12][address & 0x0FFF] = data;
	}
	else if (address >= 0x2000 && address <= 0x3EFF) {
		address &= 0x0FFF;
		if (cart->mirror = cartridge::MIRROR::VERTICAL) {
			if (address >= 0x0000 && address <= 0x03FF)
				tblName[0][address & 0x03FF] = data;
			if (address >= 0x0400 && address <= 0x07FF)
				tblName[1][address & 0x03FF] = data;
			if (address >= 0x0800 && address <= 0x0BFF)
				tblName[0][address & 0x03FF] = data;
			if (address >= 0x0C00 && address <= 0x0FFF)
				tblName[1][address & 0x03FF] = data;
		}
		else if (cart->mirror == cartridge::MIRROR::HORIZONTAL) {
			if (address >= 0x0000 && address <= 0x03FF)
				tblName[0][address & 0x03FF] = data;
			if (address >= 0x0400 && address <= 0x07FF)
				tblName[0][address & 0x03FF] = data;
			if (address >= 0x0800 && address <= 0x0BFF)
				tblName[1][address & 0x03FF] = data;
			if (address >= 0x0C00 && address <= 0x0FFF)
				tblName[1][address & 0x03FF] = data;
		}
	}
	else if (address >= 0x3F00 && address <= 0x3FFF) {
		address &= 0x001F;
		if (address == 0x0010) address = 0x0000;
		if (address == 0x0014) address = 0x0004;
		if (address == 0x0018) address = 0x0008;
		if (address == 0x001C) address = 0x000C;
		tblPalette[address] = data;
	}
}

void ppu_2C02::connectcartrigde(const std::shared_ptr<cartridge>& cartridge) {
	this->cart = cartridge;
}

void ppu_2C02::clock() {

	auto IncrementScrollX = [&]() {

		if (mask.render_background || mask.render_sprites) {
			if (vram_addr.coarse_x == 31) {
				vram_addr.coarse_x = 0;
				vram_addr.nametable_x = ~vram_addr.nametable_x;
			}
			else {
				vram_addr.coarse_x++;
			}
		}
	};

	auto IncrementScrollY = [&] () {

		if (mask.render_background || mask.render_sprites) {
			if (vram_addr.fine_y < 7) {
				vram_addr.fine_y++;
			}
			else {
				vram_addr.fine_y = 0;

				if (vram_addr.coarse_y == 29) {
					vram_addr.coarse_y = 0;
					vram_addr.nametable_y = ~vram_addr.nametable_y;

				}
				else if (vram_addr.coarse_y == 31) {
					vram_addr.coarse_y = 0;

				}
				else {
					vram_addr.coarse_y++;
				}



			}
		}
	};

	auto TransferAddressY = [&]() {
		if (mask.render_background || mask.render_sprites) {
			vram_addr.fine_y = tram_addr.fine_y;
			vram_addr.nametable_y = tram_addr.nametable_y;
			vram_addr.coarse_y = tram_addr.coarse_y;
		}
	};

	auto TransferAddressX = [&]()
	{
		// Ony if rendering is enabled
		if (mask.render_background || mask.render_sprites)
		{
			vram_addr.nametable_x = tram_addr.nametable_x;
			vram_addr.coarse_x = tram_addr.coarse_x;
		}
	};

	auto LoadBackgroundShifters = [&]() {
		background_shifter_pattern_lo = (background_shifter_pattern_lo & 0xFF00) | background_next_tile_lsb;
		background_shifter_pattern_hi = (background_shifter_pattern_hi & 0xFF00) | background_next_tile_msb;
		background_shifter_attribute_lo = (background_shifter_attribute_lo & 0xFF00) | ((background_next_tile_attribute & 0b01) ? 0xFF : 0x00);
		background_shifter_attribute_hi = (background_shifter_attribute_hi & 0xFF00) | ((background_next_tile_attribute & 0b10) ? 0xFF : 0x00);
	};

	auto UpdateShifters = [&]() {
		if (mask.render_background) {
			background_shifter_pattern_lo <<= 1;
			background_shifter_pattern_hi <<= 1;
			background_shifter_attribute_lo <<= 1;
			background_shifter_attribute_hi <<= 1;
		}
	};

	if (scanline >= -1 && scanline < 240) {
		if (scanline == 0 && cycle == 0) {
			cycle = 1;
		}

		if (scanline == -1 && cycle == 1) {
			status.vertical_blank = 0;
		}

		if ((cycle >= 2 && cycle < 258) || (cycle >= 321 && cycle < 338)) {
			UpdateShifters();

			switch ((cycle - 1) % 8) {
			case 0:
				LoadBackgroundShifters();
				background_next_tile_id = ppuread(0x2000 | (vram_addr.reg & 0x0FFF));
				break;
			case 2:
				background_next_tile_attribute = ppuread(0x23C0 | (vram_addr.nametable_y << 11)
					| (vram_addr.nametable_x << 10)
					| ((vram_addr.coarse_y >> 2) << 3)
					| (vram_addr.coarse_x >> 2));
				if (vram_addr.coarse_y & 0x02) background_next_tile_attribute >>= 4;
				if (vram_addr.coarse_x & 0x02) background_next_tile_attribute >>= 2;
				background_next_tile_attribute &= 0x03;
				break;
			case 4:

				background_next_tile_lsb = ppuread((control.pattern_background << 12) +
					((uint16_t)background_next_tile_id << 4) +
					(vram_addr.fine_y) + 0);
				break;
			case 6:
				background_next_tile_msb = ppuread((control.pattern_background << 12) +
					((uint16_t)background_next_tile_id << 4) +
					(vram_addr.fine_y) + 8);
				break;
			case 7:
				IncrementScrollX();
				break;
			}
		}

		if (cycle == 256) {
			IncrementScrollY();
		}

		if (cycle == 257) {
			LoadBackgroundShifters();
			TransferAddressX();
		}

		if (cycle == 338 || cycle == 340) {
			background_next_tile_id = ppuread(0x2000 | (vram_addr.reg & 0x0FFF));
		}

		if (scanline == -1 && cycle >= 280 && cycle < 305) {
			TransferAddressY();
		}


	}

	if (scanline >= 241 && scanline < 261) {
		if (scanline == 241 && cycle == 1) {
			status.vertical_blank = 1;

			if (control.enable_nmi)
				nmi = true;
		}
	}

	uint8_t background_pixel = 0x00;
	uint8_t background_palette = 0x00;

	if (mask.render_background) {
		uint16_t bit_mux = 0x8000 >> fine_x;
		uint8_t p0_pixel = (background_shifter_pattern_lo & bit_mux) > 0;
		uint8_t p1_pixel = (background_shifter_pattern_hi & bit_mux) > 0;

		background_pixel = (p1_pixel << 1) | p0_pixel;

		uint8_t background_pal0 = (background_shifter_attribute_lo & bit_mux) > 0;
		uint8_t background_pal1 = (background_shifter_attribute_hi & bit_mux) > 0;
		background_palette = (background_pal1 << 1) | background_pal0;
	}

	sprScreen.SetPixel(cycle - 1, scanline, GetColourFromPaletteRam(background_palette, background_pixel));
	cycle++;
	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;
		if (scanline >= 261)
		{
			scanline = -1;
			frame_complete = true;
		}
	}
}

void ppu_2C02::reset() {
	fine_x = 0x00;
	address_latch = 0x00;
	ppu_data_buffer = 0x00;
	scanline = 0;
	cycle = 0;
	background_next_tile_id = 0x00;
	background_next_tile_attribute = 0x00;
	background_next_tile_lsb = 0x00;
	background_next_tile_msb = 0x00;
	background_shifter_pattern_lo = 0x0000;
	background_shifter_pattern_hi = 0x0000;
	background_shifter_attribute_lo = 0x0000;
	background_shifter_attribute_hi = 0x0000;
	status.reg = 0x00;
	mask.reg = 0x00;
	control.reg = 0x00;
	vram_addr.reg = 0x0000;
	tram_addr.reg = 0x0000;
}