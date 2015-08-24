#include "Events.h";
#include "Lights.h";
#include "Timer.h"

class Events: public EventDelegator {
  public:
    Events() {}

    String Execute(int eventId, String& arguments) {
      switch(eventId) {
        case EVENT_LIGHT_TURN_ON: lights.Process(EVENT_LIGHT_TURN_ON, arguments); break;
        case EVENT_LIGHT_TURN_OFF: lights.Process(EVENT_LIGHT_TURN_OFF, arguments); break;
        case EVENT_LIGHT_TURN_MODE: lights.Process(EVENT_LIGHT_TURN_MODE, arguments); break;
      }
    }

    void Update() {
      lights.Update();      
    }

  private:
    Lights lights = Lights(6);
};

Events events;
Timer timer;

void update() {
  Serial.println("Update");
  events.Update();  
}

void setup() {
  Serial.begin(9600);

  timer.every(100, update);
  
  // initialize digital pin 13 as an output.
  
  // pinMode(5, INPUT_PULLUP);

  String argument = "blink";

  events.Execute(EVENT_LIGHT_TURN_ON, argument);
  events.Execute(EVENT_LIGHT_TURN_MODE, argument);
}

void loop() {
  // int sensorVal = digitalRead(5);
  timer.update();
}
