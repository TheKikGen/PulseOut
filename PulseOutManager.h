/**********************************************************************************
  PulseOutManager.  Pulse Generator class.
  Header file.
  Franck Touanen - Dec 2017.
************************************************************************************/
#ifndef PulseOutManager_h
#define PulseOutManager_h

#include <Arduino.h>
#include "PulseOut.h"

#define PULSEOUT_MAX_PIN  20 // For 20 pins from 0 to 19
class PulseOutManager
  {
    public:
      PulseOutManager();
      uint8_t getCount();
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
      bool      _mustStartAll = false;
      uint8_t   _pulseCounter=0;       // the # of pulse currently active 
  };

#endif




