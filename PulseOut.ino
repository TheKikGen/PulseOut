// PulseOut Demo sketch
// Franck Touanen - Dec 2017

#include "PulseOutManager.h"

// Declare Pulse on Arduino digital pins

PulseOutManager myPulseOutManager;

PulseOut MyPulse0(14,20000);
PulseOut MyPulse1(15,15000);
PulseOut MyPulse2(13,10000,LOW,true);
PulseOut MyPulse3(16,5000,HIGH,true);

// Declare a timer. Can't be added to a manager as the pin is used as an index
PulseOut MyTimer1(0xFF,3000);

// Using the factory
PulseOut* MyPulse4 = myPulseOutManager.factory(17,1000,HIGH,true);
PulseOut* MyPulse5 = myPulseOutManager.factory(18,750);
PulseOut* MyPulse6 = myPulseOutManager.factory(19,500);


SIGNAL(TIMER0_COMPA_vect)
{
  // Let the manager doing stuffs

  myPulseOutManager.update(millis());
  MyTimer1.update(millis());

}

void setup()
{
 // Timer0 is already used for millis()
 OCR0A = 0xAF;
 TIMSK0 |= _BV(OCIE0A);

 // Add existing pulses to the pulse manager
 myPulseOutManager.add(&MyPulse0);
 myPulseOutManager.add(&MyPulse1);
 myPulseOutManager.add(&MyPulse2);
 myPulseOutManager.add(&MyPulse3);

 myPulseOutManager.begin();

 // Start All pulses now !

 myPulseOutManager.startAll();
 MyTimer1.start();
 Serial.begin(115200);

}

void loop()
{

  // Start or restarts a pulse
  // and returns true is the pulse was started at the last call

  if ( MyPulse3.start() ) {
        Serial.println("=========== Pulse3 started");
  }

   if ( MyPulse4->start() ) {
        Serial.println("=========== Pulse4 started");
  }

  if ( MyTimer1.start() ) {
        Serial.println("=========== Timer started");
  }




}
