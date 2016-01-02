/*
A Fast and Optimized library for Pictiva Oled 288x48 drived by Solomon SSD0332, for Teensy's and Arduinos.
Version:1.2
-----------------------------------------------------------------------------------------------------------
Copyright 2015 .s.u.m.o.t.o.y. and Max MC Costa, all rights reserved!
-----------------------------------------------------------------------------------------------------------
This library it's only for personal use and cannot be copied, distributed or selled. 
Any commercial products that use this library need a special licence from the Author, 
the distribution of the library together with products it's forbidden.
Code and any it's part cannot be copied and ported to other libraries.
The library and the entire code has been developed by Max MC Costa in October 2015.
If you use (only personal NOT commercial use allowed) you must leave intact any comment included this header.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PRO (and say thanks to this library!):
 - Uses only 4 wires (plus 1 if you want reset).
 - Fast screen operations.
 - High quality display.
 - Fast operations.
 - Can use 5 bit Grayscale
 - Many fonts, even large.
 - Stream capabilities.
 - Works nice with other SPI devices on the same line.
 
CONS (most hardware design limitations):
 - Everithing on x axis must be multiple of 3! (hardware limitations).
 - Almost impossible write a single pixel, only stream of pixels it's possible (hardware limitations).
 - No way to draw oblique lines of 1 pixel (hardware limitations).
 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Note from the author:
The Pictiva 288x48 it's a retired product and this library was intended for my personal use only 
but I got pressure from some friend to share for let them use in their stuff, unfortunatly some Ebay seller got
some stock of this product and asked to use this library for sell more display (at higher price), I'm not happy
with this so I will persecute legally any possible use of this library outside my purposes...
Please note that this is the ONLY working library for this specific OLED! 
There's another library very limited that works partially in a completely different way, it's so different 
that it's not possible integrate some of my code to fix the other library, 
this mean that I spend a lot of time around this 'undocumented' chip and display 
to get the right way to go (a lot of reverse engineering), the guy who developed the other library failed probably
because not understand fully how chip works and how it's wired to the display.
*/

#ifndef OLEDpictivaWide_H
#define OLEDpictivaWide_H

#include "_includes/_CPU_commons.h"
#include "_includes/SSD0332_registers.h"
#include "_includes/SSD0332_fontDescription.h"
#include "_includes/SSD0332_imageDescription.h"
#include <SPI.h>
#include "_fonts/arial_x2.c"


//#define __TXTBENCH


#if defined(_FORCE_PROGMEM__)
/*
template <typename T> T PROGMEM_get (const T * sce)
  {
  static T temp;
  memcpy_P (&temp, sce, sizeof (T));
  return temp;
  }
*/  
  
template <typename T> void PROGMEM_read (const T * sce, T& dest)
  {
		memcpy_P (&dest, sce, sizeof (T));
  }
#endif

#if !defined(swapValues)
	#define swapValues(a, b) { typeof(a) t = a; a = b; b = t; }
#endif



enum OLEDpictivaWideDispMode {ON=0,OFF,NORMAL,INVERTED,ALL_ON,ALL_OFF };

