/*
 * Copyright:      Fabian Maximilian Thiele  mailto:me@apetech.de
 * Author:         Fabian Maximilian Thiele
 * Remarks:        this Copyright must be included
 * known Problems: none
 * Version:        1.1
 * Description:    Graphic Library for DISPLAY- (and compatible) based LCDs
 * 
 */

#include "Headers/config.h"
#include "Headers/display.h"

lcdCoord			displayCoord;
uint8_t				displayInverted=0;
displayFontCallback	displayFontRead;
uint8_t				displayFontColor;
const uint8_t*		displayFont;

void displayInit(const uint8_t invert) {
	displayCoord.x = 0;
	displayCoord.y = 0;
	displayCoord.page = 0;
	
	displayInverted = invert;
	
	LCD_CMD_DIR = 0xFF;								// command port is output
	displayWriteCommand(LCD_ON, CHIP1);				// power on
	displayWriteCommand(LCD_ON, CHIP2);
	
	displayWriteCommand(LCD_DISP_START, CHIP1);		// display start line = 0
	displayWriteCommand(LCD_DISP_START, CHIP2);
	displayClearScreen();							// display clear
	displayGotoXY(0,0);
}


void displayDrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color) {
	uint8_t length, i, y, yAlt, xTmp, yTmp;
	int16_t m;
	
	//
	// vertical line
	//
	if(x1 == x2) {
		// x1|y1 must be the upper point
		if(y1 > y2) {
			yTmp = y1;
			y1 = y2;
			y2 = yTmp;
		}
		displayDrawVertLine(x1, y1, y2-y1, color);
	
	//
	// horizontal line
	//
	} else if(y1 == y2) {	
		// x1|y1 must be the left point
		if(x1 > x2) {
			xTmp = x1;
			x1 = x2;
			x2 = xTmp;
		}
		displayDrawHoriLine(x1, y1, x2-x1, color);
	
	//
	// schiefe line :)
	//
	} else {
		// angle >= 45°
		if((y2-y1) >= (x2-x1) || (y1-y2) >= (x2-x1)) {
			// x1 must be smaller than x2
			if(x1 > x2) {
				xTmp = x1;
				yTmp = y1;
				x1 = x2;
				y1 = y2;
				x2 = xTmp;
				y2 = yTmp;
			}
		
			length = x2-x1;		// not really the length :)
			m = ((y2-y1)*200)/length;
			yAlt = y1;
			
			for(i=0; i<=length; i++) {
				y = ((m*i)/200)+y1;
				
				if((m*i)%200 >= 100)
					y++;
				else if((m*i)%200 <= -100)
					y--;
				
				displayDrawLine(x1+i, yAlt, x1+i, y, color);
				
				if(length <= (y2-y1) && y1 < y2)
					yAlt = y+1;
				else if(length <= (y1-y2) && y1 > y2)
					yAlt = y-1;
				else
					yAlt = y;
			}
		
		// angle < 45°
		} else {
			// y1 must be smaller than y2
			if(y1 > y2) {
				xTmp = x1;
				yTmp = y1;
				x1 = x2;
				y1 = y2;
				x2 = xTmp;
				y2 = yTmp;
			}
			
			length = y2-y1;
			m = ((x2-x1)*200)/length;
			yAlt = x1;
			
			for(i=0; i<=length; i++) {
				y = ((m*i)/200)+x1;
				
				if((m*i)%200 >= 100)
					y++;
				else if((m*i)%200 <= -100)
					y--;
				
				displayDrawLine(yAlt, y1+i, y, y1+i, color);
				if(length <= (x2-x1) && x1 < x2)
					yAlt = y+1;
				else if(length <= (x1-x2) && x1 > x2)
					yAlt = y-1;
				else
					yAlt = y;
			}
		}
	}
}

void displayDrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	displayDrawHoriLine(x, y, width, color);				// top
	displayDrawHoriLine(x, y+height, width, color);		// bottom
	displayDrawVertLine(x, y, height, color);			// left
	displayDrawVertLine(x+width, y, height, color);		// right
}

void displayDrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color) {
  	int16_t tSwitch, x1 = 0, y1 = radius;
  	tSwitch = 3 - 2 * radius;
	
	while (x1 <= y1) {
	    displaySetDot(x+radius - x1, y+radius - y1, color);
	    displaySetDot(x+radius - y1, y+radius - x1, color);

	    displaySetDot(x+width-radius + x1, y+radius - y1, color);
	    displaySetDot(x+width-radius + y1, y+radius - x1, color);
	    
	    displaySetDot(x+width-radius + x1, y+height-radius + y1, color);
	    displaySetDot(x+width-radius + y1, y+height-radius + x1, color);

	    displaySetDot(x+radius - x1, y+height-radius + y1, color);
	    displaySetDot(x+radius - y1, y+height-radius + x1, color);

	    if (tSwitch < 0) {
	    	tSwitch += (4 * x1 + 6);
	    } else {
	    	tSwitch += (4 * (x1 - y1) + 10);
	    	y1--;
	    }
	    x1++;
	}
	  	
	displayDrawHoriLine(x+radius, y, width-(2*radius), color);			// top
	displayDrawHoriLine(x+radius, y+height, width-(2*radius), color);	// bottom
	displayDrawVertLine(x, y+radius, height-(2*radius), color);			// left
	displayDrawVertLine(x+width, y+radius, height-(2*radius), color);	// right
}

/*
 * Hardware-Functions 
 */
void displayFillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	uint8_t mask, pageOffset, h, i, data;
	height++;
	
	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;
	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;
	
	displayGotoXY(x, y);
	for(i=0; i<=width; i++) {
		data = displayReadData();
		
		if(color == BLACK) {
			data |= mask;
		} else {
			data &= ~mask;
		}

		displayWriteData(data);
	}
	
	while(h+8 <= height) {
		h += 8;
		y += 8;
		displayGotoXY(x, y);
		
		for(i=0; i<=width; i++) {
			displayWriteData(color);
		}
	}
	
	if(h < height) {
		mask = ~(0xFF << (height-h));
		displayGotoXY(x, y+8);
		
		for(i=0; i<=width; i++) {
			data = displayReadData();
		
			if(color == BLACK) {
				data |= mask;
			} else {
				data &= ~mask;
			}
	
			displayWriteData(data);
		}
	}
}

void displayInvertRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint8_t mask, pageOffset, h, i, data, tmpData;
	height++;
	
	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;
	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;
	
	displayGotoXY(x, y);
	for(i=0; i<=width; i++) {
		data = displayReadData();
		tmpData = ~data;
		data = (tmpData & mask) | (data & ~mask);
		displayWriteData(data);
	}
	
	while(h+8 <= height) {
		h += 8;
		y += 8;
		displayGotoXY(x, y);
		
		for(i=0; i<=width; i++) {
			data = displayReadData();
			displayWriteData(~data);
		}
	}
	
	if(h < height) {
		mask = ~(0xFF << (height-h));
		displayGotoXY(x, y+8);
		
		for(i=0; i<=width; i++) {
			data = displayReadData();
			tmpData = ~data;
			data = (tmpData & mask) | (data & ~mask);
			displayWriteData(data);
		}
	}
}

void displaySetInverted(uint8_t invert) {
	if(displayInverted != invert) {
		displayInvertRect(0,0,127,63);
		displayInverted = invert;
	}
}

void displaySetDot(uint8_t x, uint8_t y, uint8_t color) {
	uint8_t data;
	
	displayGotoXY(x, y-y%8);					// read data from display memory
	data = displayReadData();
	
	if(color == BLACK) {
		data |= 0x01 << (y%8);				// set dot
	} else {
		data &= ~(0x01 << (y%8));			// clear dot
	}
	
	displayWriteData(data);					// write data back to display
}

//
// Font Functions
//

uint8_t displayReadFontData(const uint8_t* ptr) {
	return pgm_read_byte(ptr);
}

void displaySelectFont(const uint8_t* font, displayFontCallback callback, uint8_t color) {
	displayFont = font;
	displayFontRead = callback;
	displayFontColor = color;
}

