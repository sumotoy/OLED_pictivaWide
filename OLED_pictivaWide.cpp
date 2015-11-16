/*
Please refere to OLED_pictivaWide.h for copyrights!
*/
#include <OLED_pictivaWide.h>


OLED_pictivaWide::OLED_pictivaWide(const uint8_t csPin, const uint8_t dcPin, const uint8_t rstPin)
{
	_rst = rstPin;
	_dc = dcPin;
	_cs = csPin;
}
	
void OLED_pictivaWide::begin(void) {
	_cursorX = 0;
	_cursorY = 0;
	_dcState = HIGH;
	_csState = HIGH;
	_spaceCharWidth = 0;
	_FNTwidth = 0;
	_FNTheight = 0;
	_FNTinterline = 0;
	_wrap = true;
	_txtForeColor = 0xFA;
	_txtBackColor = 0;
	_txtTrasparency = false;
	_fillRegister = 0b00100000;
	SPI.begin();
	pinMode(_cs, OUTPUT);
	pinMode(_rst, OUTPUT);
	pinMode(_dc, OUTPUT);
	#if !defined(SPI_HAS_TRANSACTION)
	//legacy
		SPI.setClockDivider(2);
		delay(1);
		SPI.setDataMode(SPI_MODE0);
	#endif
	digitalWrite(_cs, _csState);
	digitalWrite(_dc, _dcState);
	if (_rst != 255){
		digitalWrite(_rst, LOW);
		delay(50);
		digitalWrite(_rst, HIGH);
		delay(500);
	}
	setContrast(0x80);
	setBrightness(21);
	_opw_send(_CMD_SETREMAP,true);//160
	_opw_send(0b01110010,true);//0b00110011
	/*
A[0]=0, Horizontal address increment (POR)
A[0]=1, Vertical address increment

A[1]=0, Column address 0 is mapped to SEG0 (POR)
A[1]=1, Column address 95 is mapped to SEG0

A[4]=0, Scan from COM 0 to COM [N –1]
A[4]=1, Scan from COM [N-1] to COM0. Where N is the Multiplex ratio.

A[5]=0, Disable COM Split Odd Even (POR)
A[5]=1, Enable COM Split Odd Even

A[7:6]=00; 256 color format = 01; 65k color format(POR)

	0:Vertical address increment			ok
	1:Column address 95 is mapped to SEG0	ok
	2:nc
	3:nc
	4:Scan from COM [N-1] to COM0. Where N is the Multiplex ratio.
	5:Disable COM Split Odd Even (POR)
	6.7:65k color format
	*/
	_opw_send(_CMD_DISPLAYOFFSET,true);
	_opw_send(OP_OFFSET,true);
	//_opw_setAddress(0,63,0,95);
	_opw_send(_CMD_MUXRATIO,true);
	_opw_send(OP_HRDWMUX,true);//63
	_opw_send(_CMD_MASTCONF,true);
	_opw_send(142,true);
	clearScreen();
	
	displayMode(ON);
	delay(100);
	setFont(&arial_x2);
	setCursor(0,0);
}

//OK
uint8_t OLED_pictivaWide::getVerticalOffset(void)
{
	return OP_OFFSET;
}

//OK 0...255
void OLED_pictivaWide::setContrast(uint8_t contrast)
{
	if (_dcState) _opw_setDC(LOW);
	_opw_startSend();
		_opw_transfer8(_CMD_SETCRTSA);
		_opw_transfer8(contrast);
		_opw_transfer8(_CMD_SETCRTSB);
		_opw_transfer8(contrast);
		_opw_transfer8(_CMD_SETCRTSC);
		_opw_transfer8(contrast);
	_opw_endSend();
}

//OK
void OLED_pictivaWide::setFontColor(uint16_t f,uint16_t b)
{
	_txtForeColor = color2grayscale(f);
	_txtBackColor = color2grayscale(b);
	_txtTrasparency = false;
}

//OK
void OLED_pictivaWide::setFontColor(uint16_t f)
{
	_txtForeColor = color2grayscale(f);
	_txtTrasparency = true;
}

//OK 0...63
void OLED_pictivaWide::verticalScroll(uint8_t val)
{
	if (val > 63) val = 63;
	_opw_send(_CMD_VERTSCROLL,true);
	_opw_send(val | 0b10000000,true);
}

