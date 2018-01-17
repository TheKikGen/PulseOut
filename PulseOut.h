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
      void Begin();
      bool Start();
      void Update(unsigned long currentMillis);
      uint8_t GetPin();

    private:
      // Class Member Variables
      uint8_t       _Pin;                  // the # of the pulse Arduino digital pin
      long          _Duration;             // total milliseconds for the pulse
      uint8_t       _Pulse     = HIGH;     // HIGH or LOW pulse
      bool          _Square    = false;    // generate a square HIGH LOW (duration * 2)

      bool          _IsActive;            // True if the pulse is on going
      bool          _MustStart;           // True if the pulse must be started
      unsigned long _PreviousMillis;      // will store last time pulse was updated
      uint8_t       _PinState;            // Hold the current pin state HIGH or LOW
  };

#endif
