#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>

#include "Events.h";
#include "Lights.h";
#include "Bluetooth.h";
#include "Timer.h"
#include "LCD.h"
#include "Adafruit_BLE_UART.h";
#include "SeeedOLED.h"


class Events: public EventDelegator {
  public:
    void Init() {
      lights.Init();
      bluetooth.Init();
      lcd.Init();
    }

    String Execute(int eventId, String arguments) {
      switch(eventId) {
        case EVENT_LIGHT_TURN_ON: return lights.Process(eventId, arguments);
        case EVENT_LIGHT_TURN_OFF: return lights.Process(eventId, arguments);
        case EVENT_LIGHT_TURN_MODE: return lights.Process(eventId, arguments);
        
        case EVENT_PRINT_NUMBER: return lcd.Process(eventId, arguments);
      }
      return "";      
    }

    void Update() {
      lights.Update(); 
      // bluetooth.Update();      
    }

    void Loop() {
      // lights.Loop(); 
      bluetooth.Loop();      
    }

  private:
    Lights lights = Lights(6);
    Bluetooth bluetooth = Bluetooth();
    LCD lcd = LCD();
};

Events events;
Timer timer;

String SendEvent(int eventId, String argument) {
  return events.Execute(eventId, argument);
}

void update() {
  events.Update();  
}

void setup() {
  Serial.begin(9600);

  events.Init();
  timer.every(100, update);
  SendEvent(EVENT_PRINT_NUMBER, "27");
}

void loop() {
  timer.update();
  events.Loop();
}
