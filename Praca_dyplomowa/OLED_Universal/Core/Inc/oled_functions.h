
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

	/* C++ detection */
	#ifdef __cplusplus
	extern C {
	#endif

	/**
	 * This OLED LCD uses I2C for communication
	 *
	 * Library features functions for drawing lines, rectangles and circles.
	 *
	 * It also allows you to draw texts and characters using appropriate functions provided in library.
	 *
	 * Default pinout
	 *
	OLED    |STM32F10x    |DESCRIPTION

	VCC        |3.3V         |
	GND        |GND          |
	SCL        |PB6          |Serial clock line
	SDA        |PB7          |Serial data line
	 */

	#include "oled_init.h"
	#include "oled_fonts.h"

	void OLED_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);
	char OLED_Putchar(uint8_t chXpos, uint8_t chYpos, char ch, FontDef_t* Font, OLED_COLOR_t color);
	char OLED_Putstring(uint8_t chXpos, uint8_t chYpos, char* str, FontDef_t* Font, OLED_COLOR_t color);

	void OLED_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, OLED_COLOR_t c);
	void OLED_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, OLED_COLOR_t c);
	void OLED_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, OLED_COLOR_t c);
	void OLED_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, OLED_COLOR_t color);
	void OLED_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, OLED_COLOR_t color);
	void OLED_DrawCircle(int16_t x0, int16_t y0, int16_t r, OLED_COLOR_t c);
	void OLED_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, OLED_COLOR_t c);

	/* C++ detection */
	#ifdef __cplusplus
	}
	#endif

#endif /* INC_OLED_FUNCTIONS_H_ */
