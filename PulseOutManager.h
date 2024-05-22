/**********************************************************************************
  PulseOutManager.  Pulse Generator class.
  Header file.
  
************************************************************************************/
#ifndef PulseOutManager_h
#define PulseOutManager_h

#include <Arduino.h>
#include "PulseOut.h"

#define PULSEOUT_MAX_PIN  50 // For 40 pins from 0 to 39
class PulseOutManager
  {
    private:

    public:
      PulseOutManager();
      uint8_t getCount();
      PulseOut* factory( uint8_t pin, unsigned long duration, uint8_t pulse=HIGH, bool square=false );
      bool add(PulseOut* pulse);
      bool remove(PulseOut* pulse);
      void clear();
      void begin();
      void startAll();
      void update(unsigned long currentMillis);
      void update(unsigned long* pcurrentMillis);
    private:
      // Class Member Variables
      PulseOut* _pulses[PULSEOUT_MAX_PIN];
      bool      _mustStartAll = false ;
      uint8_t   _pulseCounter = 0     ;       // the # of pulse currently active
  };

#endif
