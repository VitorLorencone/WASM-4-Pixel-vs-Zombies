// Compact font taken from
// https://hackaday.io/project/6309-vga-graphics-over-spi-and-serial-vgatonic/log/20759-a-tiny-4x6-pixel-font-that-will-fit-on-almost-any-microcontroller-license-mit

#include "wasm4.h"
#include "font.h"

u8 palette_black = 0x4;
u8 palette_white = 0x2;

// Font Definition
const u8 font4x6[96][2] = {
	{ 0x00  ,  0x00 },   /*SPACE*/
	{ 0x49  ,  0x08 },   /*'!'*/
	{ 0xb4  ,  0x00 },   /*'"'*/
	{ 0xbe  ,  0xf6 },   /*'#'*/
	{ 0x7b  ,  0x7a },   /*'$'*/
	{ 0xa5  ,  0x94 },   /*'%'*/
	{ 0x55  ,  0xb8 },   /*'&'*/
	{ 0x48  ,  0x00 },   /*'''*/
	{ 0x29  ,  0x44 },   /*'('*/
	{ 0x44  ,  0x2a },   /*')'*/
	{ 0x15  ,  0xa0 },   /*'*'*/
	{ 0x0b  ,  0x42 },   /*'+'*/
	{ 0x00  ,  0x50 },   /*','*/
	{ 0x03  ,  0x02 },   /*'-'*/
	{ 0x00  ,  0x08 },   /*'.'*/
	{ 0x25  ,  0x90 },   /*'/'*/
	{ 0x76  ,  0xba },   /*'0'*/
	{ 0x59  ,  0x5c },   /*'1'*/
	{ 0xc5  ,  0x9e },   /*'2'*/
	{ 0xc5  ,  0x38 },   /*'3'*/
	{ 0x92  ,  0xe6 },   /*'4'*/
	{ 0xf3  ,  0x3a },   /*'5'*/
	{ 0x73  ,  0xba },   /*'6'*/
	{ 0xe5  ,  0x90 },   /*'7'*/
	{ 0x77  ,  0xba },   /*'8'*/
	{ 0x77  ,  0x3a },   /*'9'*/
	{ 0x08  ,  0x40 },   /*':'*/
	{ 0x08  ,  0x50 },   /*';'*/
	{ 0x2a  ,  0x44 },   /*'<'*/
	{ 0x1c  ,  0xe0 },   /*'='*/
	{ 0x88  ,  0x52 },   /*'>'*/
	{ 0xe5  ,  0x08 },   /*'?'*/
	{ 0x56  ,  0x8e },   /*'@'*/
	{ 0x77  ,  0xb6 },   /*'A'*/
	{ 0x77  ,  0xb8 },   /*'B'*/
	{ 0x72  ,  0x8c },   /*'C'*/
	{ 0xd6  ,  0xba },   /*'D'*/
	{ 0x73  ,  0x9e },   /*'E'*/
	{ 0x73  ,  0x92 },   /*'F'*/
	{ 0x72  ,  0xae },   /*'G'*/
	{ 0xb7  ,  0xb6 },   /*'H'*/
	{ 0xe9  ,  0x5c },   /*'I'*/
	{ 0x64  ,  0xaa },   /*'J'*/
	{ 0xb7  ,  0xb4 },   /*'K'*/
	{ 0x92  ,  0x9c },   /*'L'*/
	{ 0xbe  ,  0xb6 },   /*'M'*/
	{ 0xd6  ,  0xb6 },   /*'N'*/
	{ 0x56  ,  0xaa },   /*'O'*/
	{ 0xd7  ,  0x92 },   /*'P'*/
	{ 0x76  ,  0xee },   /*'Q'*/
	{ 0x77  ,  0xb4 },   /*'R'*/
	{ 0x71  ,  0x38 },   /*'S'*/
	{ 0xe9  ,  0x48 },   /*'T'*/
	{ 0xb6  ,  0xae },   /*'U'*/
	{ 0xb6  ,  0xaa },   /*'V'*/
	{ 0xb6  ,  0xf6 },   /*'W'*/
	{ 0xb5  ,  0xb4 },   /*'X'*/
	{ 0xb5  ,  0x48 },   /*'Y'*/
	{ 0xe5  ,  0x9c },   /*'Z'*/
	{ 0x69  ,  0x4c },   /*'['*/
	{ 0x91  ,  0x24 },   /*'\'*/
	{ 0x64  ,  0x2e },   /*']'*/
	{ 0x54  ,  0x00 },   /*'^'*/
	{ 0x00  ,  0x1c },   /*'_'*/
	{ 0x44  ,  0x00 },   /*'`'*/
	{ 0x0e  ,  0xae },   /*'a'*/
	{ 0x9a  ,  0xba },   /*'b'*/
	{ 0x0e  ,  0x8c },   /*'c'*/
	{ 0x2e  ,  0xae },   /*'d'*/
	{ 0x0e  ,  0xce },   /*'e'*/
	{ 0x56  ,  0xd0 },   /*'f'*/
	{ 0x55  ,  0x3B },   /*'g'*/
	{ 0x93  ,  0xb4 },   /*'h'*/
	{ 0x41  ,  0x44 },   /*'i'*/
	{ 0x41  ,  0x51 },   /*'j'*/
	{ 0x97  ,  0xb4 },   /*'k'*/
	{ 0x49  ,  0x44 },   /*'l'*/
	{ 0x17  ,  0xb6 },   /*'m'*/
	{ 0x1a  ,  0xb6 },   /*'n'*/
	{ 0x0a  ,  0xaa },   /*'o'*/
	{ 0xd6  ,  0xd3 },   /*'p'*/
	{ 0x76  ,  0x67 },   /*'q'*/
	{ 0x17  ,  0x90 },   /*'r'*/
	{ 0x0f  ,  0x38 },   /*'s'*/
	{ 0x9a  ,  0x8c },   /*'t'*/
	{ 0x16  ,  0xae },   /*'u'*/
	{ 0x16  ,  0xba },   /*'v'*/
	{ 0x16  ,  0xf6 },   /*'w'*/
	{ 0x15  ,  0xb4 },   /*'x'*/
	{ 0xb5  ,  0x2b },   /*'y'*/
	{ 0x1c  ,  0x5e },   /*'z'*/
	{ 0x6b  ,  0x4c },   /*'{'*/
	{ 0x49  ,  0x48 },   /*'|'*/
	{ 0xc9  ,  0x5a },   /*'}'*/
	{ 0x54  ,  0x00 },   /*'~'*/
	{ 0x56  ,  0xe2 }    /*''*/
};

