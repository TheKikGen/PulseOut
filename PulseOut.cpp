/**********************************************************************************
  PulseOut.  Pulse Generator class.
  Implementation cpp file.
  Franck Touanen - Dec 2017.
************************************************************************************/
#include <Arduino.h>
#include "PulseOut.h"

// Constructor
PulseOut::PulseOut(uint8_t pin, unsigned long duration, uint8_t pulse, bool square ):
 _pin(pin),_duration(duration), _pulse(pulse), _square(square) 
  {
      _mustStart = false;
      _isActive  = false;
      _previousMillis = 0;
  }

// Getters
uint8_t PulseOut::getPin() { return _pin ; }

// Public methods
void PulseOut::begin() {
      // Initial PIN state according pulse type
      pinMode(_pin, OUTPUT);
      _pinState  = !_pulse;
      digitalWrite(_pin, _pinState);
}

bool PulseOut::start(){ 
  if (_mustStart) return false; // Wait the next update
  _mustStart = ! _isActive;
  return _mustStart;
}

void PulseOut::update(unsigned long currentMillis) {
  update(&currentMillis);
}
void PulseOut::update(unsigned long* pcurrentMillis)
{
  if (_isActive) {
   if ( *pcurrentMillis - _previousMillis >= _duration ) {
      // end of a pulse
      if (!_square  || (_pinState != _pulse) ) {
              _pinState = !_pulse;
              digitalWrite(_pin, _pinState );
              _isActive = false;
      }
      // Generate square if we just ended previous pulse part
      else {
              _pinState = !_pulse;
              digitalWrite(_pin, _pinState );
              _previousMillis = *pcurrentMillis;
      }
   }
 } else 
 if (_mustStart) {
    _previousMillis = *pcurrentMillis;
    _pinState = _pulse;
    digitalWrite(_pin, _pinState);
    _isActive = true;
    _mustStart = false;
 }
 
}
