/*
 * Copyright:      Fabian Maximilian Thiele  mailto:me@apetech.de
 * Author:         Fabian Maximilian Thiele
 * Remarks:        this Copyright must be included
 * known Problems: none
 * Version:        1.1
 * Description:    Graphic Library for KS0108- (and compatible) based LCDs
 * 
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
//Screen size
#define DISPLAY_SCREEN_WIDTH		128
#define DISPLAY_SCREEN_HEIGHT		64

/* DO NOT TOUCH BELOW! */
// Ports
#define LCD_CMD_PORT		PORT_LCD_CMD		// Command Output Register
#define LCD_CMD_DIR			DDR_LCD_CMD		// Data Direction Register for Command Port

#define LCD_DATA_IN			PIN_LCD_DATA		// Data Input Register
#define LCD_DATA_OUT		PORT_LCD_DATA		// Data Output Register
#define LCD_DATA_DIR		DDR_LCD_DATA		// Data Direction Register for Data Port

// Command Port Bits
#define D_I					LCD_CMD_DI		// D/I Bit Number
#define R_W					LCD_CMD_RW		// R/W Bit Number
#define EN					LCD_CMD_EN		// EN Bit Number
#define CSEL1				LCD_CMD_CS1		// CS1 Bit Number
#define CSEL2				LCD_CMD_CS2		// CS2 Bit Number

// Chips
#define CHIP1				0x00
#define CHIP2				0x01

// Commands
#define LCD_ON				0x3F
#define LCD_OFF				0x3E
#define LCD_SET_ADD			0x40
#define LCD_SET_PAGE		0xB8
#define LCD_DISP_START		0xC0

// Colors
#define BLACK				0xFF
#define WHITE				0x00

// Font Indices
#define FONT_LENGTH			0
#define FONT_FIXED_WIDTH	2
#define FONT_HEIGHT			3
#define FONT_FIRST_CHAR		4
#define FONT_CHAR_COUNT		5
#define FONT_WIDTH_TABLE	6

typedef uint8_t (*displayFontCallback)(const uint8_t*);

//
// Function Prototypes
//

// Graphic Functions
extern void displayInit(uint8_t invert);
void displayDrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
void displayDrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void displayDrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color);
void displayFillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void displayFillRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color);
void displayInvertRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void displaySetInverted(uint8_t invert);
void displaySetDot(uint8_t x, uint8_t y, uint8_t color);

#define displayDrawVertLine(x, y, length, color) {displayFillRect(x, y, 0, length, color);}
#define displayDrawHoriLine(x, y, length, color) {displayFillRect(x, y, length, 0, color);}
#define displayDrawCircle(xCenter, yCenter, radius, color) {displayDrawRoundRect(xCenter-radius, yCenter-radius, 2*radius, 2*radius, radius, color);}
#define displayClearScreen() {displayFillRect(0, 0, 127, 63, WHITE);}

// Font Functions
uint8_t displayReadFontData(const uint8_t* ptr);		//Standard Read Callback
void displaySelectFont(const uint8_t* font, displayFontCallback callback, uint8_t color);
int displayPutChar(unsigned char c);
void displayPuts(char* str);
void displayPuts_P(PGM_P str);
uint8_t displayCharWidth(char c);
uint16_t displayStringWidth(char* str);
uint16_t displayStringWidth_P(PGM_P str);

// Control Functions
void displayGotoXY(uint8_t x, uint8_t y);
uint8_t displayReadData(void);
void displayWriteCommand(uint8_t cmd, uint8_t chip);
void displayWriteData(uint8_t data);


#endif /* DISPLAY_H_ */