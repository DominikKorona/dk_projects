/**
 * original author:  Tilen Majerle<tilen@majerle.eu>
 * modification for STM32f10x: Alexander Lutsai<s.lyra@ya.ru>

   ----------------------------------------------------------------------
   	Copyright (C) Alexander Lutsai, 2016
    Copyright (C) Tilen Majerle, 2015

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */
#include "oled_functions.h"
#define ABS(x)   ((x) > 0 ? (x) : -(x))
#define ASCII_OFFSET 32


void OLED_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color)
{

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    for(int16_t j=0; j<h; j++, y++)
    {
        for(int16_t i=0; i<w; i++)
        {
            if(i & 7)
            {
               byte <<= 1;
            }
            else
            {
               byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            }
            if(byte & 0x80) OLED_DrawPixel(x+i, y, color);
		}
    }
}


char OLED_Putchar(uint8_t chXpos, uint8_t chYpos, char ch, FontDef_t* Font, OLED_COLOR_t color) {

	uint8_t i, j;
	uint8_t byte, byteWidth, rowWidthBytes;
	if (
		OLED_WIDTH <= (chXpos + Font->FontWidth) ||
		OLED_HEIGHT <= (chYpos + Font->FontHeight)
	) {
		/* Error */
		return 0;
	}
	byte = 0; // that variable is useful for greater fonts
	byteWidth = (Font->FontWidth + 7) / 8; // that variable transform bits to bytes of font width
	rowWidthBytes = Font->FontHeight * byteWidth;
	/* Go through font */
	for (i = 0; i < Font->FontHeight; i++) {
			for (j = 0; j < Font->FontWidth; j++) {
				if(j & 7) // gdy i =1,2,3,4,5,6 - to przesuwamy bity o jeden w lewo w kazdej iteracji
				{
					byte <<= 1;
				}else /* gdy i==0 to pobieram zerowy element z tablicy,
					   * i==8,==16 itd. to pobieram sasiedni element**/
				{
					byte = Font->data[(ch - ASCII_OFFSET) * rowWidthBytes + i * byteWidth + j / 8];
				}
				if (byte & 0x80){
					OLED_DrawPixel( (chXpos + j), (chYpos + i), (OLED_COLOR_t) color);
				} else {
					OLED_DrawPixel( (chXpos + j), (chYpos + i), (OLED_COLOR_t)!color);
				}
			}
		}
	/* Return character written */
	return ch;
}

char OLED_Putstring(uint8_t chXpos, uint8_t chYpos, char* str, FontDef_t* Font, OLED_COLOR_t color) {

	/* Write characters */
	while (*str) {
		/* Check available space in LCD */
		if (OLED_Putchar(chXpos, chYpos, *str, Font, color) != *str) {
			/* Return error */
			return *str;
		}
		/* Increase position */
		chXpos += Font->FontWidth;
		/* Increase string pointer */
		str++;
	}

	/* Everything OK, zero should be returned */
	return *str;
}

void OLED_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, OLED_COLOR_t c) {
	int16_t dx, dy, sx, sy, err, e2, i, tmp;

	/* Check for overflow */
	if (x0 >= OLED_WIDTH) {
		x0 = OLED_WIDTH - 1;
	}
	if (x1 >= OLED_WIDTH) {
		x1 = OLED_WIDTH - 1;
	}
	if (y0 >= OLED_HEIGHT) {
		y0 = OLED_HEIGHT - 1;
	}
	if (y1 >= OLED_HEIGHT) {
		y1 = OLED_HEIGHT - 1;
	}

	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;

	if (dx == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Vertical line */
		for (i = y0; i <= y1; i++) {
			OLED_DrawPixel(x0, i, c);
		}

		/* Return from function */
		return;
	}

	if (dy == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}

		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		/* Horizontal line */
		for (i = x0; i <= x1; i++) {
			OLED_DrawPixel(i, y0, c);
		}

		/* Return from function */
		return;
	}

	while (1) {
		OLED_DrawPixel(x0, y0, c);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}

void OLED_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, OLED_COLOR_t c) {
	/* Check input parameters */
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= OLED_WIDTH) {
		w = OLED_WIDTH - x;
	}
	if ((y + h) >= OLED_HEIGHT) {
		h = OLED_HEIGHT - y;
	}

	/* Draw 4 lines */
	OLED_DrawLine(x, y, x + w, y, c);         /* Top line */
	OLED_DrawLine(x, y + h, x + w, y + h, c); /* Bottom line */
	OLED_DrawLine(x, y, x, y + h, c);         /* Left line */
	OLED_DrawLine(x + w, y, x + w, y + h, c); /* Right line */
}

void OLED_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, OLED_COLOR_t c) {
	uint8_t i;

	/* Check input parameters */
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		/* Return error */
		return;
	}

	/* Check width and height */
	if ((x + w) >= OLED_WIDTH) {
		w = OLED_WIDTH - x;
	}
	if ((y + h) >= OLED_HEIGHT) {
		h = OLED_HEIGHT - y;
	}

	/* Draw lines */
	for (i = 0; i <= h; i++) {
		/* Draw lines */
		OLED_DrawLine(x, y + i, x + w, y + i, c);
	}
}

void OLED_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, OLED_COLOR_t color) {
	/* Draw lines */
	OLED_DrawLine(x1, y1, x2, y2, color);
	OLED_DrawLine(x2, y2, x3, y3, color);
	OLED_DrawLine(x3, y3, x1, y1, color);
}


void OLED_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, OLED_COLOR_t color) {
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;

	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay){
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		OLED_DrawLine(x, y, x3, y3, color);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void OLED_DrawCircle(int16_t x0, int16_t y0, int16_t r, OLED_COLOR_t c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    OLED_DrawPixel(x0, y0 + r, c);
    OLED_DrawPixel(x0, y0 - r, c);
    OLED_DrawPixel(x0 + r, y0, c);
    OLED_DrawPixel(x0 - r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawPixel(x0 + x, y0 + y, c);
        OLED_DrawPixel(x0 - x, y0 + y, c);
        OLED_DrawPixel(x0 + x, y0 - y, c);
        OLED_DrawPixel(x0 - x, y0 - y, c);

        OLED_DrawPixel(x0 + y, y0 + x, c);
        OLED_DrawPixel(x0 - y, y0 + x, c);
        OLED_DrawPixel(x0 + y, y0 - x, c);
        OLED_DrawPixel(x0 - y, y0 - x, c);
    }
}

void OLED_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, OLED_COLOR_t c) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    OLED_DrawPixel(x0, y0 + r, c);
    OLED_DrawPixel(x0, y0 - r, c);
    OLED_DrawPixel(x0 + r, y0, c);
    OLED_DrawPixel(x0 - r, y0, c);
    OLED_DrawLine(x0 - r, y0, x0 + r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, c);
        OLED_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, c);

        OLED_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, c);
        OLED_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
}
