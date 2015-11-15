#ifndef __IMAGE_H
	#define __IMAGE_H
	
	#include <stdio.h>
	typedef struct __PRGMTAG_ {
			const uint16_t 	*data;//R5G6B5
			int 			image_width;
			uint8_t			image_height;
			int				image_datalen;
	} tIcon;
#endif
