# OLED_pictivaWide
A real working library for the Osram Pictiva OLED 288x48 that works fast<br>

<b>Background</b><br>
I got this display from ebay, loved the quality (german, not shitty-chippy-chinese) but I immediately realized a big fail in the design, Osram cannot find a controller for the 288 columns so they choosed an obscure SSD0323 from Solomon that is 48x96 rgb and connect the single r,g,b as:<br>
 - column 0: r (pixel 1)
 - column 1: g (pixel 1)
 - column 2: b (pixel 1)
 - ...
 - column 287: b (pixel 96)
 
As result 96x3 = 288, ok, but this has literally broken every accellerated macro of the SSD chip and have a reliable access to the cgram of the display.<br> I got a library with the display, it's just avr and can only print text, the vendor was very nice to provide but unfortunatly it's terrible coded and the font uses a even nasty even/odd mapping for the row addressing that it's not acceptable.<br>
So I decided to start from scratch from the Datasheet and see if I can do better<br>
First of all, the Osram decision was very wrong sign that even Germans can fail as everyone else (can't resist) and there's no way to use basic things like draw a single pixel or better... it's possible but the more pixels you write will cover the old pixels, for example, draw pixel 0, now you decide to draw pixel 1 and you realize that this pixels (0,1,2) are part of the same pixel (remember the 96 pixel addressed as r,g,b?) so to frite pixel 1 you will need to black the r,b side of the pixel that will turn off pixel 0, I hope you get the picture!<br>
Hardware Accellerated DrawRect? Forget it! You can only have a chance to use Accellerated Draw Line for vertical and horizontal lines but NEVER for oblique one and only by using some un-usual code.<br>
Going back to library I finally managed to render font in a decent way and modified a DotFactoryProgram to convert fonts in a Pictiva 3bit assimilable form, fixed the SPI access and touched 14Mhz and get a vertical and horizontal line accellerated drawing, all this at 4bit grayscale (a secondary effect of using the r,g,b pin as addressing) and with vertical scroll, idle mode and brightness.<br>
I was really surprise that it's extremely difficult find the SSD0323 datasheet and no library exist for this display (apart the one provided by ebay vendor and another driver as linux framebuffer but really basic or not working).
