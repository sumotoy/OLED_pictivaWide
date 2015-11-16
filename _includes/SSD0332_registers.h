#ifndef OLEDpictivaRegisters_H
#define OLEDpictivaRegisters_H

#include "Arduino.h"

const static uint8_t _CMD_SETCOLUMN = 		0x15;//ok
const static uint8_t _CMD_SETROW =    		0x75;//ok
const static uint8_t _CMD_SETCRTSA =    	0x81;//set contrast color A
const static uint8_t _CMD_SETCRTSB =    	0x82;//set contrast color B
const static uint8_t _CMD_SETCRTSC =    	0x83;//set contrast color C
const static uint8_t _CMD_MASTCURR =    	0x87;//master current control
const static uint8_t _CMD_SETREMAP = 		0xA0;//ok
const static uint8_t _CMD_STARTLINE = 		0xA1;//ok
const static uint8_t _CMD_VERTSCROLL = 		0xA2;//ok
const static uint8_t _CMD_NORMALDISPLAY = 	0xA4;//ok
const static uint8_t _CMD_DISPLAYALLON =  	0xA5;//ok
const static uint8_t _CMD_DISPLAYALLOFF = 	0xA6;//ok
const static uint8_t _CMD_INVERTDISPLAY = 	0xA7;//ok
const static uint8_t _CMD_DISPLAYOFFSET = 	0xA2;//ok

const static uint8_t _CMD_MUXRATIO =       	0xA8;//changed adrs
const static uint8_t _CMD_MASTCONF = 		0xAD;//master configuration
const static uint8_t _CMD_DISPLAYOFF = 		0xAE;//ok
const static uint8_t _CMD_DISPLAYON =     	0xAF;//ok
const static uint8_t _CMD_POWSAVE =     	0xB0;//set power save
const static uint8_t _CMD_PHASEADJ =     	0xB1;//phase 1,2 period adj
const static uint8_t _CMD_CLOCKDIV = 		0xB3;//ok
const static uint8_t _CMD_SETGRAY = 		0xB8;//ok
const static uint8_t _CMD_LINGRYTABLE = 	0xB9;//enable linear gray scale table
const static uint8_t _CMD_VPALEVELA = 		0xBB;//level for color A
const static uint8_t _CMD_VPALEVELB = 		0xBC;//level for color B
const static uint8_t _CMD_VPALEVELC = 		0xBD;//level for color C
const static uint8_t _CMD_VCOMH = 			0xBE;//ok
const static uint8_t _CMD_NOP = 			0xE3;//ok
//graphic commands
const static uint8_t _CMD_DRAW_LINE = 		0x21;//
const static uint8_t _CMD_DRAW_RECT = 		0x22;//
const static uint8_t _CMD_DRAW_COPY = 		0x23;//
const static uint8_t _CMD_DRAW_DIMW = 		0x24;//
const static uint8_t _CMD_DRAW_CLRW = 		0x25;//
const static uint8_t _CMD_FILL_MODE = 		0x26;//
#define OP_SCREENW 	288
#define OP_SCREENH 	48
#define OP_HDWMAXW 	95
#define OP_HDWMAXH 	47
#define OP_HRDWMUX	48//63
#define OP_OFFSET 	-1//0x30


#endif