void PutPixel(s16 x, s16 y, u8 color)
{
  *DRAW_COLORS=color;
  line(x,y,x,y);
}

// Font retreival function - ugly, but needed.
unsigned char getFontLine(unsigned char data, s16 line_num) {
	const u8 index = (data - 32);
	unsigned char pixel = 0;
	if ((font4x6[index][1] & 1) == 1) line_num -= 1;
	if (line_num == 0) {
		pixel = (font4x6[index][0]) >> 4;
	}
	else if (line_num == 1) {
		pixel = (font4x6[index][0]) >> 1;
	}
	else if (line_num == 2) {
		// Split over 2 bytes
		return (unsigned char)((((font4x6[index][0]) & 0x03) << 2) | (((font4x6[index][1]) & 0x02)));
	}
	else if (line_num == 3) {
		pixel = (font4x6[index][1]) >> 4;
	}
	else if (line_num == 4) {
		pixel = (font4x6[index][1]) >> 1;
	}
	return pixel & 0xE;
}

static s16 PrintX, PrintY;

void DrawChar(char c, bool color)
{

	if(color){
		palette_black = 0x4;
		palette_white = 0x0;
	}else {
		palette_black = 0x2;
		palette_white = 0x0;
	}

	const u8 index = ((unsigned char)(c)) - 32;
	u8 data1 = font4x6[index][0];
	u8 data2 = font4x6[index][1];
	s16 y = PrintY;

	if (data2 & 1)	// Descender e.g. j, g
	{
		PutPixel(PrintX, y, palette_white);
		PutPixel(PrintX + 1, y, palette_white);
		PutPixel(PrintX + 2, y, palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data1 & 0x80) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data1 & 0x40) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data1 & 0x20) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data1 & 0x10) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data1 & 0x8) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data1 & 0x4) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data1 & 0x2) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data1 & 0x1) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data2 & 0x2) ? palette_black :palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data2 & 0x80) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data2 & 0x40) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data2 & 0x20) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data2 & 0x10) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data2 & 0x8) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data2 & 0x4) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;
	}
	else
	{
		PutPixel(PrintX, y, (data1 & 0x80) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data1 & 0x40) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data1 & 0x20) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data1 & 0x10) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data1 & 0x8) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data1 & 0x4) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data1 & 0x2) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data1 & 0x1) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data2 & 0x2) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data2 & 0x80) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data2 & 0x40) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data2 & 0x20) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, (data2 & 0x10) ? palette_black : palette_white);
		PutPixel(PrintX + 1, y, (data2 & 0x8) ? palette_black : palette_white);
		PutPixel(PrintX + 2, y, (data2 & 0x4) ? palette_black : palette_white);
		PutPixel(PrintX + 3, y, palette_white);
		y++;

		PutPixel(PrintX, y, palette_white);
		PutPixel(PrintX + 1, y, palette_white);
		PutPixel(PrintX + 2, y, palette_white);
		PutPixel(PrintX + 3, y, palette_white);
	}
}

void DrawString(const char* str, s16 x, s16 y, bool color)
{
	PrintX = x;
	PrintY = y;

	for (;;)
	{
		char c = *str++;
		if (!c)
			break;

		DrawChar(c, color);
		PrintX += FONT_WIDTH;
	}
}

#define MAX_DIGITS 5
void DrawInt(int16_t val, s16 x, s16 y, bool color)
{

	PrintX = x;
	PrintY = y;

	if (val == 0)
	{
		DrawChar('0', color);
		return;
	}
	else if (val < 0)
	{
		DrawChar('-', color);
		PrintX += FONT_WIDTH;
	}

	char buffer[MAX_DIGITS];
	int bufCount = 0;

	for (int n = 0; n < MAX_DIGITS && val != 0; n++)
	{
		unsigned char c = (unsigned char) val % 10;
		buffer[bufCount++] = '0' + c;
		val = val / 10;
	}

	for (int n = bufCount - 1; n >= 0; n--)
	{
		DrawChar(buffer[n], color);
		PrintX += FONT_WIDTH;
	}
}