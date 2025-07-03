# 250702-attiny85-ps2-reset-perixx-kbd-mod-zeal8bit
journey to fix missing init+config of ps2(usb?) keyboard based on holtek mcu by using digispark attiny85

it started yesterday on zeal8bit discord, then one guy posted this link and I started to think about raw attiny1624 soic14 I have here, but then cosidered arduino nano every with exposed microusb and ended up with even simpler digispark attiny85 I have here also in larger batch for some "surprise cases..." ))

https://www.reddit.com/r/beneater/s/S0dAbJ44VG

entire "consulting" session with "Lyra" here - so far, 2days and result okay :-)

https://chatgpt.com/share/686462ef-ed2c-8000-835e-2aa5e0a3de2f

btw, zeal8bit is thing which started primarily because of FPGA based video and I wanted to touch this hardware, despite I have ordered also pico9918/f18a which will be probably the main vmex/aslix video for now, not decided yet fully, but probably yes; its 9918 compatible thing, so will see ... any my specifications proposal for 7xtgv with saa7129h are far far away, as its not that simple, obviously :-)

Omar is good guy, he did this mostly because he started with the learning FPGA for video and here in interview he mentions at 33:30 the issues with PS/2 interface

https://www.youtube.com/watch?v=b6aXM_JvKxg

(sad thing about zeal8bit is there is NO schematic published - so its closed here, this is one thing I overlooked a bit, ya)

# spencekonde attinycore for arduino
https://github.com/SpenceKonde/ATTinyCore

digispark had/has unusual flashing - this is fresh library for all AVR, lots of detailed info about raw updi degug/flash over serial port
(I finaly used readmyade older modules I had here, quickest thing, despite arduino ide is pita)

# enjoy 
hope this keyboard init can help anybody with retro system and newer ps2/usb combo keyboards which expect some kind of write/init if you have only passive reading port/bitbang etc ...


