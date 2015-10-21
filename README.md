# OLED pictiva 288x48
A REAL and fully working library for the Osram Pictiva OLED 288x48, one of the most failure designed display I come across!<br>

- OS288048PQ33MY0C11
- OS288048PQ33MG1C11
- OS288048PQ33MO2C11

<b>Background</b><br>
I got this nice display on ebay, really cheap and I was really surprised, it come with an arduino library and some king of documentation (very poor indeed), it was looking a real affair!<br>
Once arrived, I discovered that needs a 12->15V voltage and a 3V3, easy to solve with a simple step-up circuit. The library was working and does exact as described, but works only as text display, fixed font size, so I take a look inside library and decided immediately to trash it, it's horrible coded with amazing errors, for example the guy who coded initialize the display, then apply an hardware reset (in this way initialization gone), he also decided to use the most weird row addressing I ever see where 1=1,2=47,3=2,4=48... As result write a char it's something that need a psychiatric to understand, even worst, write a new font file with this method it's just INSANE, all this are just a fraction of the problems, and code it's really slow (slower is impossible).<br>
Armed of the best purposed I take a look at the Osram datasheet (just one page, only descriptions), really useless but reference to a Solomon SSD0323 as driver that is also NOT documented. I had an hard time to get a really preliminary datasheet of the SSD0323 and with the tiny informations on the Osram product informations I discovered that they mapped the colums in sequence with r,g,b pixels, this because Solomon chip can handle only 96 pixels (r,g,b) but this pictiva is 288, 96x3 = 288!<br>
Ok, it's a big fail in design, doing this it's impossible to use the hardware accellerated functions of the SSD chip and even worst this display it's graphic but it's hard to use with this design! A Wolkswagen german style fail!<br>
<b>Design a new library</b><br>
Ok, time to start from scratch! I literaly trashed the old library and start to study what I can get out from this display<br>

 - Using as Text but also Graphic display
 - Ability to use the 5 bit of grey.
 - Ability to use custom fonts, I mean NORMAL and EASY converted fonts (not the messy library one)
 - Ability to use SSD Hardware accellerated functions where it's possible

These are goals, but studing how Osram designed this display I come across really big ostacles, the major it's the columns mapped to r,g,b, this give for each pixel a line of 3 pixel! Even write an oblique line it's a challenge.<br>
I like almost impossible challenge and at the end I was able to write every type of font, use most accellerated graphic command and so on, all my design point reached!<br><br>

<b>Why still not posted?</b><br>
Doing some research on the net I come across some suspect request I find in hire engineer site where a guy is paying 50US for write a simple library for this display that act as text display, this is really similar to the library I got with the display (nothing to say to the ebay display vendor, he was nice to provide and at list it works somehow), I take time to finish and optimize it (in a couple of days I will post video of proff that shows my current development results) than if I have some request I will post it. In the meantime if you came across this display you are warned, there's nothing online that can help you and it's really a challenge to write something usable!<br>

<b>Why it's so cheap?</b><br>
Probably Osram realized that their design it's a massive fail and they are selling quickly all the stocks for nothing. The display it's available on ebay for a price that it's probably lower that the production costs, I come across stock of this display everywhere in the world, you can find for 3,4 US!<br>
