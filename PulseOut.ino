// PulseOut Demo sketch
// Franck Touanen - Dec 2017

#include "PulseOutManager.h"

// Declare Pulse on Arduino digital pins

PulseOut MyPulse0(14,20000);
PulseOut MyPulse1(15,15000);
PulseOut MyPulse2(13,10000,LOW,true);
PulseOut MyPulse3(16,5000,HIGH,true);
PulseOut MyPulse4(17,1000,HIGH,true);
PulseOut MyPulse5(18,1000);
PulseOut MyPulse6(19,500);

// Declare a pulse manager
volatile PulseOutManager myPulseManager;

SIGNAL(TIMER0_COMPA_vect)
{
  unsigned long currentMillis = millis();

  // Let the manager doing stuffs 
  myPulseManager.Update(currentMillis);
}

void setup()
{
 // Timer0 is already used for millis() - we'll just interrupt somewhere
 // in the middle and call the "Compare A" function below
 OCR0A = 0xAF;
 TIMSK0 |= _BV(OCIE0A);

 Serial.begin(115200);

 // Add pulses to the pulse manager
 myPulseManager.Add(&MyPulse0);
 myPulseManager.Add(&MyPulse1);
 myPulseManager.Add(&MyPulse2);
 myPulseManager.Add(&MyPulse3);
 myPulseManager.Add(&MyPulse4);
 myPulseManager.Add(&MyPulse5);
 myPulseManager.Add(&MyPulse6);
 myPulseManager.Begin();

 Serial.println("PULSEOUT DEMO LED SHOW");
 Serial.println("======================");

 // Start All pulses now !

 myPulseManager.StartAll();

}

void loop()
{
  
  // Start starts or restarts a pulse
  // and returns true is the pulse was started at the last call  
  
  if ( MyPulse4.Start() ) {
       MyPulse5.Start();
       MyPulse6.Start();    
  }
  

  
}
