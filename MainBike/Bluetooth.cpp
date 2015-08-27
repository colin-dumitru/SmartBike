#include "Bluetooth.h"

Bluetooth::Bluetooth(){ }

void Bluetooth::Init() {
  BTLEserial.begin();
}

void Bluetooth::Loop() {
  BTLEserial.pollACI();
  
  aci_evt_opcode_t status = BTLEserial.getState();

  if (status != laststatus) {
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("[Bluetooth] Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("[Bluetooth] Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("[Bluetooth] Disconnected or advertising timed out"));
    }
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED && BTLEserial.available()) {
    String message = ReadAvailable(); 
    Serial.println("[Bluetooth] " + message);
    ProcessMessage(message);
  }
}

String Bluetooth::ReadAvailable() {
  return BTLEserial.readString(); 
}

void Bluetooth::ProcessMessage(String message) {
  short separatorIndex = message.indexOf(':');

  if (separatorIndex != -1) {
    int eventId = message.substring(0, separatorIndex).toInt();
    String arguments = (separatorIndex == message.length()) ? "" : message.substring(separatorIndex+1);
    
    SendEvent(eventId,arguments);
  }
}

