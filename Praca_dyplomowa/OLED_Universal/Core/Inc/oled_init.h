
#ifndef INC_OLED_INIT_H_
#define INC_OLED_INIT_H_

#include "oled_gram.h"



#ifndef ssd1306_I2C_TIMEOUT
#define ssd1306_I2C_TIMEOUT					20000
#endif

uint8_t SSD1306_Init(void);
void SSD1306_Clear (void);
void SSD1306_ON(void);
void SSD1306_OFF(void);

void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row);
void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row);
void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row);
void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row);
void SSD1306_Stopscroll(void);

void SSD1306_InvertDisplay (int i);
void SSD1306_UpdateScreen(void);
void ssd1306_I2C_Init();
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);



#endif /* INC_OLED_INIT_H_ */
