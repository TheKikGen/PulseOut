// PulseOut Demo sketch
// Franck Touanen - Dec 2017

#include "PulseOutManager.h"

// Declare Pulse on Arduino digital pins

PulseOut MyPulse0(14,20000);
PulseOut MyPulse1(15,15000);
PulseOut MyPulse2(13,10000,LOW,true);
PulseOut MyPulse3(16,5000,HIGH,true);
PulseOut MyPulse4(17,1000,HIGH,true);
PulseOut MyPulse5(18,750);
PulseOut MyPulse6(19,500);

// Declare a pulse manager
PulseOutManager myPulseManager;

SIGNAL(TIMER0_COMPA_vect)
{
  unsigned long currentMillis = millis();

  // Let the manager doing stuffs 
  //myPulseManager.update(&currentMillis);
  //myPulseManager.update(currentMillis);
  myPulseManager.update(millis());
}

void setup()
{
 // Timer0 is already used for millis() - we'll just interrupt somewhere
 // in the middle and call the "Compare A" function below
 OCR0A = 0xAF;
 TIMSK0 |= _BV(OCIE0A);

 // Add pulses to the pulse manager
 myPulseManager.add(&MyPulse0);
 myPulseManager.add(&MyPulse1);
 myPulseManager.add(&MyPulse2);
 myPulseManager.add(&MyPulse3);
 myPulseManager.add(&MyPulse4);
 myPulseManager.add(&MyPulse5);
 myPulseManager.add(&MyPulse6);
 myPulseManager.begin();

 // Start All pulses now !

 myPulseManager.startAll();

}

void loop()
{
  unsigned long currentMillis = millis();
  //myPulseManager.Update(millis()); // OK
  //myPulseManager.Update(&currentMillis); //OK
  // Start starts or restarts a pulse
  // and returns true is the pulse was started at the last call  
  
  if ( MyPulse4.start() ) {
       MyPulse5.start();
       MyPulse6.start();    
  }
  

  
}
