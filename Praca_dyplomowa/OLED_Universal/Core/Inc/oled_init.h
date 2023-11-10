
#ifndef INC_OLED_INIT_H_
#define INC_OLED_INIT_H_

//#include "oled_gram.h"
#include "stm32f4xx_hal.h"
#include "stdlib.h"
/* SSD1306 structure */

/**
 * @brief  SSD1306 colour enumeration
 */
typedef enum{
	DISPLAY_SSD1306,
	DISPLAY_SH1106,
	// TODO: Add new display if you need
}DisplayDriver;
/**
 * @brief  SSD1306 colour enumeration
 */
typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black colour, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Colour depends on LCD */
} SSD1306_COLOR_t;

typedef struct {
	uint8_t Inverted;
	uint8_t Initialised;
//    uint8_t Address;  // Adres I2C lub numer CS w przypadku SPI
//	DisplayDriver Driver;
//	SPI_HandleTypeDef *hspi;
//    I2C_HandleTypeDef *hi2c;  // Wskaźnik do struktury konfiguracyjnej I2C
} Display_t;



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
void ssd1306_I2C_Init();
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void SSD1306_UpdateScreen(void);


uint8_t SH1106_Init(void);
void sh1106_SPI_Write(uint8_t data);
void sh1106_SPI_WriteMulti(uint8_t* data, uint16_t count);
#endif /* INC_OLED_INIT_H_ */
