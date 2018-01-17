/**********************************************************************************
  PulseOutManager.  Pulse Generator class.
  Implementation cpp file.
  Franck Touanen - Dec 2017.
************************************************************************************/
#include <Arduino.h>
#include "PulseOutManager.h"

// Constructor
PulseOutManager::PulseOutManager() { }

// Public methods

// Add a pulse to the manager
bool PulseOutManager::Add( PulseOut* pulse) {
  // For fast access, we use the pin as an index for the array
  if (pulse->GetPin() > PULSEOUT_MAX_PIN-1 ) return false;

  // Add the pulse only if no pulse already existing on that pin
  if ( _Pulses[pulse->GetPin()] == NULL ) {    
    _Pulses[pulse->GetPin()] = pulse;
    _PulseCounter++;
    return true;  
  }
  return false;
}

// Remove a pulse from the manager
bool PulseOutManager::Remove( PulseOut* pulse) {
  // For fast access, we use the pin as an index for the array
  if (pulse->GetPin() > PULSEOUT_MAX_PIN-1 ) return false;
  _Pulses[pulse->GetPin()] = NULL;
  _PulseCounter--;
  return true;  
}

// Remove all pulses from the manager
void PulseOutManager::Clear() {
  if (_PulseCounter < 1) return;
  for(int i = 0; i < PULSEOUT_MAX_PIN; i++){
      _Pulses[i] = NULL;
  }
  _PulseCounter = 0;
}

// Begin method (in the Setup() )
// Call all Begin methods of pulses recorded

void PulseOutManager::Begin() { 
  if (_PulseCounter <1 ) return;
  // Begin All pulses recorded
  for(int i = 0; i < PULSEOUT_MAX_PIN; i++){
    if(_Pulses[i] != NULL) _Pulses[i]->Begin();
  }  
}

// Start All Pulses at the same time at the next update
void PulseOutManager::StartAll() { 
  if (_PulseCounter <1 ) return;
  _MustStartAll = true;
}

// Update all pulses
void PulseOutManager::Update(unsigned long currentMillis) {
  if (_PulseCounter <1 ) return;

  // Update all pulses recorded
  for(int i = 0; i < PULSEOUT_MAX_PIN; i++){
    if(_Pulses[i] != NULL) {
      if (_MustStartAll) { _Pulses[i]->Start(); }
      _Pulses[i]->Update(currentMillis);
    }
  }
  if (_MustStartAll) _MustStartAll  = false  ;
  
}



