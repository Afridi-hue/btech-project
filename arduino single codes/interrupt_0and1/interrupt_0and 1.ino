// Interrupt pin on arduino uno and nano are pin 2 and pin 3.
// 0 means the pin2 and 1 means pin3
#include "LowPower.h"
void setup()
{
	pinMode(13,OUTPUT);
	pinMode(2,INPUT);
	pinMode(3,INPUT);
	attachInterrupt(0,turnLEDon,RISING);
	attachInterrupt(1,turnLEDoff,FALLING);
}

void loop()
{
	LowPower.powerDown(SLEEP_FOREVER,ADC_OFF,BOD_OFF);

}

void turnLEDon()
{
	digitalWrite(13,HIGH);
}
void turnLEDff()
{
	digitalWrite(13,LOW);
}