int displayPutChar(unsigned char c) {
       uint8_t width = 0;
       uint8_t height = displayFontRead(displayFont+FONT_HEIGHT);
       uint8_t bytes = (height+7)/8;
       uint8_t tooMuch = height % 8;
       
       uint8_t firstChar = displayFontRead(displayFont+FONT_FIRST_CHAR);
       uint8_t charCount = displayFontRead(displayFont+FONT_CHAR_COUNT);
       
       uint16_t index = 0;
       uint8_t x = displayCoord.x, y = displayCoord.y;
       
       if(c < firstChar || c >= (firstChar+charCount)) {
               return 1;
       }
       c-= firstChar;
       
       // read width data, to get the index
       for(uint8_t i=0; i<c; i++)
               index += displayFontRead(displayFont+FONT_WIDTH_TABLE+i);
       index = index*bytes+charCount+FONT_WIDTH_TABLE;
       width = displayFontRead(displayFont+FONT_WIDTH_TABLE+c);
       
       // last but not least, draw the character
       for(uint8_t i=0; i<bytes; i++)
       {
               uint8_t page = i*width;
               for(uint8_t j=0; j<width; j++)
               {
                       uint8_t data = displayFontRead(displayFont+index+page+j);
                       
                       if (i + 1 == bytes)
                       {
                               uint8_t pageOld = (i - 1) * width;
                               uint8_t dataOld = displayFontRead(displayFont+index+pageOld+j); //get last byte
                               dataOld >>= tooMuch;
                               data |= dataOld;
                       }
                       
                       if(displayFontColor == BLACK)
                       {
                               displayWriteData(data);
                       } else
                       {
                               displayWriteData(~data);
                       }
               }
               // 1px gap between chars
               if(displayFontColor == BLACK)
               {
                       displayWriteData(0x00);
               }
               else
               {
                       displayWriteData(0xFF);
               }
               if (i + 2 < bytes)
                       displayGotoXY(x, displayCoord.y+8);
               else
                       displayGotoXY(x, displayCoord.y + tooMuch);
       }
       displayGotoXY(x+width+1, y);
       
       return 0;
}

void displayPuts(char* str) {
	int x = displayCoord.x;
	while(*str != 0) {
		if(*str == '\n') {
			displayGotoXY(x, displayCoord.y+displayFontRead(displayFont+FONT_HEIGHT));
		} else {
			displayPutChar(*str);
		}
		str++;
	}
}

void displayPuts_P(PGM_P str) {
	int x = displayCoord.x;
	while(pgm_read_byte(str) != 0) {
		if(pgm_read_byte(str) == '\n') {
			displayGotoXY(x, displayCoord.y+displayFontRead(displayFont+FONT_HEIGHT));
		} else {
			displayPutChar(pgm_read_byte(str));
		}
		str++;
	}
}

uint8_t displayCharWidth(char c) {
	uint8_t width = 0;
	uint8_t firstChar = displayFontRead(displayFont+FONT_FIRST_CHAR);
	uint8_t charCount = displayFontRead(displayFont+FONT_CHAR_COUNT);
	
	// read width data
	if(c >= firstChar && c < (firstChar+charCount)) {
		c -= firstChar;
		width = displayFontRead(displayFont+FONT_WIDTH_TABLE+c)+1;
	}
	
	return width;
}

uint16_t displayStringWidth(char* str) {
	uint16_t width = 0;
	
	while(*str != 0) {
		width += displayCharWidth(*str++);
	}
	
	return width;
}

uint16_t displayStringWidth_P(PGM_P str) {
	uint16_t width = 0;
	
	while(pgm_read_byte(str) != 0) {
		width += displayCharWidth(pgm_read_byte(str++));
	}
	
	return width;
}

void displayGotoXY(uint8_t x, uint8_t y) {
	uint8_t chip = CHIP1, cmd;
	
	if(x > 127) x = 0;								// ensure that coordinates are legal
	if(y > 63)  y = 0;
	
	displayCoord.x = x;								// save new coordinates
	displayCoord.y = y;
	displayCoord.page = y/8;
	
	if(x >= 64) {									// select the right chip
		x -= 64;
		chip = CHIP2;
	}
	cmd = LCD_SET_ADD | x;
	displayWriteCommand(cmd, chip);					// set x address on active chip
	
	cmd = LCD_SET_PAGE | displayCoord.page;			// set y address on both chips
	displayWriteCommand(cmd, CHIP1);
	displayWriteCommand(cmd, CHIP2);
}



