#include "Arduino.h";

#define EVENT_LIGHT_TURN_ON 0
#define EVENT_LIGHT_TURN_OFF 1
#define EVENT_LIGHT_TURN_MODE 2

#ifndef EventDelegator_h
#define EventDelegator_h

class EventDelegator {
  public:
    String Execute(int eventId, String& arguments);
};

#endif

#ifndef EventListener_h
#define EventListener_h

class EventListener {
    public:

      virtual ~EventListener() {};

      void Init(EventDelegator* delegator) {
        this->delegator = delegator;
      }

      /* Called on an external trigger */
      virtual String Process(int eventId, String& arguments) = 0;
      /* Called every 100ms, to update the state of the listener*/
      virtual void Update() = 0;

    private:
      EventDelegator* delegator;
};

#endif