//ok (0x0...0x15)(0..21)
void OLED_pictivaWide::setBrightness(byte val)
{
	if (val > 0x15) val = 0x15;
	_opw_send(_CMD_MASTCURR,true);
	_opw_send(val | 0b10000000,true);//1000xxxx
}

//Mmmm, dunno if it's really working, the datasheet is silent about...
void OLED_pictivaWide::powerSafe(bool safeMode)
{
	if (_dcState) _opw_setDC(LOW);
	_opw_startSend();
		_opw_transfer8(_CMD_POWSAVE);
		if (safeMode){
			_opw_transfer8(0b00010010);
			_opw_transfer8(_CMD_DISPLAYOFF);
		} else {
			_opw_transfer8(0);
			_opw_transfer8(_CMD_DISPLAYON);
		}
	_opw_endSend();
}

//OK
void OLED_pictivaWide::clearScreen(void) 
{
	if (_dcState) _opw_setDC(LOW);
	_opw_startSend();
		_opw_transfer8(_CMD_DRAW_CLRW);
		_opw_transfer8(0);
		_opw_transfer8(0);
		_opw_transfer8(OP_HDWMAXW);
		_opw_transfer8(63);
	_opw_endSend();
	delayMicroseconds(400);//increase if there's image flickering
	//undocumented bug, after this command the SSD0332 needs some time to stabilize
}

//OK
void OLED_pictivaWide::clearArea(int sY, int eY, int sX, int eX) 
{
	sX = intCeil(sX,3);
	eX = intCeil(eX,3);
	if (sX > OP_HDWMAXW) sX = OP_HDWMAXW;
	if (eX > OP_HDWMAXW) eX = OP_HDWMAXW;
	if (_dcState) _opw_setDC(LOW);
	_opw_startSend();
		_opw_transfer8(_CMD_DRAW_CLRW);
		_opw_transfer8(sY);
		_opw_transfer8(eY);
		_opw_transfer8(sX);
		_opw_transfer8(eX);
	_opw_endSend();
}

//OK
void OLED_pictivaWide::dimWindow(int sX, int sY, int eX, int eY) 
{
	sX = intCeil(sX,3);
	eX = intCeil(eX,3);
	if (sX > OP_HDWMAXW) sX = OP_HDWMAXW;
	if (eX > OP_HDWMAXW) eX = OP_HDWMAXW;
	if (_dcState) _opw_setDC(LOW);
	_opw_startSend();
		_opw_transfer8(_CMD_DRAW_DIMW);
		_opw_transfer8(sY);
		_opw_transfer8(sX);
		_opw_transfer8(eY);
		_opw_transfer8(eX);
	_opw_endSend();
}

//OK
void OLED_pictivaWide::displayMode(enum OLEDpictivaWideDispMode m) {
	switch(m){
		case ON:
			_opw_send(_CMD_DISPLAYON,true);
			break;
		case OFF:
			_opw_send(_CMD_DISPLAYOFF,true);
			break;
		case NORMAL:
		default:
			_opw_send(_CMD_NORMALDISPLAY,true);
			break;
		case INVERTED:
			_opw_send(_CMD_INVERTDISPLAY,true);
			break;
		case ALL_ON:
			_opw_send(_CMD_DISPLAYALLON,true);
			break;
		case ALL_OFF:
			_opw_send(_CMD_DISPLAYALLOFF,true);
			break;
	}
}

