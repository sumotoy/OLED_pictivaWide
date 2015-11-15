
/*******************************************************************************

* name: battery_x2
* family: MS Shell Dlg 2
* size: 14
* style: Normal
* --------------------------------------
* included characters:  012345
* --------------------------------------
* antialiasing: no
* type: proportional
* encoding: latin0
* unicode bom: no
*
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Edge 144
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: yes
* ------------------------------------------------------------------------------
* Created by a custom template of LCD-Image-Converter for .s.u.m.o.t.o.y. RA8875
* Font template version: 2.0
* Note: Font height should be fixed and all glyps must have the same height!
* ------------------------------------------------------------------------------
* Designed by sumotoy, freem for using with this library.
* 0:empty battery, 5:full
*******************************************************************************/



#include <stdint.h>



static const uint8_t image_data_battery_x2_0x20[1] __PRGMTAG_  = {
    0x00
};////character: ' '

static const tImage battery_x2_0x20 __PRGMTAG_ = { image_data_battery_x2_0x20,
    6, 1};//character: ' ' , height: 13, (charW,total bytes)

static const uint8_t image_data_battery_x2_0x30[15] __PRGMTAG_  = {
    0x3e, 0x11, 0x3f, 0xf0, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x1f, 0xf8
};////character: '0'

static const tImage battery_x2_0x30 __PRGMTAG_ = { image_data_battery_x2_0x30,
    9, 15};//character: '0' , height: 13, (charW,total bytes)

static const uint8_t image_data_battery_x2_0x31[15] __PRGMTAG_  = {
    0x3e, 0x11, 0x3f, 0xf0, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x7f, 0xff, 0xff, 0xf8
};////character: '1'

static const tImage battery_x2_0x31 __PRGMTAG_ = { image_data_battery_x2_0x31,
    9, 15};//character: '1' , height: 13, (charW,total bytes)

static const uint8_t image_data_battery_x2_0x32[15] __PRGMTAG_  = {
    0x3e, 0x11, 0x3f, 0xf0, 0x18, 0x0c, 0x06, 0x03, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8
};////character: '2'

static const tImage battery_x2_0x32 __PRGMTAG_ = { image_data_battery_x2_0x32,
    9, 15};//character: '2' , height: 13, (charW,total bytes)

static const uint8_t image_data_battery_x2_0x33[15] __PRGMTAG_  = {
    0x3e, 0x11, 0x3f, 0xf0, 0x18, 0x0c, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8
};////character: '3'

static const tImage battery_x2_0x33 __PRGMTAG_ = { image_data_battery_x2_0x33,
    9, 15};//character: '3' , height: 13, (charW,total bytes)

static const uint8_t image_data_battery_x2_0x34[15] __PRGMTAG_  = {
    0x3e, 0x11, 0x3f, 0xf0, 0x18, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8
};////character: '4'

static const tImage battery_x2_0x34 __PRGMTAG_ = { image_data_battery_x2_0x34,
    9, 15};//character: '4' , height: 13, (charW,total bytes)

static const uint8_t image_data_battery_x2_0x35[15] __PRGMTAG_  = {
    0x3e, 0x11, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8
};////character: '5'

static const tImage battery_x2_0x35 __PRGMTAG_ = { image_data_battery_x2_0x35,
    9, 15};//character: '5' , height: 13, (charW,total bytes)


static const tChar battery_x2_array[] = {

  // character: ' '
  {0x20, &battery_x2_0x20},

  // character: '0'
  {0x30, &battery_x2_0x30},

  // character: '1'
  {0x31, &battery_x2_0x31},

  // character: '2'
  {0x32, &battery_x2_0x32},

  // character: '3'
  {0x33, &battery_x2_0x33},

  // character: '4'
  {0x34, &battery_x2_0x34},

  // character: '5'
  {0x35, &battery_x2_0x35}

};

//num chars, array, width, height, compression

const tFont battery_x2 = { 7, battery_x2_array,0,13,0 };

