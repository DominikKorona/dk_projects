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
#include "fonts.h"


/* Character bitmaps for Arial 14pt */
const uint8_t Arial_14pt[] = {

    /* ' ' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '!' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '"' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x80,
    0x02, 0x80,
    0x02, 0x80,
    0x02, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '#' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x40,
    0x02, 0x40,
    0x04, 0x80,
    0x1f, 0xe0,
    0x04, 0x80,
    0x04, 0x80,
    0x1f, 0xe0,
    0x09, 0x00,
    0x09, 0x00,
    0x09, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '$' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x07, 0x80,
    0x0a, 0x40,
    0x12, 0x00,
    0x12, 0x00,
    0x0e, 0x00,
    0x03, 0x80,
    0x02, 0x40,
    0x02, 0x40,
    0x12, 0x80,
    0x0f, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '%' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x18, 0x40,
    0x24, 0x80,
    0x24, 0x80,
    0x25, 0x00,
    0x19, 0x00,
    0x02, 0x60,
    0x02, 0x90,
    0x04, 0x90,
    0x04, 0x90,
    0x08, 0x60,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '&' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x03, 0x80,
    0x04, 0x40,
    0x04, 0x40,
    0x04, 0x80,
    0x03, 0x00,
    0x05, 0x00,
    0x08, 0xa0,
    0x08, 0x40,
    0x08, 0x60,
    0x07, 0x90,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* ''' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '(' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x80,

    /* ')' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,

    /* '*' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x07, 0xc0,
    0x01, 0x00,
    0x02, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '+' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x0f, 0xe0,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* ',' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,

    /* '-' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '.' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '/' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x80,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '0' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '1' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x03, 0x00,
    0x05, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '2' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x00, 0x40,
    0x00, 0x40,
    0x00, 0x80,
    0x01, 0x00,
    0x02, 0x00,
    0x04, 0x00,
    0x0f, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '3' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x00, 0x40,
    0x03, 0x80,
    0x00, 0x40,
    0x00, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '4' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x80,
    0x01, 0x80,
    0x02, 0x80,
    0x04, 0x80,
    0x04, 0x80,
    0x08, 0x80,
    0x10, 0x80,
    0x1f, 0xc0,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '5' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0xc0,
    0x04, 0x00,
    0x08, 0x00,
    0x0f, 0x80,
    0x08, 0x40,
    0x00, 0x40,
    0x00, 0x40,
    0x08, 0x40,
    0x08, 0x80,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '6' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x03, 0x80,
    0x04, 0x40,
    0x08, 0x00,
    0x08, 0x00,
    0x0b, 0x80,
    0x0c, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '7' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x00, 0x40,
    0x00, 0x80,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '8' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '9' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0xc0,
    0x07, 0x40,
    0x00, 0x40,
    0x00, 0x40,
    0x08, 0x80,
    0x07, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* ':' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* ';' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x00, 0x00,

    /* '<' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x40,
    0x01, 0x80,
    0x06, 0x00,
    0x08, 0x00,
    0x06, 0x00,
    0x01, 0x80,
    0x00, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '=' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '>' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x00,
    0x06, 0x00,
    0x01, 0x80,
    0x00, 0x40,
    0x01, 0x80,
    0x06, 0x00,
    0x08, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '?' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x00, 0x40,
    0x00, 0x80,
    0x01, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '\x0040' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x30, 0x20,
    0x40, 0x10,
    0x47, 0x48,
    0x88, 0xc8,
    0x90, 0x48,
    0x90, 0x88,
    0x90, 0x90,
    0x91, 0x90,
    0x4e, 0xe0,
    0x40, 0x08,
    0x30, 0x30,
    0x0f, 0xc0,

    /* 'A' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x02, 0x80,
    0x02, 0x80,
    0x02, 0x80,
    0x04, 0x40,
    0x04, 0x40,
    0x0f, 0xe0,
    0x08, 0x20,
    0x10, 0x10,
    0x10, 0x10,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'B' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x0f, 0xc0,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x0f, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'C' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x10, 0x20,
    0x10, 0x00,
    0x10, 0x00,
    0x10, 0x00,
    0x10, 0x00,
    0x10, 0x20,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'D' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x1f, 0x80,
    0x10, 0x40,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x40,
    0x1f, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'E' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xe0,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x0f, 0xe0,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x0f, 0xe0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'F' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xe0,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x0f, 0xc0,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'G' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0xc0,
    0x08, 0x20,
    0x10, 0x10,
    0x10, 0x00,
    0x10, 0x00,
    0x10, 0xf0,
    0x10, 0x10,
    0x10, 0x10,
    0x08, 0x20,
    0x07, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'H' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x0f, 0xe0,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'I' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'J' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x80,
    0x08, 0x80,
    0x08, 0x80,
    0x07, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'K' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x10,
    0x08, 0x20,
    0x08, 0x40,
    0x08, 0x80,
    0x09, 0x00,
    0x0a, 0x80,
    0x0c, 0x40,
    0x08, 0x40,
    0x08, 0x20,
    0x08, 0x10,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'L' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x0f, 0xe0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'M' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x10, 0x10,
    0x18, 0x30,
    0x18, 0x30,
    0x14, 0x50,
    0x14, 0x50,
    0x12, 0x90,
    0x12, 0x90,
    0x12, 0x90,
    0x11, 0x10,
    0x11, 0x10,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'N' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x20,
    0x0c, 0x20,
    0x0a, 0x20,
    0x0a, 0x20,
    0x09, 0x20,
    0x09, 0x20,
    0x08, 0xa0,
    0x08, 0xa0,
    0x08, 0x60,
    0x08, 0x20,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'O' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0xc0,
    0x08, 0x20,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x08, 0x20,
    0x07, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'P' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x0f, 0xc0,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'Q' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0xc0,
    0x08, 0x20,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0x10,
    0x10, 0xa0,
    0x08, 0x60,
    0x07, 0xb0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'R' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x1f, 0xc0,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x20,
    0x10, 0x20,
    0x1f, 0xc0,
    0x11, 0x00,
    0x10, 0x80,
    0x10, 0x40,
    0x10, 0x20,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'S' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0xc0,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x00,
    0x07, 0x00,
    0x00, 0xe0,
    0x00, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x07, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'T' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xe0,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'U' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x08, 0x20,
    0x04, 0x40,
    0x03, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'V' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x10, 0x10,
    0x10, 0x10,
    0x08, 0x20,
    0x08, 0x20,
    0x04, 0x40,
    0x04, 0x40,
    0x02, 0x80,
    0x02, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'W' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x41, 0x04,
    0x42, 0x84,
    0x22, 0x88,
    0x22, 0x88,
    0x22, 0x88,
    0x14, 0x50,
    0x14, 0x50,
    0x14, 0x50,
    0x08, 0x20,
    0x08, 0x20,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'X' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x10, 0x20,
    0x08, 0x40,
    0x08, 0x40,
    0x04, 0x80,
    0x03, 0x00,
    0x03, 0x00,
    0x04, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x10, 0x20,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'Y' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x10, 0x10,
    0x08, 0x20,
    0x04, 0x40,
    0x04, 0x40,
    0x02, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'Z' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xe0,
    0x00, 0x40,
    0x00, 0x80,
    0x00, 0x80,
    0x01, 0x00,
    0x02, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x08, 0x00,
    0x1f, 0xe0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '[' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x03, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x03, 0x00,

    /* '\' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x80,
    0x00, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* ']' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x03, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x03, 0x00,

    /* '^' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x02, 0x80,
    0x02, 0x80,
    0x02, 0x80,
    0x04, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '_' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x1f, 0xe0,

    /* '`' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'a' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x00, 0x40,
    0x03, 0xc0,
    0x04, 0x40,
    0x08, 0x40,
    0x08, 0xc0,
    0x07, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'b' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x0b, 0x80,
    0x0c, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x0c, 0x40,
    0x0b, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'c' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x03, 0x80,
    0x04, 0x40,
    0x04, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x04, 0x40,
    0x03, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'd' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x40,
    0x00, 0x40,
    0x07, 0x40,
    0x08, 0xc0,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0xc0,
    0x07, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'e' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x0f, 0xc0,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'f' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x80,
    0x02, 0x00,
    0x07, 0x80,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'g' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x40,
    0x08, 0xc0,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0xc0,
    0x07, 0x40,
    0x00, 0x40,
    0x08, 0x40,
    0x07, 0x80,

    /* 'h' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x00,
    0x08, 0x00,
    0x0b, 0x80,
    0x0c, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'i' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'j' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x06, 0x00,

    /* 'k' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x04, 0x00,
    0x04, 0x00,
    0x04, 0x20,
    0x04, 0x40,
    0x04, 0x80,
    0x05, 0x00,
    0x06, 0x80,
    0x04, 0x40,
    0x04, 0x40,
    0x04, 0x20,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'l' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'm' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x16, 0xe0,
    0x19, 0x90,
    0x11, 0x10,
    0x11, 0x10,
    0x11, 0x10,
    0x11, 0x10,
    0x11, 0x10,
    0x11, 0x10,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'n' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0b, 0x80,
    0x0c, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'o' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x80,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x07, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'p' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0b, 0x80,
    0x0c, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x0c, 0x40,
    0x0b, 0x80,
    0x08, 0x00,
    0x08, 0x00,
    0x08, 0x00,

    /* 'q' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x07, 0x40,
    0x08, 0xc0,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0xc0,
    0x07, 0x40,
    0x00, 0x40,
    0x00, 0x40,
    0x00, 0x40,

    /* 'r' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0xc0,
    0x03, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 's' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x03, 0x80,
    0x04, 0x40,
    0x04, 0x00,
    0x03, 0x80,
    0x00, 0x40,
    0x00, 0x40,
    0x04, 0x40,
    0x03, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 't' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x07, 0x80,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x03, 0x80,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'u' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0x40,
    0x08, 0xc0,
    0x07, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'v' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x20,
    0x08, 0x20,
    0x04, 0x40,
    0x04, 0x40,
    0x02, 0x80,
    0x02, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'w' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x11, 0x10,
    0x11, 0x10,
    0x0a, 0xa0,
    0x0a, 0xa0,
    0x0a, 0xa0,
    0x0a, 0xa0,
    0x04, 0x40,
    0x04, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'x' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x40,
    0x04, 0x80,
    0x04, 0x80,
    0x03, 0x00,
    0x03, 0x00,
    0x04, 0x80,
    0x04, 0x80,
    0x08, 0x40,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* 'y' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x08, 0x20,
    0x08, 0x20,
    0x04, 0x40,
    0x04, 0x40,
    0x02, 0x80,
    0x02, 0x80,
    0x02, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x06, 0x00,

    /* 'z' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0f, 0xc0,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x04, 0x00,
    0x0f, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    /* '{' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x80,

    /* '|' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,

    /* '}' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x00, 0x80,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x01, 0x00,
    0x02, 0x00,

    /* '~' (14 pixels wide)*/
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x0e, 0x40,
    0x13, 0xc0,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00
};

/* Font information for Arial */
FontDef_t Arial_14x16 =
{
    14, /*  Width, in pixels, of space character */
    16, /*  Character height */
    Arial_14pt /*  Character bitmap array */
};


char* FONTS_GetStringSize(char* str, FONTS_SIZE_t* SizeStruct, FontDef_t* Font) {
	/* Fill settings */
	SizeStruct->Height = Font->FontHeight;
	SizeStruct->Length = Font->FontWidth * strlen(str);

	/* Return pointer */
	return str;
}
