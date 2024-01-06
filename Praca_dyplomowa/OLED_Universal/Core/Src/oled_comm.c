
#include "oled_comm.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef	hi2c1;
extern SPI_HandleTypeDef 	hspi2;

#define I2C_HANDLE 			(&hi2c1)
#define SPI_HANDLE 			(&hspi2)

uint32_t t1_start;
uint32_t t1_end;
volatile uint8_t counter;

uint32_t t1_buff_start[8];
uint32_t t1_buff_end[8];

extern uint8_t dmaCounter;
extern TIM_HandleTypeDef htim2;
uint32_t micros(void) {
    return  __HAL_TIM_GET_COUNTER(&htim2); // htimx to Twój timer
}
/**
 * @brief  This function provides a delay (in microseconds)
 * @param  microseconds: delay in microseconds
 */

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
	uint8_t i;
	for(i = 0; i < count; i++)
		dt[i+1] = data[i];
	t1_buff_start[counter] = micros();
	HAL_I2C_Master_Transmit(I2C_HANDLE, address, dt, count+1, 10);
	t1_buff_end[counter] = micros();
}


void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(I2C_HANDLE, address, dt, 2, 10);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMA
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(USE_DMA)
void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t* buff, uint16_t count) {
//	t1_start=micros();
	t1_buff_start[dmaCounter]=micros();
    HAL_I2C_Mem_Write_DMA(I2C_HANDLE, address, reg, 1, buff, count);
    t1_buff_end[dmaCounter]=micros();
}
#endif

#elif defined(INTERFACE_SPI)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SPI
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// GPIO peripherals
//#define SH1106_GPIO_PERIPH   (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN)
// SH1106 CS (Chip Select) pin (PB4)
#define CS_GPIO_Port 	GPIOB
#define CS_Pin			GPIO_PIN_4
#define SH1106_CS_H()	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define SH1106_CS_L()	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)

// SH1106 DC/A0 (Data/Command select) pin (PA7)
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
//	SH1106_CS_H();
	SH1106_DC_H(); // data
	SH1106_CS_L();
	t1_buff_start[counter] = micros();
	HAL_SPI_Transmit(SPI_HANDLE, data, count, HAL_MAX_DELAY);
	t1_buff_end[counter] = micros();
//	SH1106_CS_H(); //?
}

void sh1106_SPI_Write(uint8_t data){

	SH1106_CS_H();
	SH1106_DC_L(); // command
	SH1106_CS_L();
	HAL_SPI_Transmit(SPI_HANDLE, &data, 1, HAL_MAX_DELAY);
	SH1106_CS_H();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DMA
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(USE_DMA)
void sh1106_SPI_WriteMulti_DMA(uint8_t* data, uint16_t count) {
//	SH1106_CS_H();//mozna wylaczyc
	SH1106_DC_H();
	SH1106_CS_L();
	t1_buff_start[dmaCounter]=micros();
	HAL_SPI_Transmit_DMA(SPI_HANDLE, data, count);
	t1_buff_end[dmaCounter]=micros();
}


#endif
#endif
/////// PREPARE INTERFACE ///////
uint8_t OLED_Prepare_Interface(void){
#if defined(INTERFACE_I2C)
	/* Check if LCD connected to I2C */
	HAL_Delay(1);
	if (HAL_I2C_IsDeviceReady(I2C_HANDLE, SSD1306_I2C_ADDR, 1, 20000) != HAL_OK) {
		/* Return false */
		return 0;
	}
	/* A little delay */
	uint32_t p = 2500;
	while(p>0)
		p--;
#elif defined(INTERFACE_SPI)
	/* Check if LCD connected to SPI */
	if (HAL_SPI_GetState(SPI_HANDLE) == HAL_SPI_STATE_RESET) {
		return 0;
	}
//	/*Init SPI*/
	SH1106_CS_H();
	SH1106_DC_L();
	SH1106_RST_L();
	SH1106_RST_H();
#endif
	return 1;
}