/*
TODO:need fixings
In theory this should be straightforward but because of the osram creative pixel mapping 
was a real challenge, maybe there's better ways but believe me it was a brain crunch!!!
As result, writing a line can be 1 to 3 hardware accellerated macros, not so bad at the end...
Unfortunatly it's not possible (for now) draw diagonal lines due pixel mapping!!!
*/
void OLED_pictivaWide::drawLine(int sX,int sY,int eX,int eY,uint8_t color)
{
	_opw_startSend();
	lineCommandCont(sX,sY,eX,eY,color,color,color);
	_opw_endSend();
	/*
	if (sY >= OP_SCREENH || eY >= OP_SCREENH) eY = OP_SCREENH - 1;
	if (sX >= OP_SCREENW || eX >= OP_SCREENW) eX = OP_SCREENW - 1;
	//calculate y values, osram mapped y pixels in a very creative way...
	int len = 0;
	uint8_t lineColor[3];
	//now dealing with x.
	//the solomon chip can handle only 96 pixels but we have 288 here!
	//osram mapped a column to each r,g,b side of the solomon pixel, result in 288/3=96
	//this allow to control the grey level of every pixel but addressing results a nightmare!
	if (sX > eX) {
		swapValues(sX,eX);
		len = eX - sX + 1;
	} else if (eX == sX) {
		len = 1;
	} else {
		len = eX - sX + 1;
	}
	uint8_t xStartBit = _wichRGBbit(sX);//xLUTable[sX];
	uint8_t xEndBit = 0;
	if (len > 3) {
		_opw_startSend();
		//check how line starts
		if (xStartBit > 2) {
			len--;
			lineCommandCont(sX,sY,sX,eY,0,0,color);
			sX++;
		} else if (xStartBit > 1) {
			len = len - 2;
			lineCommandCont(sX,sY,sX,eY,0,color,color);
			sX++;
		}
		int dv = len;
		uint8_t remaining = 0;
		//calculate the number of divisions
		while (dv % 3) {// check when number will be divisible by 3
			dv--;
		}
		if (dv > 0) {
			uint8_t realPixLen = dv / 3;
			remaining = len - dv;
			//add the remaining pixels (< 3)
			if (remaining > 0) {
				xEndBit = _wichRGBbit(eX);//xLUTable[eX];
				if (xEndBit > 2) {
					lineColor[2] = 0;
					lineColor[1] = 0;
					lineColor[0] = 0;
				} else if (xEndBit > 1) {
					lineColor[2] = 0;
				} else {
					lineColor[2] = 0;
					lineColor[1] = 0;
				}
				lineCommandCont(realPixLen+1,sY,realPixLen+1,eY,lineColor[0],lineColor[1],lineColor[2]);
			}
			//fill the middle line
			lineCommandCont(sX,sY,realPixLen,eY,color,color,color);
			_opw_endSend();
			return;
		} else {
			//this is an exception! A small line going across 2 blocks of 3 pixels
			//the first block it's already here, just need the last block
			xEndBit = _wichRGBbit(eX);//xLUTable[eX];
			if (xEndBit > 2) {
				lineColor[2] = 0;
				lineColor[1] = 0;
				lineColor[0] = 0;
			} else if (xEndBit > 1) {
				lineColor[2] = 0;
			} else {
				lineColor[2] = 0;
				lineColor[1] = 0;
			}
			lineCommandCont(eX/3,sY,eX/3,eY,lineColor[0],lineColor[1],lineColor[2]);
			_opw_endSend();
			return;
		}
	}
	//number too small or remaining pixels
	if (xStartBit > 2) {
		lineColor[2] = 0;
	} else if (xStartBit > 1) {
		lineColor[2] = 0;
		lineColor[1] = 0;
	} else {
		lineColor[2] = 0;
		lineColor[1] = 0;
		lineColor[0] = 0;
	}
	lineCommandCont(sX,sY,sX,eY,lineColor[0],lineColor[1],lineColor[2]);
	_opw_endSend();
	*/
}

//TODO:need fix!
void OLED_pictivaWide::drawFastVLine(int x, int y, int h, uint8_t color)
{
	if (h < 1) h = 1;
	drawLine(x, y, x, h, color);
}


//TODO:almost OK, need check
void OLED_pictivaWide::drawFastHLine(int x, int y, int w, uint8_t c1,uint8_t c2,uint8_t c3)
{
	if (w < 1) return;
	if (y >= OP_SCREENH) y = OP_SCREENH - 1;
	if (x >= OP_SCREENW) x = OP_SCREENW - 1;
	if (x + w >= OP_SCREENW) return;
	x = intCeil(x,3);
	w = intCeil(w,3);
	if (w < 3) w = 1;
	if (_dcState) _opw_setDC(LOW);//command
	_opw_startSend();
	lineCommandCont(x,y,x+w,y,c1,c2,c3);
	_opw_endSend();
}

