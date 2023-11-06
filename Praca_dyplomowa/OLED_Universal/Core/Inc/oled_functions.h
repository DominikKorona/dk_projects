
#ifndef INC_OLED_FUNCTIONS_H_
#define INC_OLED_FUNCTIONS_H_


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
	#ifndef SSD1306_H
	#define SSD1306_H 100

	/* C++ detection */
	#ifdef __cplusplus
	extern C {
	#endif

	/**
	 * This SSD1306 LCD uses I2C for communication
	 *
	 * Library features functions for drawing lines, rectangles and circles.
	 *
	 * It also allows you to draw texts and characters using appropriate functions provided in library.
	 *
	 * Default pinout
	 *
	SSD1306    |STM32F10x    |DESCRIPTION

	VCC        |3.3V         |
	GND        |GND          |
	SCL        |PB6          |Serial clock line
	SDA        |PB7          |Serial data line
	 */

	#include "oled_init.h"
	#include "oled_fonts.h"

	void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);
	char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);
	char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);
	void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);
	void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
	void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
	void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
	void SSD1306_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
	void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
	void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

	/* C++ detection */
	#ifdef __cplusplus
	}
	#endif

	#endif

#endif /* INC_OLED_FUNCTIONS_H_ */
