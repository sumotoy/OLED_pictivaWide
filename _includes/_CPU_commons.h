#ifndef __CPU_H_
#define __CPU_H_
/*
CPU based Preprocessor directives file.
*/
/* 
--------------------------------------------------------------
			ENERGIA BASED BOARDS
	Partially supported and actually never tested
--------------------------------------------------------------
*/
#if defined(ENERGIA)
	#include "Energia.h"
	#undef byte
	#define byte uint8_t
	#if defined(__TM4C129XNCZAD__) || defined(__TM4C1294NCPDT__)//tiva???
		#define NEEDS_SET_MODULE
		#define _FASTCPU
	#elif defined(__LM4F120H5QR__) || defined(__TM4C123GH6PM__)//stellaris first version
		#define NEEDS_SET_MODULE
		#define _FASTCPU
	#elif defined(__MSP430MCU__)//MSP430???
		// don't know
	#elif defined(TMS320F28069)//C2000???
		// don't know
	#elif defined(__CC3200R1M1RGC__)//CC3200???
		// don't know
	#endif
	static uint8_t SPImodule;
	static uint8_t SPDR;
#elif defined(__AVR__)
/* 
--------------------------------------------------------------
			8 BIT AVR BOARDS (UNO,YUN,LEONARDO,ETC.)
	Fully supported (tested)
--------------------------------------------------------------
*/
	#if !defined(_FORCE_PROGMEM__)
		#define _FORCE_PROGMEM__
	#endif
	#define __PRGMTAG_	PROGMEM
	#include "Arduino.h"
	#include <math.h>
	#include <avr/pgmspace.h>
#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
/* 
--------------------------------------------------------------
			TEENSY 3, TEENSY 3.1, TEENSY 3.2, TEENSY LC
	Fully supported (tested)
--------------------------------------------------------------
*/
	#define ___TEENSYES
	#define _FASTCPU
	#include "Arduino.h"
	#include <avr/pgmspace.h>//Teensy3 and AVR arduinos can use pgmspace.h
	#if defined(_FORCE_PROGMEM__)
		#undef _FORCE_PROGMEM__
		#define PROGMEM __attribute__((section(".progmem.data")))
	#endif
	#define __PRGMTAG_	
#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) //chipkit uno, chipkit max
/* 
--------------------------------------------------------------
			CHIPKIT UNO, CHIPKIT MAX
	Partially supported and never tested
--------------------------------------------------------------
*/
	#define ___CHIPKIT
	#define _FASTCPU
	#include "Arduino.h"
	#ifndef __PGMSPACE_H_
	  #define __PGMSPACE_H_ 1
	  #define PROGMEM
	  #define PGM_P  const char *
	  #define PSTR(str) (str)
	  #define pgm_read_byte_near(addr) pgm_read_byte(addr)
	  #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
	  #define pgm_read_word(addr) (*(const unsigned short *)(addr))
	#endif
	#define __PRGMTAG_	
#elif defined (__arm__) && defined(_VARIANT_ARDUINO_DUE_X_)
/* 
--------------------------------------------------------------
			ARDUINO DUE
	Fully supported (tested)
--------------------------------------------------------------
*/
	#define ___DUESTUFF
	#define _FASTCPU
	#include "Arduino.h"
	#ifndef __PGMSPACE_H_
	  #define __PGMSPACE_H_ 1
	  #define PROGMEM
	  #define PGM_P  const char *
	  #define PSTR(str) (str)
	  #define pgm_read_byte_near(addr) pgm_read_byte(addr)
	  #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
	  #define pgm_read_word(addr) (*(const unsigned short *)(addr))
	#endif
	#define __PRGMTAG_	
#elif defined (__arm__) && defined(__SAM3X8E__)
/* 
--------------------------------------------------------------
			ARDUINO DUE COMPATIBLE
	Fully supported (as DUE, tested)
--------------------------------------------------------------
*/
	#define ___DUESTUFF
	#define _FASTCPU
	#include "Arduino.h"
	#ifndef __PGMSPACE_H_
	  #define __PGMSPACE_H_ 1
	  #define PROGMEM
	  #define PGM_P  const char *
	  #define PSTR(str) (str)
	  #define pgm_read_byte_near(addr) pgm_read_byte(addr)
	  #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
	  #define pgm_read_word(addr) (*(const unsigned short *)(addr))
	#endif