//TODO:almost OK, need check
void OLED_pictivaWide::drawFastHLine(int x, int y, int w, uint8_t c)
{
	if (w < 1) return;
	if (y >= OP_SCREENH) y = OP_SCREENH - 1;
	if (x >= OP_SCREENW) x = OP_SCREENW - 1;
	if (x+w >= OP_SCREENW) return;
	x = intCeil(x,3);
	w = intCeil(w,3);
	if (w < 3) w = 1;
	if (_dcState) _opw_setDC(LOW);//command
	_opw_startSend();
	lineCommandCont(x,y,x+w,y,c,c,c);
	_opw_endSend();
}

//OK
void OLED_pictivaWide::lineCommandCont(uint8_t sX,uint8_t sY,uint8_t eX,uint8_t eY,uint8_t cA,uint8_t cB,uint8_t cC)
{
	_opw_transfer8(_CMD_DRAW_LINE);
	_opw_transfer8(sX);_opw_transfer8(sY);_opw_transfer8(eX);_opw_transfer8(eY);
	_opw_transfer8(cA);_opw_transfer8(cB);_opw_transfer8(cC);
}


//TODO:almost OK, need check
void OLED_pictivaWide::drawRect(int x,int y,int w,int h,uint8_t borderC,uint8_t insideC)
{
	if (w < 1) return;
	if (y >= OP_SCREENH) y = OP_SCREENH - 1;
	if (x >= OP_SCREENW) x = OP_SCREENW - 1;
	if (x + w >= OP_SCREENW) return;
	if (y + h >= OP_SCREENH) return;
	x = intCeil(x,3);
	w = intCeil(w,3);
	if (w < 3) w = 1;
	if (_dcState) _opw_setDC(LOW);//command
	_opw_startSend();
	rectCommandCont(x,y,x + w,y + h,borderC,borderC,borderC,insideC,insideC,insideC,false);
	_opw_endSend();
	delayMicroseconds(100);
}

//TODO:almost OK, need check
void OLED_pictivaWide::fillRect(int x,int y,int w,int h,uint8_t borderC,uint8_t insideC)
{
	if (w < 1) return;
	if (y >= OP_SCREENH) y = OP_SCREENH - 1;
	if (x >= OP_SCREENW) x = OP_SCREENW - 1;
	if (x + w >= OP_SCREENW) return;
	if (y + h >= OP_SCREENH) return;
	x = intCeil(x,3);
	w = intCeil(w,3);
	if (w < 3) w = 1;
	if (_dcState) _opw_setDC(LOW);//command
	_opw_startSend();
	rectCommandCont(x,y,x + w,y + h,borderC,borderC,borderC,insideC,insideC,insideC,true);
	_opw_endSend();
}

//OK
void OLED_pictivaWide::rectCommandCont(uint8_t sX,uint8_t sY,uint8_t eX,uint8_t eY,
							uint8_t bcol_cA,uint8_t bcol_cB,uint8_t bcol_cC,
							uint8_t incol_cA,uint8_t incol_cB,uint8_t incol_cC,bool fill)
{
	if (fill && !bitRead(_fillRegister,0)){
		_opw_transfer8(_CMD_FILL_MODE);
		bitSet(_fillRegister,0);
		_opw_transfer8(_fillRegister);
	} else if (!fill && bitRead(_fillRegister,0)){
		_opw_transfer8(_CMD_FILL_MODE);
		bitClear(_fillRegister,0);
		_opw_transfer8(_fillRegister);
	}
	_opw_transfer8(_CMD_DRAW_RECT);
	_opw_transfer8(sX);_opw_transfer8(sY);_opw_transfer8(eX);_opw_transfer8(eY);
	_opw_transfer8(bcol_cA);_opw_transfer8(bcol_cB);_opw_transfer8(bcol_cC);
	_opw_transfer8(incol_cA);_opw_transfer8(incol_cB);_opw_transfer8(incol_cC);
}


//TODO:almost OK, need check
void OLED_pictivaWide::setCursor(uint8_t col, uint8_t row) {
	_cursorX = col * _spaceCharWidth;
	_cursorY = row * (_FNTheight + _FNTinterline);

}

//OK
uint8_t OLED_pictivaWide::getCursorX(void)
{
	return _cursorX;
}

