# FeatherOLED SSD1351

A library to control a SSD1351 OLED using a Feather Huzzah or other ESP8266

This library was originally written in order to get the 1.5" OLED breakout from Adafruit to interface with the ESP8266 powered Adafruit Feather Huzzah. It is a very simple UI framework to support basic text, pagination and shapes. VERY BASIC.

A lot of this code was taken from https://www.mgo-tec.com/blog-entry-adafruit-oled-ssd1351-esp-wroom-nonlib.html


-----------

### How to setup

1. Add the library to your Arduino libraries folder.

2. Include the library in your project:

```
#include <FeatherOLED.h>
```

3. Define your SPI pins for communication with the OLED breakout:

```
#define sclk 14
#define mosi 13
#define cs 15
const int DCpin =  4;
const int RSTpin =  5;
```

4. In your setup loop, define your pin modes for each of the SPI pins:

```
pinMode(DCpin, OUTPUT);
pinMode(sclk, OUTPUT);
pinMode(mosi, OUTPUT);
pinMode(RSTpin, OUTPUT);
pinMode(cs, OUTPUT);
digitalWrite(cs, LOW);   
digitalWrite(RSTpin, HIGH);
delay(500);
digitalWrite(RSTpin, LOW);
delay(500);
digitalWrite(RSTpin, HIGH);
delay(500);

```

5. Implement an instance of the FeatherOLED object for use in your program. The instance requires your pin definitions as well as the x and y dimensions of the screen (128 x 128 for the 1.5" OLED breakout):

```
featherOLED oled = featherOLED(sclk, mosi, cs, DCpin, 128, 128); //sclk, mosi, cs, DCpin, max x, max y
```

6. Initialize and blackout the screen:

```
oled.init();
oled.blank();
```


### Function reference

**print(X, Y, Red, Green, Blue, "String")**
Send font characters to the screen. Each character is fixed width at 8x16px and the text will cut off rather than line wrap in this version. The Red Green Blue parameters should be supplied as uint8_t values that correspond to the maximum colors avaiulable on your screen (i.e. 16-bit resolution = 31, 63, 31 maximum values respectively).


**paginate(Y, Total, Selected)**
Write a pagination UI to the screen cenetered at the selected Y start value. Total = the total number of pages (max is screen width / 8 or 16 on a 128px screen). The selected parameter refers to the currently selected page to generate the appropriate "filled in dot" on the display.


**blank()**
Clears the screen (sets all pixels to black).


**init()**
Initializes the screen and prepares the device for writing.