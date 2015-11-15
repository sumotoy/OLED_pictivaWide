# OLED pictiva 288x48
A REAL and fully working library for the Osram Pictiva OLED 288x48, made in Germany and Failed like Wolkswagen!<br>

- OS288048PQ33MY0C11
- OS288048PQ33MG1C11
- OS288048PQ33MO2C11

<b>Current version:</b><br>
<b>1.1b1</b>: This is the first public beta, I have used it a bit in some project and works really well, I have enabled almost all features in goals, play nice with other SPI devices and it's fast, however there's some work to do, for example I have not clear how to deal with X values soince internally are limited by 96 but actually display it's 288!<br>
Since the x axis it's color-drived I personally prefere the 96 pixel approach since draw between r,g,b pixel require a large amount of code so take a look to the examples and pay attention to code comments.<br>

<b>Background</b><br>
I got this nice display on ebay, really cheap and I was really surprised, it come with an arduino library and some king of documentation (very poor indeed), it was looking a real affair!<br>
The display it's superbly made, german quality, chip on glass, really nice Yellow, it's an OLED of course and contain 13824 LED's so reading it's crisp and visible at any angle, simply superb!<br>
Once arrived, I discovered that needs a 12->15V voltage and a 3V3, easy to solve with a simple step-up circuit. The library was working and does exact as described, but only as text display, fixed font size, so I take a look inside code and decided immediately to trash it, ridicolous coded with massive errors, for example it initialize the display, then apply an hardware reset (!), it also use the most weird row addressing I ever see, where 1=1,2=47,3=2,4=48... As result write a char is something that need a alien to understand, even worst, write a new font file with this method it's just INSANE,  a lot of commands are simply wrong, some missed and...amazing slow. The only good thing? It's so badly coded that works, slow, using resources but works.<br>
Armed of the best purposes I take a look at the Osram datasheet (just one page, only description), really useless but reference to an obscure Solomon SSD0323 as driver (also NOT documented). I had an hard time to get a really preliminary datasheet of the SSD0323 and with the tiny informations of Osram I discovered that it has colums mapped in sequence with r,g,b pixels, this because Solomon chip can handle only 96 pixels (r,g,b) but this pictiva is 288, 96x3 = 288! Genius? no, FAIL!<br>
With this design limitation it's impossible to use the hardware accellerated functions of the SSD chip and the pixel addressing is actually very complicated, you cannot draw a inclined line without create crazy complicated (and slow) algorithm or a simply vertical line or just a serie of pixels! It recalls me the Wolkswagen fail...<br><br>

<b>Design a new library</b><br>
Time to start from scratch? Yes, I literaly trashed the old library and studied what I can get out from this display since online I cannot find any help and my informations are really limited. I have contacted Osram and they refused any support or documents because it's a retired products and the only doc it's just for reference. Thanks a lot, Fritz, so let's decide the goals and code myself:<br><br>

<b>Goals..</b><br>
 - Easy to use, only 4 Wires.
 - Enable 5 bit of greyscale.
 - Custom fonts, I mean NORMAL and EASY converted fonts (not like the twisted one included in demo library).
 - Use SSD Hardware accellerated functions where it's possible.
 - Use most SSD functions where possible.
 - Enable global Brightness (for longer OLED life).
 - Enable change Contrast.
 - Ability to send 24Bit image and convert on the fly to 5 bit grayscale, full screen!
 - Since OLEDs consume very low, ability to use Sleep.
 - Uses standard SPI, full SPI transaction compatible and play nice with other SPI devices.

In theory everithing it's possible, but studing how Osram designed this display I come across big ostacles, the major is the mapping of each colums by using r,g,b lines of a single pixel (the SSD it's color but display not), this give for each pixel a line of 3 pixel! Even write an oblique line it's a challenge but also a single pixel, I need to write always 3 pixels! The only pro is that I can use 5 bit for change the greyscale of each pixel but addressing it's a mess, with a fast processor you can (in theory) use it as frame buffer but it waste resources, grr... I hope at Osram kick the ass to the guy under this twisted idea!<br>
I like almost impossible challenge and now finally I got all my design point reached! It cost me a lot of time because the lack of informations and have to rewrite several time a lot of code to simplify the weird addressing of this chip, but it's over now and I'm actually using in some of my projects, looks beautiful, I love OLED, and this one it's really far from the crappy chinese stuff (stamp size) I've used in the past, consider that this one cost at list half price!<br><br>

<b>Connections</b><br>
Actually I've tested only with Teensy 3.1, Here's connections:<br>
![Teensy](https://github.com/sumotoy/OLED_pictivaWide/blob/master/docs/pictivaTeensy.png)
<br>
As you notice this display needs an extra voltage of 12-15V! Only few milliamps needed so you can use literally anything to provide this voltage but if you are plan to use this display in Audio or measurement be careful to filter enough the voltage or you can get a lot of EMI emissions!<br>
The logic works only at 3V3 and logic level are only 3V3! Do not connect directly to an Arduino UNO or any processors at 5V or you will destroy it!<br>


<b>Why it's so cheap?</b><br>
Probably Osram realized that their design it's a massive fail and they are selling/selled quickly all factory stocks strongly undercost. The display it's available on ebay for a price that it's probably lower that the production costs, I've seen listed everywhere, even in Farnell and RS (discontinued of course), lower price it's around 4US but I'm sure it will drop<br>
