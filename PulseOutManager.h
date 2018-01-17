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
      bool Add(PulseOut* pulse);
      bool Remove(PulseOut* pulse);
      void Clear();            
      void Begin();
      void StartAll();
      void Update(unsigned long currentMillis);

    private:
      // Class Member Variables
      PulseOut* _Pulses[PULSEOUT_MAX_PIN];
      bool      _MustStartAll = false;
      uint8_t   _PulseCounter=0;       // the # of pulse currently active 
  };

#endif