//OK
uint8_t OLED_pictivaWide::getCursorY(void)
{
	return _cursorY;
}

//TODO:almost OK, need check
uint8_t OLED_pictivaWide::getFontWidth(boolean inColums) 
{
	if (_FNTwidth < 1) return 0; //variable with
	if (inColums){
		return (OP_SCREENW / _FNTwidth);
	} else {
		return _FNTwidth;
	}
}

//TODO:almost OK, need check
uint8_t OLED_pictivaWide::getFontHeight(boolean inRows) 
{
	if (inRows){
		return (OP_SCREENH / _FNTheight);
	} else {
		return _FNTheight;
	}
}


/*
	OK, test first with 8 bit arduino
	This helper check if the char it's in the library
*/
int OLED_pictivaWide::_getCharCode(uint8_t ch)
{
	int i;
	for (i=0;i<_currentFont->length;i++){//search for char code
		if (_currentFont->chars[i].char_code == ch) return i;
	}//i
	return -1;
}

/*
	OK, need test, actually unused!
	This function calculate precisely the lenght of a string
	it actually not used!
*/
int OLED_pictivaWide::_STRlen_helper(const char* buffer,int len)
{
	int charIndex = -1;
	int i;
	if (len == 0) len = strlen(buffer);		//try to get data from string
	if (len == 0) return 0;					//better stop here
	if (_FNTwidth > 0){						// fixed width font
		return ((len * _spaceCharWidth));
	} else {								// variable width, need to loop trough entire string!
		int totW = 0;
		for (i = 0;i < len;i++){			//loop trough buffer
			if (buffer[i] == 32){			//a space
				totW += _spaceCharWidth;
			} else if (buffer[i] != 13 && buffer[i] != 10 && buffer[i] != 32){//avoid special char
				charIndex = _getCharCode(buffer[i]);
				if (charIndex > -1) {		//found!
					#if defined(_FORCE_PROGMEM__)
						totW += (PROGMEM_read(&_currentFont->chars[charIndex].image->image_width));
					#else
						totW += (_currentFont->chars[charIndex].image->image_width);
					#endif
				}
			}//inside permitted chars
		}//buffer loop
		return totW;						//return data
	}//end variable w font
}

/*
	OK
	This function set the current font and prepare some variable that will help
	other functions to handle text.
*/
void OLED_pictivaWide::setFont(const tFont *font) 
{
	_currentFont = font;
	_FNTheight = 		_currentFont->font_height;
	_FNTwidth = 		_currentFont->font_width;//if 0 it's variable width font
	//get all needed infos
	if (_FNTwidth > 0){
		_spaceCharWidth = _FNTwidth;
	} else {
		//_FNTwidth will be 0 to inform other functions that this it's a variable w font
		// We just get the space width now...
		int temp = _getCharCode(0x20);
		if (temp > -1){
			#if defined(_FORCE_PROGMEM__)
			_spaceCharWidth = PROGMEM_read(&_currentFont->chars[temp].image->image_width);
			#else
			_spaceCharWidth = (_currentFont->chars[temp].image->image_width);
			#endif
		} else {
			//font malformed, doesn't have needed space parameter
			//will return to system font
			setFont(&arial_x2);
			return;
		}
	}
}


/*
	OK
	This function just write a string, it's really simple because the 99.9% of the job
	it's actually done by other functions!
*/
void OLED_pictivaWide::_textWrite(const char* buffer, uint16_t len)
 {
	uint16_t i;
	if (len == 0) len = strlen(buffer);//try get the info from the buffer
	if (len == 0) return;//better stop here, the string it's really empty!
	#if defined(__TXTBENCH)
		unsigned long start = micros();
	#endif
	//Loop trough every char and write them one by one...
	_opw_startSend();
	for (i=0;i<len;i++){
		_charWriteR(buffer[i]);   // user fonts
	}//end loop
	#if defined(__TXTBENCH)
	  unsigned long result = micros() - start;
	  Serial.print("Text Rendered in:");
	  Serial.print(result);
	  Serial.print(" ms");
	  Serial.print("\n");
	#endif
	if (_dcState) _opw_setDC(LOW);
	_opw_transfer8(_CMD_NOP);//dunno why but fill the final gap of 1 pixel!
	_opw_endSend();
}


