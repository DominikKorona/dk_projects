
#include "oled_init.h"
#include <string.h>

/*Private structure*/
typedef struct {
	uint8_t Inverted;
	uint8_t Initialised;
} Display_t;
Display_t OLED_DISPLAY;
////////////////////////////////////////////////TIMER

volatile uint8_t dmaCounter; // set static!
volatile uint8_t dmaTransferComplete=1;

////////////////////////////////////////////////TIMER
/* Private data buffer */
static uint8_t OLED_BUFFER[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// I2C
#if defined(INTERFACE_I2C)
/* Write command */
#define OLED_WRITECMD(command)      		ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define OLED_WRITEDATA(data, width)        	ssd1306_I2C_WriteMulti(SSD1306_I2C_ADDR, 0x40, (data), (width))
#if defined(USE_DMA)
#define OLED_WRITEDATA_DMA(buff, width)     ssd1306_I2C_WriteMulti_DMA(SSD1306_I2C_ADDR, 0x40, (buff), (width))
#endif

// SPI
#elif defined(INTERFACE_SPI)
/* Write command */
#define OLED_WRITECMD(command)      		sh1106_SPI_Write(command)
/* Write data */
#define OLED_WRITEDATA(data,width)			sh1106_SPI_WriteMulti(data, width)
#if defined(USE_DMA)
#define OLED_WRITEDATA_DMA(buff, width)     sh1106_SPI_WriteMulti_DMA(buff, width)
#endif
#endif

#define SSD1306_DEACTIVATE_SCROLL   0x2E // Stop scroll
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7

uint8_t OLED_Init(void) {
	OLED_Prepare_Interface();
	OLED_WRITECMD(0xAE); //display off
	OLED_WRITECMD(0x20); //Set Memory Addressing Mode
	OLED_WRITECMD(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_WRITECMD(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	OLED_WRITECMD(0xC8); //Set COM Output Scan Direction
	OLED_WRITECMD(0x00); //---set low column address
	OLED_WRITECMD(0x10); //---set high column address
	OLED_WRITECMD(0x40); //--set start line address
	OLED_WRITECMD(0x81); //--set contrast control register
	OLED_WRITECMD(0xFF);
	OLED_WRITECMD(0xA1); //--set segment re-map 0 to 127
	OLED_WRITECMD(0xA6); //--set normal display
	OLED_WRITECMD(0xA8); //--set multiplex ratio(1 to 64)
	OLED_WRITECMD(0x3F); //1/64 duty
	OLED_WRITECMD(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WRITECMD(0xD3); //-set display offset
	OLED_WRITECMD(0x00); //-not offset
	OLED_WRITECMD(0xD5); //--set display clock divide ratio/oscillator frequency
	OLED_WRITECMD(0xF0); //--set divide ratio
	OLED_WRITECMD(0xD9); //--set pre-charge period
	OLED_WRITECMD(0x22); //
	OLED_WRITECMD(0xDA); //--set com pins hardware configuration
	OLED_WRITECMD(0x12);
	OLED_WRITECMD(0xDB); //--set vcomh
	OLED_WRITECMD(0x20); //0x20,0.77xVcc
	OLED_WRITECMD(0x8D); //--set DC-DC enablev
	OLED_WRITECMD(0x14); //
	OLED_WRITECMD(0xAF); //--turn on SSD1306 panel
	/*initialised*/
	OLED_DISPLAY.Initialised=1;
	/*normal colour*/
	OLED_DISPLAY.Inverted=0;
	OLED_Clear();
	/* Return OK */
	return 1;
}

void OLED_Clear(void)
{
	OLED_Fill (0);
    OLED_UpdateScreen();
}
void OLED_Fill(SSD1306_COLOR_t color) {
	if (OLED_DISPLAY.Inverted) {
		color = (SSD1306_COLOR_t)!color;
	}
	/* Set memory */
	memset(OLED_BUFFER, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(OLED_BUFFER));
}
void SSD1306_ON(void) {
	OLED_WRITECMD(0x8D);
	OLED_WRITECMD(0x14);
	OLED_WRITECMD(0xAF);
}
void SSD1306_OFF(void) {
	OLED_WRITECMD(0x8D);
	OLED_WRITECMD(0x10);
	OLED_WRITECMD(0xAE);
}

void SSD1306_Stopscroll(void)
{
	OLED_WRITECMD(SSD1306_DEACTIVATE_SCROLL);
}
void OLED_InvertDisplay (int i)
{
  if (i) OLED_WRITECMD (SSD1306_INVERTDISPLAY);

  else OLED_WRITECMD (SSD1306_NORMALDISPLAY);

}
/////////////////////////////////////////////////////////////////////////
//
// GRAM
//
/////////////////////////////////////////////////////////////////////////

void OLED_ToggleInvert(void) {
	uint16_t i;
	/* Toggle invert */
	OLED_DISPLAY.Inverted = !OLED_DISPLAY.Inverted;
	/* Do memory toggle */
	for (i = 0; i < sizeof(OLED_BUFFER); i++) {
		OLED_BUFFER[i] = ~OLED_BUFFER[i];
	}
}

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {
	if (
		x >= SSD1306_WIDTH ||
		y >= SSD1306_HEIGHT
	) {
		/* Error */
		return;
	}
	/* Check if pixels are inverted */
	if (OLED_DISPLAY.Inverted) {
		color = (SSD1306_COLOR_t)!color;
	}
	/* Set colour */
	if (color == SSD1306_COLOR_WHITE) {
		OLED_BUFFER[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} else {
		OLED_BUFFER[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  _____
// / ____|
//| |
//| |
//| |____
// \_____|OMMON
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(USE_DMA)
extern volatile uint8_t counter;

void OLED_UpdateScreen(void) {
    uint8_t m;
    counter=0;
    for (m = 0; m < 8; m++) {
        OLED_WRITECMD(0xB0 + m);
        OLED_WRITECMD(0x02);
        OLED_WRITECMD(0x10);
        /* Write multi data */
        OLED_WRITEDATA(&OLED_BUFFER[SSD1306_WIDTH * m], SSD1306_WIDTH);
        counter++;
    }
}



//void OLED_UpdateScreen(void) {
//	uint8_t m;
//	for (m = 0; m < 8; m++) {
//		OLED_WRITECMD(0xB0 + m);
//		OLED_WRITECMD(0x02);
//		OLED_WRITECMD(0x10);
//		/* Write multi data */
//		OLED_WRITEDATA(&OLED_BUFFER[SSD1306_WIDTH * m], SSD1306_WIDTH);
//	}
//}
#elif defined(USE_DMA)
////////////////////////////////////////////////////
//
// Callbacks
//
////////////////////////////////////////////////////


void OLED_UpdateScreen(void) {
	if (dmaCounter==0) {
		dmaTransferComplete=0;
	}

	OLED_WRITECMD(0xB0 + dmaCounter);
	OLED_WRITECMD(0x02);
	OLED_WRITECMD(0x10);

	OLED_WRITEDATA_DMA(&OLED_BUFFER[SSD1306_WIDTH * dmaCounter], SSD1306_WIDTH);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
//	t1_buff_end[dmaCounter]=micros();
	dmaCounter++;
	if (dmaCounter < 8){
		OLED_UpdateScreen(); // ta funkcja to powod dlaczego w tym pliku calback jest
	}else{
		dmaCounter=0;
		dmaTransferComplete=1;
	}
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
    // Trigger the next DMA transferig
//	t1_buff_end[dmaCounter]=micros();
	dmaCounter++;
	if (dmaCounter < 8) {
		OLED_UpdateScreen();
	}else{
		dmaCounter = 0;
		dmaTransferComplete=1;
	}
}
//-------
////////////////////////////////////////////////////
#endif

