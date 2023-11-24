
#include "oled_comm.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_tx;

extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

#define I2C_HANDLE 			&hi2c1
#define SPI_HANDLE 			&hspi2
#define I2C_DMA_HANDLE 		&hdma_i2c1_tx
//#define SPI_DMA_HANDLE 		&

//volatile uint8_t dmaTransferComplete=1;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  _____ ___   _____
// |_   _|__ \ / ____|
//   | |    ) | |
//   | |   / /| |
//  _| |_ / /_| |____
// |_____|____|\_____|
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(INTERFACE_I2C)
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	uint8_t dt[256];
	dt[0] = reg;
	uint16_t i;
	for(i = 0; i < count; i++){
		dt[i+1] = data[i];
	}
//	HAL_I2C_Master_Transmit(&hi2c1, address, dt, count+1, 10);
	HAL_I2C_Master_Transmit(&hi2c1, address, data, count, 10);
}

void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&hi2c1, address, dt, 2, 10);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMA
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(USE_DMA)
void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t* buff, uint16_t count) {
//	uint8_t dt[256];
//	dt[0] = reg;
//	uint16_t i;
//	for(i = 0; i < count; i++){
//		dt[i+1] = data[i];
//	}
    HAL_I2C_Mem_Write_DMA(&hi2c1, address, 0x40, 1, buff, count);
}
#endif

#elif defined(INTERFACE_SPI)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SPI
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// GPIO peripherals
#define SH1106_GPIO_PERIPH   (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN)
// SH1106 CS (Chip Select) pin (PB4)
#define CS_GPIO_Port 	GPIOB
#define CS_Pin			GPIO_PIN_4
#define SH1106_CS_H()	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define SH1106_CS_L()	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)

// SH1106 RS/A0 (Data/Command select) pin (PA7)
#define DC_GPIO_Port	GPIOC
#define DC_Pin			GPIO_PIN_7
#define SH1106_DC_H()	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET)
#define SH1106_DC_L()	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET)

// SH1106 RST (Reset) pin (PC9)
#define RST_GPIO_Port	GPIOA
#define RST_Pin			GPIO_PIN_9
#define SH1106_RST_H()	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)
#define SH1106_RST_L()	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)

void sh1106_SPI_WriteMulti(uint8_t* data, uint16_t count){
	SH1106_CS_H();
	SH1106_DC_H();
	SH1106_CS_L();
	HAL_SPI_Transmit(&hspi2, data, count, 20);
	SH1106_CS_H(); //?
}

void sh1106_SPI_Write(uint8_t data){
	SH1106_CS_H();
	SH1106_DC_L();
	SH1106_CS_L();
	HAL_SPI_Transmit(&hspi2, &data, 1, 20);
	SH1106_CS_H();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMA
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
extern UART_HandleTypeDef huart2; //temp
#if defined(USE_DMA)
extern volatile uint8_t dmaCounter; //temp



void sh1106_SPI_WriteMulti_DMA(uint8_t* data, uint16_t count) {
//		HAL_Delay(1);
	SH1106_CS_H();
	SH1106_DC_H();
	SH1106_CS_L();
	HAL_UART_Transmit(&huart2, (uint8_t *)"Hello, 1!\r\n", 14, HAL_MAX_DELAY);
	HAL_SPI_Transmit_DMA(&hspi2, data, count);
//	while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY) {}
//	uint8_t v=2500;
//	while (v>0)
//		v--;
	SH1106_CS_H();
}
#endif
#endif

void testowy(void){
//	SH1106_CS_H();
	SH1106_RST_L();
}
/////// PREPARE INTERFACE ///////

uint8_t OLED_Prepare_Interface(void){
#if defined INTERFACE_I2C
	/* Check if LCD connected to I2C */
	HAL_Delay(1);
	if (HAL_I2C_IsDeviceReady(&hi2c1, SSD1306_I2C_ADDR, 1, 20000) != HAL_OK) {
		/* Return false */
		return 0;
	}
#elif defined(INTERFACE_SPI)
	/* Check if LCD connected to SPI */
	if (HAL_SPI_GetState(&hspi2) == HAL_SPI_STATE_RESET) {
		return 0;
	}
	/*Init SPI*/
	SH1106_CS_H();
	SH1106_DC_L();
	SH1106_RST_H();
	/* A little delay */
	HAL_Delay(1); // add delay function in micro (10u)
	SH1106_RST_L();
	HAL_Delay(1); // 100u
	SH1106_RST_H();
#endif
	return 1;
}

