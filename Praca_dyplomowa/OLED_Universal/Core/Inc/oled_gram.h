
#ifndef INC_OLED_GRAM_H_
#define INC_OLED_GRAM_H_

#include "stm32f4xx_hal.h"
#include "stdlib.h"

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

/**
 * @brief  SSD1306 color enumeration
 */
typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;



void SSD1306_SetXY(uint16_t x, uint16_t y);
void SSD1306_GetXY(uint16_t* x, uint16_t* y);
void SSD1306_GetBufor(uint8_t *buf);
void SSD1306_ResetStructure(void);

void SSD1306_ToggleInvert(void);
void SSD1306_Fill(SSD1306_COLOR_t Color);
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);



#endif /* INC_OLED_GRAM_H_ */
