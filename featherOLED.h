/*
Some programs to allow the SSD1351 OLED to work with Adafruit's Feather Huzzah ESP8266
*/
#include <stdint.h>
#include <arduino.h>

#ifndef _FEATHEROLED_H
#define _FEATHEROLED_H

class featherOLED {
	uint8_t max_x, max_y, sclk, mosi, cs, DCpin;
	uint8_t page_char[2][16] = {{0x0,0x0,0x0,0x0,0x0,0x18,0x24,0x24,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 0 = Off
								{0x0,0x0,0x0,0x0,0x0,0x18,0x3C,0x3C,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x0}}; // 1 = On
	uint8_t blank_char[16] ={0x0,0x0,0x0,0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x0,0x0,0x0,0x0};
	uint8_t letter[37][16] = {	{0x0,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0,0x0}, // 0 = 0
                          		{0x0,0x0,0x8,0x18,0x78,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x0,0x0,0x0}, // 1 = 1
                          		{0x0,0x0,0x7C,0xC6,0x82,0x82,0x2,0x4,0x18,0x20,0x40,0x80,0xFE,0x0,0x0,0x0}, // 2 = 2
                          		{0x0,0x0,0x7C,0xC2,0x82,0x2,0x4,0x8,0x6,0x2,0x82,0xC6,0x7C,0x0,0x0,0x0}, // 3 = 3
                          		{0x0,0x0,0x4,0xC,0x1C,0x14,0x24,0x44,0xC4,0xFF,0x4,0x4,0x4,0x0,0x0,0x0}, // 4 = 4
                          		{0x0,0x0,0x7E,0x40,0x40,0xC0,0xFC,0xC4,0x2,0x2,0x82,0xC4,0x78,0x0,0x0,0x0}, // 5 = 5
                          		{0x0,0x0,0x38,0x44,0x86,0x80,0xB8,0xE4,0xC2,0xC2,0xC2,0x64,0x38,0x0,0x0,0x0}, // 6 = 6
                          		{0x0,0x0,0xFE,0x2,0x4,0xC,0x18,0x10,0x30,0x30,0x20,0x60,0x60,0x0,0x0,0x0}, // 7 = 7
                          		{0x0,0x0,0x7C,0xC2,0x82,0x82,0x44,0x3C,0xC6,0x82,0x82,0xC6,0x7C,0x0,0x0,0x0}, // 8 = 8
                          		{0x0,0x0,0x38,0x4C,0x86,0x86,0x86,0x4E,0x3A,0x2,0x86,0xC4,0x78,0x0,0x0,0x0}, // 9 = 9
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 10 = A
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 11 = B
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 12 = C
								{0x0,0x0,0x0,0x0,0x78,0x44,0x42,0x42,0x42,0x42,0x42,0x44,0x78,0x0,0x0,0x0}, // 13 = D
								{0x0,0x0,0x0,0x0,0x7E,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x7E,0x0,0x0,0x0}, // 14 = E
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 15 = F
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 16 = G
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 17 = H
								{0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0,0x0,0x0}, // 18 = I
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 19 = J
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 20 = K
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 21 = L
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 22 = M
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 23 = N
								{0x0,0x0,0x0,0x0,0x3C,0x42,0x81,0x81,0x81,0x81,0x81,0x42,0x3C,0x0,0x0,0x0}, // 24 = O
								{0x0,0x0,0x0,0x0,0x7C,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x0,0x0,0x0}, // 25 = P
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 26 = Q
								{0x0,0x0,0x0,0x0,0x7C,0x42,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0x0,0x0,0x0}, // 27 = R
								{0x0,0x0,0x0,0x0,0x78,0x84,0x84,0xC0,0x3C,0x2,0x82,0xC2,0x7C,0x0,0x0,0x0}, // 28 = S
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 29 = T
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 30 = U
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 31 = V
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 32 = W
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 33 = X
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 34 = Y
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}, // 35 = Z
								{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0} // 36 = SPACE
							};
public: 
	featherOLED(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
	void print(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, char *);
	void paginate(uint8_t,uint8_t,uint8_t);
	void init();
	void blank();

private:
	void Font1x1(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
	void Font2x2(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
	void SPIwrite(uint8_t);
	void writeCommand(uint8_t);
	void writeData(uint8_t);
};

#endif