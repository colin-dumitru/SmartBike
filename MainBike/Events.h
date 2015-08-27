#include "Arduino.h";

#define EVENT_LIGHT_TURN_ON 0
#define EVENT_LIGHT_TURN_OFF 1
#define EVENT_LIGHT_TURN_MODE 2

#define EVENT_PRINT_NUMBER 10

#ifndef EventDelegator_h
#define EventDelegator_h

class EventDelegator {
  public:
    virtual String Execute(int eventId, String arguments) {};
    
    virtual void Update() {};
    virtual void Init() {};
    virtual void Loop() {};
};

#endif

#ifndef EventListener_h
#define EventListener_h

class EventListener {
    public:

      virtual ~EventListener() {};

      virtual void Init() {
      }

      /* Called on an external trigger */
      virtual String Process(int eventId, String& arguments) {};
      /* Called every 100ms, to update the state of the listener*/
      virtual void Update() {};
      /* Called on each update cycle*/
      virtual void Loop() {};
};

#endif
