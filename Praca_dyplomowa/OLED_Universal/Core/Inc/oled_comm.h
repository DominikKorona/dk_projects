
#ifndef INC_OLED_COMM_H_
#define INC_OLED_COMM_H_

#include "stm32f4xx_hal.h"

/*Choose the Interface*/

//#define INTERFACE_I2C
#define INTERFACE_SPI
#define USE_DMA
/* I2C address */
#if defined(INTERFACE_I2C)
#define SSD1306_I2C_ADDR         0x78
//#define SSD1306_I2C_ADDR       0x7A
#endif

/* OLED settings */
/* OLED display width in pixels */
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH            128
#endif
/* OLED display in pixels */
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT           64
#endif

#ifndef ssd1306_I2C_TIMEOUT
#define ssd1306_I2C_TIMEOUT					20000
#endif

uint8_t OLED_Prepare_Interface(void);

#if defined(INTERFACE_I2C)
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);

#elif defined(INTERFACE_SPI)
void sh1106_SPI_WriteMulti(uint8_t* data, uint16_t count);
void sh1106_SPI_Write(uint8_t data);
void sh1106_SPI_WriteMulti_DMA(uint8_t* data, uint16_t count);
#endif

void testowy(void);
#endif /* INC_OLED_COMM_H_ */
