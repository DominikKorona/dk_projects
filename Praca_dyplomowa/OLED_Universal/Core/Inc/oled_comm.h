
#ifndef INC_OLED_COMM_H_
#define INC_OLED_COMM_H_

#include "stm32f4xx_hal.h"


/*Choose the Interface*/
/*
SSD1306    |STM32F41x    |DESCRIPTION

VCC        |3.3V         |
GND        |GND          |
SCL        |PB_          |Serial clock line
SDA        |PB_          |Serial data line
 */
/* Configuration */
// I2C Fast Mode

/* SPI */
/*
SH1106     |STM32F41x    |DESCRIPTION

VCC        |3.3V         |
GND        |GND          |
MOSI       |PC_3         |Serial data line
RST        |PC_9         |Reset
CLK        |PB_10        |Serial clock line
DC         |PA_7         |Data/Command
CS         |PB_4         |Chip select
 */
/* Configuration */
// Clock Parameters
// Prescaler 				8
// Baud Rate				5.25 MBits/s
// Clock Polarity (CPOL) 	HIGH
// Clock Phase (CPHA)		2 EDGE

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
#ifndef OLED_WIDTH
#define OLED_WIDTH            128
#endif
/* OLED display in pixels */
#ifndef OLED_HEIGHT
#define OLED_HEIGHT           64
#endif

#ifndef ssd1306_I2C_TIMEOUT
#define ssd1306_I2C_TIMEOUT					20000
#endif

uint8_t OLED_Prepare_Interface(void);
uint32_t micros(void);
extern uint32_t t1_start;
extern uint32_t t1_end;
extern uint32_t t1_buff_start[8];
extern uint32_t t1_buff_end[8];

#if defined(INTERFACE_I2C)
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);

#elif defined(INTERFACE_SPI)
void sh1106_SPI_WriteMulti(uint8_t* data, uint16_t count);
void sh1106_SPI_Write(uint8_t data);
void sh1106_SPI_WriteMulti_DMA(uint8_t* data, uint16_t count);
#endif
#endif /* INC_OLED_COMM_H_ */
