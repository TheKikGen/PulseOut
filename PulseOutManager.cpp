/**********************************************************************************
  PulseOutManager.  Pulse Generator class.
  Implementation cpp file.
  Franck Touanen - Dec 2017.
************************************************************************************/
#include <Arduino.h>
#include "PulseOutManager.h"

// Constructor
PulseOutManager::PulseOutManager() { }

// Getters
uint8_t PulseOutManager::getCount() {return _pulseCounter;}

// Public methods

// Add a pulse to the manager
bool PulseOutManager::add( PulseOut* pulse) {
  // For fast access, we use the pin as an index for the array
  uint8_t pin = pulse->getPin();
  
  if (pin > PULSEOUT_MAX_PIN-1 ) return false;

  // Add the pulse only if no pulse already existing on that pin
  if ( _pulses[pin] == NULL ) {    
    _pulses[pin] = pulse;
    _pulseCounter++;
    return true;  
  }
  return false;
}

// Remove a pulse from the manager
bool PulseOutManager::remove( PulseOut* pulse) {
  // For fast access, we use the pin as an index for the array
  uint8_t pin = pulse->getPin();
  
  if (pin > PULSEOUT_MAX_PIN-1 ) return false;
  _pulses[pin] = NULL;
  _pulseCounter--;
  return true;  
}

// Remove all pulses from the manager
void PulseOutManager::clear() {
  if (_pulseCounter < 1) return;
  for(int i = 0; i < PULSEOUT_MAX_PIN; i++){
      _pulses[i] = NULL;
  }
  _pulseCounter = 0;
}

// Begin method (in the Setup() )
// Call all Begin methods of pulses recorded

void PulseOutManager::begin() { 
  if (_pulseCounter <1 ) return;
  // Begin All pulses recorded
  for(int i = 0; i < PULSEOUT_MAX_PIN; i++){
    if(_pulses[i] != NULL) _pulses[i]->begin();
  }  
}

// Start All Pulses at the same time at the next update
void PulseOutManager::startAll() { 
  if (_pulseCounter <1 ) return;
  _mustStartAll = true;
}

// Update all pulses
void PulseOutManager::update(unsigned long currentMillis) {
  update(&currentMillis);
}

void PulseOutManager::update(unsigned long* pcurrentMillis) {
  if (_pulseCounter <1 ) return;

  // Update all pulses recorded
  for(int i = 0; i < PULSEOUT_MAX_PIN; i++){
    if(_pulses[i] != NULL) {
      if (_mustStartAll) { _pulses[i]->start(); }
      _pulses[i]->update(pcurrentMillis);
    }
  }
  if (_mustStartAll) _mustStartAll  = false  ;
  
}



