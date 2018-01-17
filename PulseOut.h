/**********************************************************************************
  PulseOut.  Pulse Generator class.
  Header file.
  Franck Touanen - Dec 2017.
************************************************************************************/
#ifndef PulseOut_h
#define PulseOut_h

#include <Arduino.h>

class PulseOut
  {
    public:
      PulseOut(uint8_t pin, long duration, uint8_t pulse=NULL, bool square=NULL );
      void begin();
      bool start();
      void update(unsigned long currentMillis);
      void update(unsigned long* pcurrentMillis); // Faster when called by a manager
      uint8_t getPin();

    private:
      // Class Member Variables
      uint8_t       _pin;                  // the # of the pulse Arduino digital pin
      long          _duration;             // total milliseconds for the pulse
      uint8_t       _pulse     = HIGH;     // HIGH or LOW pulse
      bool          _square    = false;    // generate a square HIGH LOW (duration * 2)

      bool          _isActive;            // True if the pulse is on going
      bool          _mustStart;           // True if the pulse must be started
      unsigned long _previousMillis;      // will store last time pulse was updated
      uint8_t       _pinState;            // Hold the current pin state HIGH or LOW
  };

#endif