#elif defined(STM32F2XX) || defined(STM32F10X_MD) || defined(STM32_SERIES_F1) || defined(STM32_SERIES_F2)
/* 
--------------------------------------------------------------
			STM32 BOARDS
	Initial support and actually won't compile
--------------------------------------------------------------
*/
	#define ___STM32STUFF
	#include "Arduino.h"
	#if defined(_FORCE_PROGMEM__)
		#undef _FORCE_PROGMEM__
	#endif
	#define __PRGMTAG_	
#elif defined(__arm__) && !defined(__XTENSA__) && !defined(___TEENSYES)
/* 
--------------------------------------------------------------
			ARM generic
	Mistery....
--------------------------------------------------------------
*/
	#if defined(_FORCE_PROGMEM__)
		#undef _FORCE_PROGMEM__
	#endif
	#include "Arduino.h"
	#define __PRGMTAG_	
	#warning "Generic Arm detected, not sure if your board it's compatible!"
#elif defined(__XTENSA__)
/* 
--------------------------------------------------------------
			XTENSA (ESP)
	It compiles but never tested
--------------------------------------------------------------
*/
	#include "Arduino.h"
	#if defined(_FORCE_PROGMEM__)
		#undef _FORCE_PROGMEM__
		#define PROGMEM __attribute__((section(".progmem.data")))
	#endif
	#define __PRGMTAG_	
#else
	#error "your board it's not supported yet!"
#endif


#if defined(SPI_HAS_TRANSACTION)
//SPI transaction enabled library----------------------
	#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
		const static uint32_t MAXSPISPEED	= 30000000UL;  //don't go higher than 22000000!;
	#elif defined(__MKL26Z64__)							 //[Teensy LC] (12 or 24 Mhz max)
		const static uint32_t MAXSPISPEED	= 12000000UL;	 //default SPI main speed TeensyLC
		const static uint32_t MAXSPISPEED2	= 24000000UL;  //don't go higher than 22000000!;
	#elif defined(___DUESTUFF)							 //[DUE]
		const static uint32_t MAXSPISPEED	= 30000000UL;  // try experiment higher values but NOT over 22000000!
		//#define _FASTSSPORT
	// TODO: add more CPU here!
	#else												 //rest of the world (UNO, etc)
		const static uint32_t MAXSPISPEED	= 10000000UL;  //be careful, higher values result in extremely slow rendering!
		#define _FASTSSPORT
	#endif
#else
// legacy SPI library-------------------------------------------------------------
	#if defined(ENERGIA) 
	// LaunchPad, FraunchPad and StellarPad specific
		#if defined(__TM4C129XNCZAD__) || defined(__TM4C1294NCPDT__)//tiva???
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV4
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV8
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV8
		#elif defined(__LM4F120H5QR__) || defined(__TM4C123GH6PM__)//stellaris first version
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV4
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV8
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV8
		#elif defined(__MSP430MCU__)//MSP430???
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV4
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV4
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV8
		#elif defined(TMS320F28069)//C2000???
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV4
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV4
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV8
		#elif defined(__CC3200R1M1RGC__)//CC3200???
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV4
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV4
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV8
		#endif
	#else
	// DUE
		#if defined(___DUESTUFF)
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV4	//84 divided by 4 = 21Mhz
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV8
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV6	//10.5Mhz
			//#define _FASTSSPORT
		#else
		// TODO: Add more CPU here!
	//rest of the world included UNO, etc.
			#define SPI_SPEED_WRITE 	SPI_CLOCK_DIV2	//UNO = 4Mhz
			#define SPI_SPEED_READ 		SPI_CLOCK_DIV4
			#define SPI_SPEED_SAFE 		SPI_CLOCK_DIV2
			#define _FASTSSPORT
		#endif
	#endif
#endif


#include "Print.h"

#endif