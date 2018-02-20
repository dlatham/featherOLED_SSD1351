#include "featherOLED.h"

featherOLED::featherOLED(uint8_t sclk_in, uint8_t mosi_in, uint8_t cs_in, uint8_t DCpin_in, uint8_t x, uint8_t y){
	sclk = sclk_in;
	mosi = mosi_in;
	cs = cs_in;
	DCpin = DCpin_in;
	//x and y set the maximum dimensions of the screem
	max_x = x;
	max_y = y;
}

void featherOLED::print(uint8_t StartX, uint8_t StartY, uint8_t Red, uint8_t Green, uint8_t Blue, char* text){
	Serial.print("OLED: Print requested for ");
	Serial.print(text);
	Serial.print(" with a character count of ");
	Serial.println(sizeof(text));
	for(int i = 0; i <= sizeof(text); i++){
		if((StartX + (8 * i))>(max_x - 8)){
			Serial.println("OLED: End of line");
			break;
		} else {
			Serial.print("OLED: Requesting Font1x1(");
			Serial.print(StartX + (8 * i));
			Serial.print(", ");
			Serial.print(StartY);
			Serial.print(", ");
			Serial.print(Red);
			Serial.print(", ");
			Serial.print(Green);
			Serial.print(", ");
			Serial.print(Blue);
			Serial.print(", ");
			Serial.print(letter[int(text[i])-64][4]);
			Serial.println(")");
			Font1x1(StartX + (8 * i), StartY, Red, Green, Blue, letter[int(text[i])-64]);
		}
		
	}
}

void featherOLED::init(){
  writeCommand(0xFD); //Set Command Lock
    writeData(0x12); //Unlock OLED driver IC MCU interface from entering command
  writeCommand(0xFD); //Set Command Lock
    writeData(0xB1); //Command A2,B1,B3,BB,BE,C1 accessible if in unlock state
  writeCommand(0xAE); //Sleep mode On (Display OFF)
  writeCommand(0xB3); //Front Clock Divider
    writeCommand(0xF1); // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
  writeCommand(0xCA); //Set MUX Ratio
    writeData(127);
  writeCommand(0xA0); //Set Re-map
    writeData(B01110100); //65k color
    //writeData(B10110100); //262k color
    //writeData(B11110100); //262k color, 16-bit format 2
  writeCommand(0x15); //Set Column
    writeData(0); //start
    writeData(127); //end
  writeCommand(0x75); //Set Row
    writeData(0); //start
    writeData(127); //end
  writeCommand(0xA1); //Set Display Start Line
    writeData(0);
  writeCommand(0xA2); //Set Display Offset
    writeData(0);
  writeCommand(0xB5); //Set GPIO
    writeData(0);
  writeCommand(0xAB); //Function Selection
    writeData(0x01); //Enable internal Vdd /8-bit parallel
    //writeData(B01000001); //Enable internal Vdd /Select 16-bit parallel interface
  writeCommand(0xB1); //Set Reset(Phase 1) /Pre-charge(Phase 2)
    //writeCommand(B00110010); //5 DCLKs / 3 DCLKs
    writeCommand(0x74);
  writeCommand(0xBE); //Set VCOMH Voltage
    writeCommand(0x05); //0.82 x VCC [reset]
  writeCommand(0xA6); //Reset to normal display
  writeCommand(0xC1); //Set Contrast
    writeData(0xC8); //Red contrast (reset=0x8A)
    writeData(0x80); //Green contrast (reset=0x51)
    writeData(0xC8); //Blue contrast (reset=0x8A)
  writeCommand(0xC7); //Master Contrast Current Control
    writeData(0x0F); //0-15
  writeCommand(0xB4); //Set Segment Low Voltage(VSL)
    writeData(0xA0);
    writeData(0xB5);
    writeData(0x55);
  writeCommand(0xB6); //Set Second Precharge Period
    writeData(0x01); //1 DCLKS
  writeCommand(0x9E); //Scroll Stop Moving
  writeCommand(0xAF); //Sleep mode On (Display ON)

  delay(100);
}

void featherOLED::blank(){
  writeCommand(0x15); //Set Column
    writeData(0x00);
    writeData(127);
  writeCommand(0x75); //Set Row
    writeData(0x00);
    writeData(127);
  writeCommand(0x5C); //Write RAM
  for(int i=0; i<max_x*max_y; i++){
    writeData(0x00);
    writeData(0x00);
    //writeData(0x00); //262k colorの場合３バイト分送信
  }
}

void featherOLED::Font1x1(uint8_t StartX, uint8_t StartY, uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t* buf){
  int16_t i,j;
  uint8_t RGBbit1, RGBbit2;
  RGBbit1 = (Red<<3) | (Green>>3);
  RGBbit2 = (Green<<5) | Blue;
   
  writeCommand(0x15); //Set Column
    writeData(StartX);
    writeData(StartX+7);
  writeCommand(0x75); //Set Row
    writeData(StartY);
    writeData(StartY+15);
  writeCommand(0x5C); //Write RAM
   
  for(i=0; i<16; i++){
    for(j=7; j>=0; j--){
      if(buf[i] & (1<<(j))){
        writeData(RGBbit1);
        writeData(RGBbit2);
      }else{
        writeData(0);
        writeData(0);
      }
    }
  }
}

void featherOLED::Font2x2(uint8_t StartX, uint8_t StartY, uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t* buf){
  int16_t i,j,ii;
  uint8_t RGBbit1, RGBbit2;
  RGBbit1 = (Red<<3) | (Green>>3);
  RGBbit2 = (Green<<5) | Blue;
   
  writeCommand(0x15); //Set Column
    writeData(StartX);
    writeData(StartX+15);
  writeCommand(0x75); //Set Row
    writeData(StartY);
    writeData(StartY+31);
  writeCommand(0x5C); //Write RAM
   
  for(i=0; i<16; i++){
    for(ii=0; ii<2; ii++){//倍角の場合２行同じものを描く
      for(j=7; j>=0; j--){
        if(buf[i] & (1<<(j))){
          writeData(RGBbit1);
          writeData(RGBbit2);
          writeData(RGBbit1);
          writeData(RGBbit2);
        }else{
          writeData(0);
          writeData(0);
          writeData(0);
          writeData(0);
        }
      }
    }
  }
}

void featherOLED::SPIwrite(uint8_t c){
  digitalWrite(sclk, HIGH);
  int8_t i; //signed int
  for (i=7; i>=0; i--) {
      digitalWrite(sclk, LOW);    
      if (c & (1<<(i))) {
          digitalWrite(mosi, HIGH);
      } else {
          digitalWrite(mosi, LOW);
      }
      digitalWrite(sclk, HIGH);
  }
}
 
void featherOLED::writeCommand(uint8_t c) {
    digitalWrite(DCpin, LOW);
    digitalWrite(cs, LOW);
    SPIwrite(c);
    digitalWrite(cs, HIGH);
}
 
void featherOLED::writeData(uint8_t c) {
    digitalWrite(DCpin, HIGH);
    digitalWrite(cs, LOW);
    SPIwrite(c);
    digitalWrite(cs, HIGH);
}