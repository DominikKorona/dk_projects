
#ifndef INC_OLED_INIT_H_
#define INC_OLED_INIT_H_

#include "oled_comm.h"

/**
 * @brief  SSD1306 colour enumeration
 */
typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black colour, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Colour depends on LCD */
} SSD1306_COLOR_t;

uint8_t OLED_Init(void);

void SSD1306_Clear (void);
void SSD1306_ON(void);
void SSD1306_OFF(void);
void SSD1306_Stopscroll(void);
void SSD1306_InvertDisplay (int i);

// GRAM
void OLED_UpdateScreen(void);

void SSD1306_Fill(SSD1306_COLOR_t Color);
void SSD1306_ToggleInvert(void);
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
///////


#endif /* INC_OLED_INIT_H_ */