class OLED_pictivaWide : public Print {
   public:
   OLED_pictivaWide(const uint8_t csPin, const uint8_t dcPin, const uint8_t rstPin=255);
	void 		begin(void);//OK
	void 		setContrast(uint8_t contrast=128);//OK
	void 		clearScreen(void);//OK
	void 		clearArea(int sY, int eY, int sX, int eX);
	//TODO:clearWindow
	void 		displayMode(enum OLEDpictivaWideDispMode m=NORMAL);//OK
	void 		setCursor(uint8_t col, uint8_t row);//OK
	uint8_t 	getCursorX(void);
	uint8_t 	getCursorY(void);
	void 		setFontColor(uint16_t f,uint16_t b);
	void 		setFontColor(uint16_t f);
	void 		setBrightness(byte val);//TODO:small fix
	void 		verticalScroll(uint8_t val);
	void 		drawFastVLine(int x, int y, int h, uint8_t color);
	void 		drawFastHLine(int x, int y, int w, uint8_t c1,uint8_t c2,uint8_t c3);//OK
	void 		drawFastHLine(int x, int y, int w, uint8_t c);//OK
	void 		drawRect(int x,int y,int w,int h,uint8_t borderC,uint8_t insideC);
	void 		fillRect(int x,int y,int w,int h,uint8_t borderC,uint8_t insideC);
	void 		drawIcon(int x, int y,const tIcon *icon);
	void 		dimWindow(int sX, int sY, int eX, int eY);
	void 		powerSafe(bool safeMode);//TODO: not working
	uint8_t 	getVerticalOffset(void);//OK
	void 	drawLine(int sX,int sY,int eX,int eY,uint8_t color);
	//inline uint16_t Color565(uint8_t r,uint8_t g,uint8_t b) { return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); }
	void 		setFont(const tFont *font);
	uint8_t 	getFontHeight(boolean inRows);
	uint8_t 	getFontWidth(boolean inColums);
	virtual size_t 	write(uint8_t b) { _textWrite((const char *)&b, 1); return 1;}
	virtual size_t  write(const uint8_t *buffer, size_t size) {_textWrite((const char *)buffer, size); return size;}

protected:
	volatile bool 				  _dcState;
	volatile bool 				  _csState;
	uint8_t 					  _cursorX;
	uint8_t 					  _cursorY;
	uint8_t						  _txtForeColor;
	uint8_t						  _txtBackColor;
	bool						  _txtTrasparency;
	uint8_t						  _FNTwidth, 		  _FNTheight;
	int							  _spaceCharWidth;
	uint8_t						  _FNTinterline;
	bool						  _wrap;
	uint8_t						  _fillRegister;
	
	/* ------------------- Low Level SPI ------------------------- */
	//TODO -> Not all MCU can handle this
	inline __attribute__((always_inline))
	void _opw_startTransaction(void) {
		#if defined(SPI_HAS_TRANSACTION)
			SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
		#endif
	}
	
	//TODO -> Not all MCU can handle this
	inline __attribute__((always_inline))
	void _opw_endTransaction(void) {
		#if defined(SPI_HAS_TRANSACTION)
			SPI.endTransaction();
		#endif
	}
	
	inline __attribute__((always_inline)) 
	void _opw_setDC(bool state) {
		if (_dcState != state){
			_dcState = state;
			#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
				digitalWriteFast(_dc, _dcState);
			#else
				digitalWrite(_dc, _dcState);
			#endif
		}
	}

	inline __attribute__((always_inline)) 
	void _opw_setCS(bool state) {
		if (_csState != state){
			_csState = state;
			#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
				digitalWriteFast(_cs, _csState);
			#else
				digitalWrite(_cs, _csState);
			#endif
		}
	}
	
	//TODO -> Not all MCU can handle this
	inline __attribute__((always_inline)) 
	void _opw_transfer16(uint16_t data) {
	#if defined(___SPILEGACY)
		SPI.transfer(data >> 8);
		SPI.transfer(data & 0xFF);
	#else	
		SPI.transfer16(data);
	#endif
	}
	
	inline __attribute__((always_inline)) 
	void _opw_transfer8(uint8_t data) {
		SPI.transfer(data);
	}
	
	inline __attribute__((always_inline)) 
	void _opw_startSend(void) {
		_opw_startTransaction();
		_opw_setCS(LOW);
	}
	
	inline __attribute__((always_inline)) 
	void _opw_endSend(void) {
		_opw_setCS(HIGH);
		_opw_endTransaction();
	}
	

	inline __attribute__((always_inline)) 
	void _opw_send(byte cmd,bool isCmd) {
		if (isCmd && _dcState){
			_opw_setDC(LOW);
		} else if (!isCmd && !_dcState){
			_opw_setDC(HIGH);
		}			
		_opw_startSend();
			_opw_transfer8(cmd);
		_opw_endSend();	
	}
	

