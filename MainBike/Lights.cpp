#include "Lights.h"

Lights::Lights(int toggle_pin) : pin(toggle_pin) {
  pinMode(toggle_pin, OUTPUT);  
}

String Lights::Process(int eventId, String& arguments) {
  switch(eventId) {
    case EVENT_LIGHT_TURN_ON:
      enabled = true;
      break;
    case EVENT_LIGHT_TURN_OFF:
      enabled = false;
      break;
    case EVENT_LIGHT_TURN_MODE:
      mode = arguments == "blink" ? LIGHT_MODE_BLINK : LIGHT_MODE_CONSTANT;
      break;
  }
  return "";
}

void Lights::Update() {
  if (mode == LIGHT_MODE_CONSTANT) {
    if (enabled) {
      digitalWrite(pin, HIGH);
    } else {
      digitalWrite(pin, LOW);            
    }    
  } else {
    if (lightsOn) {
      digitalWrite(pin, LOW);      
    } else {
      digitalWrite(pin, HIGH);
    }
    lightsOn = !lightsOn;
  }    
}