inline void displayEnable(void) {
	LCD_CMD_PORT |= 0x01 << EN;						// EN high level width: min. 450ns
	asm volatile("nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 ::);
	LCD_CMD_PORT &= ~(0x01 << EN);
	for(volatile uint8_t i=0; i<30; i++);			// a little delay loop (faster than reading the busy flag)
}

uint8_t displayDoReadData(uint8_t first) {
	uint8_t data;
	volatile uint8_t i;
	
	LCD_DATA_OUT = 0x00;
	LCD_DATA_DIR = 0x00;							// data port is input
	
	if(displayCoord.x < 64) {
		LCD_CMD_PORT &= ~(0x01 << CSEL2);			// deselect chip 2
		LCD_CMD_PORT |= 0x01 << CSEL1;				// select chip 1
	} else if(displayCoord.x >= 64) {
		LCD_CMD_PORT &= ~(0x01 << CSEL1);			// deselect chip 1
		LCD_CMD_PORT |= 0x01 << CSEL2;				// select chip 2
	}
	if(displayCoord.x == 64 && first) {				// chip2 X-address = 0
		displayWriteCommand(LCD_SET_ADD, CHIP2); 	// wuff wuff
	}
	
	LCD_CMD_PORT |= 0x01 << D_I;					// D/I = 1
	LCD_CMD_PORT |= 0x01 << R_W;					// R/W = 1
	
	LCD_CMD_PORT |= 0x01 << EN;						// EN high level width: min. 450ns
	asm volatile("nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 ::);
	
	data = LCD_DATA_IN;								// read Data			 
	
	LCD_CMD_PORT &= ~(0x01 << EN);
	for(i=0; i<8; i++);								// a little delay loop (faster than reading the busy flag)
	
	LCD_DATA_DIR = 0xFF;
	
	displayGotoXY(displayCoord.x, displayCoord.y);
	
	if(displayInverted)
		data = ~data;
	return data;
}

uint8_t displayReadData(void) {
	displayDoReadData(1);							// dummy read
	return displayDoReadData(0);						// "real" read
}

void displayWriteCommand(uint8_t cmd, uint8_t chip) {
	if(chip == CHIP1) {
		LCD_CMD_PORT &= ~(0x01 << CSEL2);			// deselect chip 2
		LCD_CMD_PORT |= 0x01 << CSEL1;				// select chip 1
	} else if(chip == CHIP2) {
		LCD_CMD_PORT &= ~(0x01 << CSEL1);			// deselect chip 1
		LCD_CMD_PORT |= 0x01 << CSEL2;				// select chip 2
	}
	
	LCD_CMD_PORT &= ~(0x01 << D_I);					// D/I = 0
	LCD_CMD_PORT &= ~(0x01 << R_W);					// R/W = 0
	LCD_DATA_DIR = 0xFF;							// data port is output
	LCD_DATA_OUT = cmd;								// write command
	displayEnable();									// enable
	LCD_DATA_OUT = 0x00;
}

void displayWriteData(uint8_t data) {
	uint8_t displayData, yOffset, cmdPort;

#ifdef DEBUG
	volatile uint16_t i;
	for(i=0; i<5000; i++);
#endif

	if(displayCoord.x >= 128)
		return;

	if(displayCoord.x < 64) {
		LCD_CMD_PORT &= ~(0x01 << CSEL2);			// deselect chip 2
		LCD_CMD_PORT |= 0x01 << CSEL1;				// select chip 1
	} else if(displayCoord.x >= 64) {
		LCD_CMD_PORT &= ~(0x01 << CSEL1);			// deselect chip 1
		LCD_CMD_PORT |= 0x01 << CSEL2;				// select chip 2
	}
	if(displayCoord.x == 64)							// chip2 X-address = 0
		displayWriteCommand(LCD_SET_ADD, CHIP2);
	
	LCD_CMD_PORT |= 0x01 << D_I;					// D/I = 1
	LCD_CMD_PORT &= ~(0x01 << R_W);					// R/W = 0
	LCD_DATA_DIR = 0xFF;							// data port is output
	
	
	yOffset = displayCoord.y%8;
	if(yOffset != 0) {
		// first page
		cmdPort = LCD_CMD_PORT;						// save command port
		displayData = displayReadData();
		
		LCD_CMD_PORT = cmdPort;						// restore command port
		LCD_DATA_DIR = 0xFF;						// data port is output
		
		displayData |= data << yOffset;
		if(displayInverted)
			displayData = ~displayData;
		LCD_DATA_OUT = displayData;					// write data
		displayEnable();								// enable
		
		// second page
		displayGotoXY(displayCoord.x, displayCoord.y+8);
		
		displayData = displayReadData();
		
		LCD_CMD_PORT = cmdPort;						// restore command port
		LCD_DATA_DIR = 0xFF;						// data port is output
		
		displayData |= data >> (8-yOffset);
		if(displayInverted)
			displayData = ~displayData;
		LCD_DATA_OUT = displayData;					// write data
		displayEnable();								// enable
		
		displayGotoXY(displayCoord.x+1, displayCoord.y-8);
	} else {
		if(displayInverted)
			data = ~data;
		LCD_DATA_OUT = data;						// write data
		displayEnable();								// enable
		displayCoord.x++;
	}
	LCD_DATA_OUT = 0x00;
}