	inline __attribute__((always_inline)) 
	void _opw_sendData16(word data) {
		_opw_setDC(HIGH);
		_opw_startSend();
			_opw_transfer16(data);
		_opw_endSend();	
	}
	
	/* ----------------------- Low Level Commands ------------------------ */
	
	inline __attribute__((always_inline)) 
	void _opw_setX(uint8_t xStart, uint8_t xEnd) {//0..95 
		if (_dcState) _opw_setDC(LOW);
		_opw_startSend();
			_opw_transfer8(_CMD_SETCOLUMN);
			_opw_transfer8(xStart);_opw_transfer8(xEnd);
		_opw_endSend();
	}
	
	inline __attribute__((always_inline)) 
	void _opw_setY(uint8_t yStart, uint8_t yEnd) {//0..63
		if (_dcState) _opw_setDC(LOW);
		_opw_startSend();
			_opw_transfer8(_CMD_SETROW);
			_opw_transfer8(yStart);_opw_transfer8(yEnd);
		_opw_endSend();
	}
	
	inline __attribute__((always_inline)) 
	void _opw_setX(uint8_t x) {//0..95 
		_opw_setX(x,x); 
	}
	
	inline __attribute__((always_inline)) 
	void _opw_setY(uint8_t y) {//0..63
		_opw_setY(y,y); 
	}
	
	inline __attribute__((always_inline)) 
	void _opw_setAddress(uint8_t yStart, uint8_t yEnd, uint8_t xStart, uint8_t xEnd,bool continued=false) {
		if (_dcState) _opw_setDC(LOW);
		if (!continued) _opw_startSend();
			_opw_transfer8(_CMD_SETROW);
			_opw_transfer8(yStart);_opw_transfer8(yEnd);
			_opw_transfer8(_CMD_SETCOLUMN);
			_opw_transfer8(xStart);_opw_transfer8(xEnd);
		if (!continued) _opw_endSend();
	}
	
	//3987 -> 2321(1813)

	
	//here's the column decoder algorithm for this damn pictiva oled
	//this time return only witch r,g,b pixel (named 1,2,3) correspond a number
	inline __attribute__((always_inline)) 
	uint8_t _wichRGBbit(int x){
		if (x % 3 == 0) {
			return 1;
		} else {
			int temp = x;
			while(temp % 3){ temp--; } 
			return x-temp + 1;
		}
	}
	
	/*
	This is not exact but resonable usable, it uses only shift and multiples to get fast conversion
	*/
	inline __attribute__((always_inline)) 
	int color2grayscale(unsigned int c) {
		if (c < 1) return 0;
		if (c > 0xFFFE) return 0xFA;
		//return (19595 * (((c >> 11) << 3) & 0xFF) + 38470 * (((c >> 5) << 2) & 0xFF) + 7471 * ((c << 3) & 0xFF)) >> 16;
		return (0x4C8B * (((c >> 11) << 3) & 0xFF) + 0x9646 * (((c >> 5) << 2) & 0xFF) + 0x1D2F * ((c << 3) & 0xFF)) >> 16;
	}
	
