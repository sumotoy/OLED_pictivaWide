# OLED pictiva 288x48
A real and fully working library for the <b>Osram Pictiva OLED 288x48</b>, made in Germany, great quality but design Wolkswagen-like Fail!<br>
Osram choosed an obscure SSD0332, a parent of SSD1331, a capable rgb OLED driver but limited to 96 pixel wide. Instead choose something better, Osram cheat by using each r,g,b of the 96 pixels as addressing so they get 288 pixel but at the cost of limited features and performances and complicated coding, this caused premature dead of the product and now this display can be found only as ex-stock. I've seen this display many times in ebay and price always dropped a lot because the design limitations and the lack of documentation blocked most people to create an functional code for use it!<br> This until I got a decent stock of this display for cheap price, the seller confirmed that there's almost no documentation and cose examples so they decided to get rid of the entire stock.<br>
I like the quality of this display, another world if you compare to the last chinese shitty stuff I got in ebay, so I decided to give it another chance<br>
This is actually the only library that really works with this display.<br>

- OS288048PQ33MY0C11
- OS288048PQ33MG1C11
- OS288048PQ33MO2C11

<b>Current version:</b><br>
<b>1.1b1</b>: This is the first public beta, I have used it a bit in some project and works really well, I have enabled almost all features in goals, play nice with other SPI devices and it's fast, however there's some work to do, for example I have not clear how to deal with X values since internally are limited by 96 but actually display it's 288! (it uses the r,g,b values as pixels)<br>
Since the x axis it's color-drived I personally prefere the 96 pixel approach (draw between r,g,b pixel require a large amount of code) so take a look to the examples and pay attention to code comments.<br>

<b>Font and Icon conversion:</b><br>
It's virtually possible convert any font but it's absolutely necessary to choose fonts with wide of 3 or multiple of 3! I mean, the font can contain any glyph between 3 to 6,9,12,etc but NEVER numbert outside this range! This caused by design choosed by OSRAM for this display, in theory it's possible avoid this but require a large amount of code. The font can be any high since on Y axis there's only the limitation of 47.<br>
For Icons there's the same limitation, only numbers multiple of 3 in wide.<br>
It looks complicated but in reality it's much better this approach than add tons of code!<br>
For conversion I use https://github.com/riuson/lcd-image-converter, I provide 2 different templates for FONT and ICON named <b>sumotoy_font.tmpl</b> (the same used in RA8875) and <b>sumotoy_image.tmpl</b> follow wiki https://github.com/sumotoy/OLED_pictivaWide/wiki/Font-Conversion (please note that it's a preliminary early wiki copied from my RA8875 one but for this library there's limitations above mentioned)<br>
The RA8875 and this library can sharing the same fonts, however only this library fonts can be used in both libraries! The RA8875 fonts are not compatible due the hardware limitation of this one that needs only multiple of 3 pixel wide fonts (included space), very rare to find as is...<br>

<b>Background</b><br>
I got this nice display on ebay, really cheap and I was really surprised, it come with an arduino library and some kind of documentation (very poor indeed), it was looking a real affair!<br>
The display it's superbly made, german quality, chip on glass, really nice Yellow, it's an OLED of course and contain 13824 LED's so reading it's crisp and visible at any angle, simply superb!<br>
Once arrived, I discovered that needs a 12->15V voltage and a 3V3, easy to solve with a simple step-up circuit. The library was working and does exact as described, but only as text display, fixed font size, so I take a look inside code and decided immediately to trash it, ridicolous coded with massive errors, for example it initialize the display, then apply an hardware reset (!), it also use the most weird row addressing I ever see, where 1=1,2=47,3=2,4=48... As result write a char is something that need a alien to understand, even worst, write a new font file with this method it's just INSANE,  a lot of commands are simply wrong, some missed and...amazing slow. The only good thing? It's so badly coded that works, slow, using resources but works.<br>
Armed of the best purposes I take a look at the Osram datasheet (just one page, only description), really useless but reference to an obscure Solomon SSD0323 as driver (also NOT documented). I had an hard time to get a really preliminary datasheet of the SSD0323 and with the tiny informations of Osram I discovered that it has colums mapped in sequence with r,g,b pixels, this because Solomon chip can handle only 96 pixels (r,g,b) but this pictiva is 288, 96x3 = 288! Genius? no, FAIL!<br>
With this design limitation it's impossible to use the hardware accellerated functions of the SSD chip and the pixel addressing is actually very complicated, you cannot draw a inclined line without create crazy complicated (and slow) algorithm or a simply vertical line or just a serie of pixels! It recalls me the Wolkswagen fail...<br><br>

<b>Design a new library</b><br>
Time to start from scratch, I literaly trashed the old library and studied what I can get out from this display since online I cannot find any help and my informations are really limited. I have contacted Osram and they refused any support or documents because it's a retired products and the only doc it's just for reference. Thanks a lot, Fritz, so let's decide the goals and code myself:<br><br>

<b>Goals..</b>. Of course saving this design failure from the trash!<br>
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

<b>Proof of working (on Teensy 3.1, fonts and demo distributed with library)</b><br>

![starWars](https://github.com/sumotoy/OLED_pictivaWide/blob/gh-pages/images/CIMG5416.png)
![bars](https://github.com/sumotoy/OLED_pictivaWide/blob/gh-pages/images/CIMG5418.png)
![font1](https://github.com/sumotoy/OLED_pictivaWide/blob/gh-pages/images/CIMG5425.png)
![font2](https://github.com/sumotoy/OLED_pictivaWide/blob/gh-pages/images/CIMG5427.png)
![oledFun](https://github.com/sumotoy/OLED_pictivaWide/blob/gh-pages/images/CIMG5423.png)
