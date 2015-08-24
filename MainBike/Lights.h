#ifndef Lights_h
#define Lights_h

#include "Arduino.h";
#include "Events.h";

#define LIGHT_MODE_BLINK 0
#define LIGHT_MODE_CONSTANT 1

class Lights: public EventListener{
  public:
    Lights(int toggle_pin);

    virtual String Process(int eventId, String& arguments);
    virtual void Update();

  private:
    int pin;
    byte mode = LIGHT_MODE_CONSTANT;
    bool lightsOn = false;
    bool enabled = true;
};

#endif Lights_h
