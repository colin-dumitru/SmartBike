#include "LCD.h"

LCD::LCD(){}

String LCD::Process(int eventId, String& arguments) {
  switch(eventId) {
    case EVENT_PRINT_NUMBER:
      PrintLargeNumber(arguments.toInt());
      break;
  }
  return "";
}

void LCD::Init() {
  Wire.begin();
  SeeedOled.init();            
  SeeedOled.clearDisplay();    
  SeeedOled.setNormalDisplay();
}

void LCD::PrintLargeDigit(unsigned char num, unsigned char xOffset) {
  if (num < 0 || num > 9) {
    return;
  }
  
  for (unsigned char i=0; i<8; i++) {
    SeeedOled.setTextXY(i, xOffset);
    
    for (unsigned char j=0; j<64; j++) {   
      SeeedOled.sendData(pgm_read_byte(&LargeNumberFont[8*num + i][j]));
    }    
  }  
}

void LCD::PrintLargeNumber(byte num) {
  if (num < 0) {
    num = 0;
  }
  if (num > 99) {
    num = 99;
  }
  if (num < 10) {
    PrintLargeDigit(num, 4);
  } else {
    PrintLargeDigit(num / 10, 0);    
    PrintLargeDigit(num % 10, 8);    
  }
}

