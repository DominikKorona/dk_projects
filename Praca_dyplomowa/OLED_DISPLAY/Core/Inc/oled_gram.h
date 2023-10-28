#ifndef INC_OLED_GRAM_H_
#define INC_OLED_GRAM_H_

/* C++ detection */
#ifdef __cplusplus
	extern C {
	#endif

	#include "stm32f4xx_hal.h"
/*-------------------------------------------------------------------------*/
/*---------------------------------SSD1306---------------------------------*/
/*-------------------------------------------------------------------------*/
	/* I2C address */
	#ifndef SSD1306_I2C_ADDR
	#define SSD1306_I2C_ADDR         0x78
	//#define SSD1306_I2C_ADDR       0x7A
	#endif

	/* SSD1306 settings */
	/* SSD1306 width in pixels */
	#ifndef SSD1306_WIDTH
	#define SSD1306_WIDTH            128
	#endif
	/* SSD1306 LCD height in pixels */
	#ifndef SSD1306_HEIGHT
	#define SSD1306_HEIGHT           64
	#endif
	/* Write command */
	#define SSD1306_WRITECOMMAND(command)      ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
	/* Write data */
	#define SSD1306_WRITEDATA(data)            ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
	/**
	 * @brief  SSD1306 color enumeration
	 */
	typedef enum {
		SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
		SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
	} SSD1306_COLOR_t;

	extern I2C_HandleTypeDef hi2c1;

	void SSD1306_UpdateScreen(void);
	void SSD1306_ToggleInvert(void);
	void SSD1306_Fill(SSD1306_COLOR_t Color);
	void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR_t color);

	void SSD1306_InitStructure(void);
	void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------*/
/*---------------------------------SH1106----------------------------------*/
/*-------------------------------------------------------------------------*/
	//TODO sth
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
	/* C++ detection */
	#ifdef __cplusplus
	}
#endif
#endif /* INC_OLED_GRAM_H_ */
