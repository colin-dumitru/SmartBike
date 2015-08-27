#ifndef Bluetooth_h
#define Bluetoothr_h

#include "Events.h";
#include "Adafruit_BLE_UART.h";

#define BLE_REQ 10
#define BLE_RDY 7     // This should be an interrupt pin, on Uno thats #2 or #3
#define BLE_RST 18

extern String SendEvent(int,String);

class Bluetooth: public EventListener{
  public:
    Bluetooth();

    virtual void Init();
    virtual void Loop();

  private:
    Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(BLE_REQ, BLE_RDY, BLE_RST);
    aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

    String ReadAvailable();
    void ProcessMessage(String message);
};

#endif