	/*
	Some simple math in action, divide by a number and it give back an integer
	but using kinda ceil (in excess). So divide 20 by 3 will give back 7 (6.66...)
	I used extensively for get the right pixel in the x axys...
	*/
	inline __attribute__((always_inline)) 
	int intCeil(int num,int div) {
		if (num < div) return 0;
		return 1 + ((num - 1) / div);
	}
	
private:
	void 		  lineCommandCont(uint8_t sX,uint8_t sY,uint8_t eX,uint8_t eY,uint8_t cA,uint8_t cB,uint8_t cC);
	void 		  rectCommandCont(uint8_t sX,uint8_t sY,uint8_t eX,uint8_t eY,uint8_t bcol_cA,uint8_t bcol_cB,uint8_t bcol_cC,uint8_t incol_cA,uint8_t incol_cB,uint8_t incol_cC,bool fill);
    uint8_t 	  _cs;
    uint8_t 	  _dc;
    uint8_t 	  _rst;
	const tFont   *  _currentFont;
	int 	  	  _STRlen_helper(const char* buffer,int len);
	int 		  _getCharCode(uint8_t ch);
	void 		  _textWrite(const char* buffer, uint16_t len);
	void 		  _charWriteR(const char c);
	void 		  _drawChar_unc(int16_t x,int16_t y,int index,int charW);
};
//here's the elapsedMillis from Paul Stoffregen, Teensy has already in core but some micro not.
//since library uses this function I've provided it and it will automatically included if needed.
#ifndef elapsedMillis_h
#define elapsedMillis_h
#ifdef __cplusplus
/* Elapsed time types - for easy-to-use measurements of elapsed time
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2011 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

class elapsedMillis
{
private:
	unsigned long ms;
public:
	elapsedMillis(void) { ms = millis(); }
	elapsedMillis(unsigned long val) { ms = millis() - val; }
	elapsedMillis(const elapsedMillis &orig) { ms = orig.ms; }
	operator unsigned long () const { return millis() - ms; }
	elapsedMillis & operator = (const elapsedMillis &rhs) { ms = rhs.ms; return *this; }
	elapsedMillis & operator = (unsigned long val) { ms = millis() - val; return *this; }
	elapsedMillis & operator -= (unsigned long val)      { ms += val ; return *this; }
	elapsedMillis & operator += (unsigned long val)      { ms -= val ; return *this; }
	elapsedMillis operator - (int val) const           { elapsedMillis r(*this); r.ms += val; return r; }
	elapsedMillis operator - (unsigned int val) const  { elapsedMillis r(*this); r.ms += val; return r; }
	elapsedMillis operator - (long val) const          { elapsedMillis r(*this); r.ms += val; return r; }
	elapsedMillis operator - (unsigned long val) const { elapsedMillis r(*this); r.ms += val; return r; }
	elapsedMillis operator + (int val) const           { elapsedMillis r(*this); r.ms -= val; return r; }
	elapsedMillis operator + (unsigned int val) const  { elapsedMillis r(*this); r.ms -= val; return r; }
	elapsedMillis operator + (long val) const          { elapsedMillis r(*this); r.ms -= val; return r; }
	elapsedMillis operator + (unsigned long val) const { elapsedMillis r(*this); r.ms -= val; return r; }
};

class elapsedMicros
{
private:
	unsigned long us;
public:
	elapsedMicros(void) { us = micros(); }
	elapsedMicros(unsigned long val) { us = micros() - val; }
	elapsedMicros(const elapsedMicros &orig) { us = orig.us; }
	operator unsigned long () const { return micros() - us; }
	elapsedMicros & operator = (const elapsedMicros &rhs) { us = rhs.us; return *this; }
	elapsedMicros & operator = (unsigned long val) { us = micros() - val; return *this; }
	elapsedMicros & operator -= (unsigned long val)      { us += val ; return *this; }
	elapsedMicros & operator += (unsigned long val)      { us -= val ; return *this; }
	elapsedMicros operator - (int val) const           { elapsedMicros r(*this); r.us += val; return r; }
	elapsedMicros operator - (unsigned int val) const  { elapsedMicros r(*this); r.us += val; return r; }
	elapsedMicros operator - (long val) const          { elapsedMicros r(*this); r.us += val; return r; }
	elapsedMicros operator - (unsigned long val) const { elapsedMicros r(*this); r.us += val; return r; }
	elapsedMicros operator + (int val) const           { elapsedMicros r(*this); r.us -= val; return r; }
	elapsedMicros operator + (unsigned int val) const  { elapsedMicros r(*this); r.us -= val; return r; }
	elapsedMicros operator + (long val) const          { elapsedMicros r(*this); r.us -= val; return r; }
	elapsedMicros operator + (unsigned long val) const { elapsedMicros r(*this); r.us -= val; return r; }
};

#endif // __cplusplus
#endif // elapsedMillis_h

#endif


