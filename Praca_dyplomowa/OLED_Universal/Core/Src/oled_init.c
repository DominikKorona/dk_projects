/*
 * oled_init.c
 *
 *  Created on: Oct 28, 2023
 *      Author: domko
 */
#include "oled_init.h"

/* Write command */
#define SSD1306_WRITECOMMAND(command)      ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define SSD1306_WRITEDATA(data)            ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
/**/

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SSD1306_DEACTIVATE_SCROLL                    0x2E // Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F // Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range

#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7

extern I2C_HandleTypeDef hi2c1;

uint8_t SSD1306_Init(void) {

	/* Init I2C */
	ssd1306_I2C_Init();

	/* Check if LCD connected to I2C */
	if (HAL_I2C_IsDeviceReady(&hi2c1, SSD1306_I2C_ADDR, 1, 20000) != HAL_OK) {
		/* Return false */
		return 0;
	}
	/* A little delay */
	uint32_t p = 2500;
	while(p>0)
		p--;

	/* Init LCD */
	SSD1306_WRITECOMMAND(0xAE); //display off
	SSD1306_WRITECOMMAND(0x20); //Set Memory Addressing Mode
	SSD1306_WRITECOMMAND(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	SSD1306_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	SSD1306_WRITECOMMAND(0xC8); //Set COM Output Scan Direction
	SSD1306_WRITECOMMAND(0x00); //---set low column address
	SSD1306_WRITECOMMAND(0x10); //---set high column address
	SSD1306_WRITECOMMAND(0x40); //--set start line address
	SSD1306_WRITECOMMAND(0x81); //--set contrast control register
	SSD1306_WRITECOMMAND(0xFF);
	SSD1306_WRITECOMMAND(0xA1); //--set segment re-map 0 to 127
	SSD1306_WRITECOMMAND(0xA6); //--set normal display
	SSD1306_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
	SSD1306_WRITECOMMAND(0x3F); //
	SSD1306_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	SSD1306_WRITECOMMAND(0xD3); //-set display offset
	SSD1306_WRITECOMMAND(0x00); //-not offset
	SSD1306_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
	SSD1306_WRITECOMMAND(0xF0); //--set divide ratio
	SSD1306_WRITECOMMAND(0xD9); //--set pre-charge period
	SSD1306_WRITECOMMAND(0x22); //
	SSD1306_WRITECOMMAND(0xDA); //--set com pins hardware configuration
	SSD1306_WRITECOMMAND(0x12);
	SSD1306_WRITECOMMAND(0xDB); //--set vcomh
	SSD1306_WRITECOMMAND(0x20); //0x20,0.77xVcc
	SSD1306_WRITECOMMAND(0x8D); //--set DC-DC enable
	SSD1306_WRITECOMMAND(0x14); //
	SSD1306_WRITECOMMAND(0xAF); //--turn on SSD1306 panel

	SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
	/* Clear screen */
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	/* Update screen */
	SSD1306_UpdateScreen();
	/* Set default values */
	SSD1306_ResetStructure();

	/* Return OK */
	return 1;
}


void SSD1306_Clear (void)
{
	SSD1306_Fill (0);
    SSD1306_UpdateScreen();
}
void SSD1306_ON(void) {
	SSD1306_WRITECOMMAND(0x8D);
	SSD1306_WRITECOMMAND(0x14);
	SSD1306_WRITECOMMAND(0xAF);
}
void SSD1306_OFF(void) {
	SSD1306_WRITECOMMAND(0x8D);
	SSD1306_WRITECOMMAND(0x10);
	SSD1306_WRITECOMMAND(0xAE);
}

/**
 * Scroll functions
 */

void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND (SSD1306_RIGHT_HORIZONTAL_SCROLL);  // send 0x26
  SSD1306_WRITECOMMAND (0x00);  // send dummy
  SSD1306_WRITECOMMAND(start_row);  // start page address
  SSD1306_WRITECOMMAND(0X00);  // time interval 5 frames
  SSD1306_WRITECOMMAND(end_row);  // end page address
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(0XFF);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL); // start scroll
}


void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND (SSD1306_LEFT_HORIZONTAL_SCROLL);  // send 0x26
  SSD1306_WRITECOMMAND (0x00);  // send dummy
  SSD1306_WRITECOMMAND(start_row);  // start page address
  SSD1306_WRITECOMMAND(0X00);  // time interval 5 frames
  SSD1306_WRITECOMMAND(end_row);  // end page address
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(0XFF);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL); // start scroll
}


void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);  // sect the area
  SSD1306_WRITECOMMAND (0x00);   // write dummy
  SSD1306_WRITECOMMAND(SSD1306_HEIGHT);

  SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  SSD1306_WRITECOMMAND (0x00);
  SSD1306_WRITECOMMAND(start_row);
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(end_row);
  SSD1306_WRITECOMMAND (0x01);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL);
}

void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row)
{
  SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA);  // sect the area
  SSD1306_WRITECOMMAND (0x00);   // write dummy
  SSD1306_WRITECOMMAND(SSD1306_HEIGHT);

  SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  SSD1306_WRITECOMMAND (0x00);
  SSD1306_WRITECOMMAND(start_row);
  SSD1306_WRITECOMMAND(0X00);
  SSD1306_WRITECOMMAND(end_row);
  SSD1306_WRITECOMMAND (0x01);
  SSD1306_WRITECOMMAND (SSD1306_ACTIVATE_SCROLL);
}

void SSD1306_Stopscroll(void)
{
	SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
}
void SSD1306_InvertDisplay (int i)
{
  if (i) SSD1306_WRITECOMMAND (SSD1306_INVERTDISPLAY);

  else SSD1306_WRITECOMMAND (SSD1306_NORMALDISPLAY);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  _____ ___   _____
// |_   _|__ \ / ____|
//   | |    ) | |
//   | |   / /| |
//  _| |_ / /_| |____
// |_____|____|\_____|
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SSD1306_UpdateScreen(void) {
	uint8_t m;
	uint8_t bufor[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
	SSD1306_GetBufor(bufor);

	for (m = 0; m < 8; m++) {
		SSD1306_WRITECOMMAND(0xB0 + m);
		SSD1306_WRITECOMMAND(0x00);
		SSD1306_WRITECOMMAND(0x10);

		/* Write multi data */
		ssd1306_I2C_WriteMulti(SSD1306_I2C_ADDR, 0x40, &bufor[SSD1306_WIDTH * m], SSD1306_WIDTH);
	}
}

void ssd1306_I2C_Init() {
	//MX_I2C1_Init();
	uint32_t p = 250000;
	while(p>0)
		p--;
	//HAL_I2C_DeInit(&hi2c1);
	//p = 250000;
	//while(p>0)
	//	p--;
	//MX_I2C1_Init();
}

void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	uint8_t dt[256];
	dt[0] = reg;
	uint16_t i;
	for(i = 0; i < count; i++){
		dt[i+1] = data[i];
	}
	HAL_I2C_Master_Transmit(&hi2c1, address, dt, count+1, 10);
}


void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c1, address, dt, 2, 10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SPI
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
