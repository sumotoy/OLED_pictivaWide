
/*******************************************************************************

* name: battery_x1
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



static const uint8_t image_data_battery_x1_0x20[2] __PRGMTAG_  = {
    0x00
};////character: ' '

static const tImage battery_x1_0x20 __PRGMTAG_ = { image_data_battery_x1_0x20,
    3, 1};//character: ' ' , height: 10, (charW,total bytes)

static const uint8_t image_data_battery_x1_0x30[8] __PRGMTAG_  = {
    0x33, 0xf8, 0x61, 0x86, 0x18, 0x61, 0x87, 0xf0
};////character: '0'

static const tImage battery_x1_0x30 __PRGMTAG_ = { image_data_battery_x1_0x30,
    6, 8};//character: '0' , height: 10, (charW,total bytes)

static const uint8_t image_data_battery_x1_0x31[8] __PRGMTAG_  = {
    0x33, 0xf8, 0x61, 0x86, 0x18, 0x7f, 0xff, 0xf0
};////character: '1'

static const tImage battery_x1_0x31 __PRGMTAG_ = { image_data_battery_x1_0x31,
    6, 8};//character: '1' , height: 10, (charW,total bytes)

static const uint8_t image_data_battery_x1_0x32[8] __PRGMTAG_  = {
    0x33, 0xf8, 0x61, 0x87, 0xff, 0xff, 0xff, 0xf0
};////character: '2'

static const tImage battery_x1_0x32 __PRGMTAG_ = { image_data_battery_x1_0x32,
    6, 8};//character: '2' , height: 10, (charW,total bytes)

static const uint8_t image_data_battery_x1_0x33[8] __PRGMTAG_  = {
    0x33, 0xf8, 0x61, 0xff, 0xff, 0xff, 0xff, 0xf0
};////character: '3'

static const tImage battery_x1_0x33 __PRGMTAG_ = { image_data_battery_x1_0x33,
    6, 8};//character: '3' , height: 10, (charW,total bytes)

static const uint8_t image_data_battery_x1_0x34[8] __PRGMTAG_  = {
    0x33, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf0
};////character: '4'

static const tImage battery_x1_0x34 __PRGMTAG_ = { image_data_battery_x1_0x34,
    6, 8};//character: '4' , height: 10, (charW,total bytes)

static const uint8_t image_data_battery_x1_0x35[8] __PRGMTAG_  = {
    0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};////character: '5'

static const tImage battery_x1_0x35 __PRGMTAG_ = { image_data_battery_x1_0x35,
    6, 8};//character: '5' , height: 10, (charW,total bytes)


static const tChar battery_x1_array[] = {

  // character: ' '
  {0x20, &battery_x1_0x20},

  // character: '0'
  {0x30, &battery_x1_0x30},

  // character: '1'
  {0x31, &battery_x1_0x31},

  // character: '2'
  {0x32, &battery_x1_0x32},

  // character: '3'
  {0x33, &battery_x1_0x33},

  // character: '4'
  {0x34, &battery_x1_0x34},

  // character: '5'
  {0x35, &battery_x1_0x35}

};

//num chars, array, width, height, compression

const tFont battery_x1 = { 7, battery_x1_array,0,10,0 };