/*
OK
 The following function identify the char and set the correct values of x,y
*/
void OLED_pictivaWide::_charWriteR(const char c)
{
	int p;
	uint8_t i;
	if (_cursorY < 1) _cursorY = 1;//temporary fix...
	if (c == 13){//------------------------------- CARRIAGE ----------------------------------
		//ignore
	} else if (c == 10){//------------------------- NEW LINE ---------------------------------
		_cursorX = 0;
		_cursorY += _FNTheight + _FNTinterline;
	} else if (c == 32){//--------------------------- SPACE ---------------------------------
		if (!_txtTrasparency){//!
			//_opw_startSend();
			for (i=0;i<_FNTheight-1;i++){
				_opw_setAddress(_cursorY+i,_cursorY+i, _cursorX,_cursorX + _spaceCharWidth/3,true);
				if (!_dcState) _opw_setDC(HIGH);
				for (p=0;p<_spaceCharWidth/3;p++){
					_opw_transfer16(((_txtBackColor >> 3) << 11) | ((_txtBackColor >> 3) << 6) | (_txtBackColor >> 3));
				}
			}
			//_opw_endSend();
		}
		_cursorX += _spaceCharWidth/3;
	} else {//-------------------------------------- CHAR ------------------------------------
		int charIndex = _getCharCode(c);//get char code
		if (charIndex > -1){//valid?
			//check if goes out of screen and goes to a new line (if wrap) or just avoid
			#if defined(_FORCE_PROGMEM__)
				int charW =   PROGMEM_read(&_currentFont->chars[charIndex].image->image_width);
			#else
				int charW =  _currentFont->chars[charIndex].image->image_width;
			#endif
			if (_wrap){
				if (_cursorX + charW/3 > OP_SCREENW/3){
					_cursorX = 0;
					_cursorY += _FNTheight + _FNTinterline;
				}
			} else {
				if (_cursorX + charW/3 >= OP_SCREENW/3) return;
			}
			//-------------------------Actual single char drawing here -----------------------------------
			_drawChar_unc(_cursorX,_cursorY,charIndex,charW);
		}//end valid
	}//end char
}

/*
	OK
	This is the char render algorithm, it's inspired partially to the RA8875 font render code
	that was created by myself. It's resonable fast, can be slight faster but code complexity will suffer
	so in this release I will leave like this. It's pretty powerful, can render transparent font or not.
	Due the weird hardware design of this display the code it's not standard so it will not work with other display.
*/
void OLED_pictivaWide::_drawChar_unc(int16_t x,int16_t y,int index,int charW)
{
	//start by getting some glyph data...
	#if defined(_FORCE_PROGMEM__)
		const uint8_t * charGlyp = PROGMEM_read(&_currentFont->chars[index].image->data);//char data
		int			  totalBytes = PROGMEM_read(&_currentFont->chars[index].image->image_datalen);
	#else
		const uint8_t * charGlyp = _currentFont->chars[index].image->data;
		int			  totalBytes = _currentFont->chars[index].image->image_datalen;
	#endif
	int i,p;
	uint8_t temp = 0;
	//bool needEnd = true;
	uint8_t charWReal = charW/3;
	//some basic variable...
	uint8_t currentXposition = 0;//the current position of the writing cursor in the x axis, from 0 to charW
	uint8_t currentYposition = 0;//the current position of the writing cursor in the y axis, from 1 to _FNTheight
	int currentByte = 0;//the current byte in reading (from 0 to totalBytes)
	bool lineBuffer[charW];//the temporary line buffer (will be _FNTheight each char)
	int lineChecksum = 0;//part of the optimizer
	//the main loop that will read all bytes of the glyph
	
	while (currentByte < totalBytes){
		//read n byte
		#if defined(_FORCE_PROGMEM__)
			temp = PROGMEM_read(&charGlyp[currentByte]);
		#else
			temp = charGlyp[currentByte];
		#endif
		for (i = 7;i >= 0;i --){//scan byte
			//----------------------------------- exception
			if (currentXposition >= charW){//at every fontW
				//line buffer has been filled!
				currentXposition = 0;//reset the line x position
				_opw_setAddress(y + currentYposition,y + currentYposition,x,x + charWReal,true);
				if (!_dcState) _opw_setDC(HIGH);//prepare for data stream
				if (lineChecksum < 1){//empty line
					//jump down 1 row!
					if (!_txtTrasparency){
						for (p = 0;p < charWReal;p ++){
							_opw_transfer16(((_txtBackColor >> 3) << 11) | ((_txtBackColor >> 3) << 6) | (_txtBackColor >> 3));
						}
					}
				} else if (lineChecksum == charW){//full line
					for (p = 0;p < charWReal;p ++){
						_opw_transfer16(((_txtForeColor >> 3) << 11) | ((_txtForeColor >> 3) << 6) | (_txtForeColor >> 3));
					}
				} else { //line render
					for (p = 0;p < charW;p += 3) {//every 3 pixels
						uint16_t c1 = _txtBackColor;
						uint16_t c2 = _txtBackColor;
						uint16_t c3 = _txtBackColor;
						if (lineBuffer[p]) 		c1 = _txtForeColor;
						if (lineBuffer[p+1]) 	c2 = _txtForeColor;
						if (lineBuffer[p+2]) 	c3 = _txtForeColor;
						_opw_transfer16(((c1 >> 3) << 11) | ((c2 >> 3) << 6) | (c3 >> 3));	
					}		
				}
				currentYposition++;//next line
				lineChecksum = 0;//reset checksum
			}//end exception
			//-------------------------------------------------------
			lineBuffer[currentXposition] = bitRead(temp,i);//continue fill line buffer
			lineChecksum += lineBuffer[currentXposition];
			currentXposition++;
		}
		currentByte++;
	}
	_cursorX += charWReal;
	_cursorY = y;
}


