
#ifndef INC_OLED_GRAM_H_
#define INC_OLED_GRAM_H_


#include "oled_init.h"

void SSD1306_ToggleInvert(void);
void SSD1306_Fill(SSD1306_COLOR_t Color);
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);

#endif /* INC_OLED_GRAM_H_ */
