/**********************************************************************************
  PulseOut.  Pulse Generator class.
  Implementation cpp file.
  Franck Touanen - Dec 2017.
************************************************************************************/
#include <Arduino.h>
#include "PulseOut.h"

// Constructor
PulseOut::PulseOut(uint8_t pin, long duration, uint8_t pulse, bool square )
  {
      _Pin       = pin;
      _Duration  = duration;
      if ( pulse != NULL) _Pulse     = pulse;
      if (square != NULL) _Square    = square;

      _MustStart = false;
      _IsActive  = false;
      _PreviousMillis = 0;
  }

// Public methods
void PulseOut::Begin() {
      // Initial PIN state according pulse type
      pinMode(_Pin, OUTPUT);
      _PinState  = !_Pulse;
      digitalWrite(_Pin, _PinState);
}

// Getters
uint8_t PulseOut::GetPin() { return _Pin ; }

bool PulseOut::Start(){ 
  if(!_IsActive)_MustStart = true;
  return _MustStart;
}

void PulseOut::Update(unsigned long currentMillis)
{
 if (_MustStart) {
    _PreviousMillis = currentMillis;
    _PinState = _Pulse;
    digitalWrite(_Pin, _PinState);
    _IsActive = true;
    _MustStart = false;
 }
 else if (_IsActive) {
   if ( currentMillis - _PreviousMillis >= _Duration ) {
      // end of a pulse
      if (!_Square  || (_PinState != _Pulse) ) {
              _PinState = !_Pulse;
              digitalWrite(_Pin, _PinState );
              _IsActive = false;
      }
      // Generate square if we just ended previous pulse part
      else {
              _PinState = !_Pulse;
              digitalWrite(_Pin, _PinState );
              _PreviousMillis = currentMillis;
      }
   }
 }
}
