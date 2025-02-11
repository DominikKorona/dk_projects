
#ifndef INC_OLED_INIT_H_
#define INC_OLED_INIT_H_

#include "oled_comm.h"

/**
 * @brief  SSD1306 colour enumeration
 */
typedef enum {
	OLED_COLOR_BLACK = 0x00, /*!< Black colour, no pixel */
	OLED_COLOR_WHITE = 0x01  /*!< Pixel is set. Colour depends on LCD */
} OLED_COLOR_t;

uint8_t OLED_Init(void);

void OLED_Clear (void);
void SSD1306_ON(void);
void SSD1306_OFF(void);
void SSD1306_Stopscroll(void);
void OLED_InvertDisplay (int i);

// GRAM
void OLED_UpdateScreen(void);

void OLED_Fill(OLED_COLOR_t Color);
void OLED_ToggleInvert(void);
void OLED_DrawPixel(uint16_t x, uint16_t y, OLED_COLOR_t color);


///////


#endif /* INC_OLED_INIT_H_ */