/*
	OK
	This function has been rewritten many times, it's really a challenge send in stream
	a 288x48 image to a 96x64 chip and convert on the fly full 24 bit color images into 5 bit grayscale,
	fast and without using divisions or if..then and so on.
	I've used tons of shift instead, the result it's a blazing fast display of a 288x48 image!
	I'm proud of the semplicity of this function, simple and fast, but this is the result of several attempts!
	NOTE: The width of the icon SHOULD BE A MULTIPLE OF 3 due hardware limitations
*/
void OLED_pictivaWide::drawIcon(int x, int y,const tIcon *icon)
{
	//get data
	#if defined(_FORCE_PROGMEM__)
		const uint16_t * iconData = PROGMEM_read(&icon->data);//char data
		int			  iWidth     = PROGMEM_read(&icon->image_width);
		uint8_t 	  iHeight    = PROGMEM_read(&icon->image_height);
		int 		  datalen	 = PROGMEM_read(&icon->image_datalen);
	#else
		const uint16_t * iconData = icon->data;//char data
		int			  iWidth     = icon->image_width;
		uint8_t 	  iHeight    = icon->image_height;
		int 		  datalen	 = icon->image_datalen;
	#endif
	//before continue, better execute some tests
	if (iWidth % 3 != 0) return; //cannot continue if number it's not a multiple of 3!
	iWidth = (iWidth/3) - 1;
	//x = intCeil(x,3);
	//if (iWidth > OP_HDWMAXW) iWidth = OP_HDWMAXW;
	//if (iHeight > OP_HDWMAXH) iHeight = OP_HDWMAXH;
	//if (x + iWidth > OP_HDWMAXW) return;
	//if (y + iHeight > OP_HDWMAXH) return;
	//if we are here, time to render
	_opw_startSend();
		_opw_setDC(LOW);//command
			//set area
			_opw_transfer8(_CMD_SETROW);
			_opw_transfer8(y);_opw_transfer8(y + iHeight);
			_opw_transfer8(_CMD_SETCOLUMN);
			_opw_transfer8(x);_opw_transfer8(x + iWidth);
		_opw_setDC(HIGH);//data
	int current = 0;
		while (current < datalen){//data stream
			_opw_transfer16(((color2grayscale(iconData[current]) >> 3) << 11) | ((color2grayscale(iconData[current+1]) >> 3) << 6) | (color2grayscale(iconData[current+2]) >> 3));//send 3 pixels in one time!
			current += 3;
		}
	_opw_endSend();
}



