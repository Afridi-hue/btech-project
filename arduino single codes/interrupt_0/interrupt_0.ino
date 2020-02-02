// Interrupt pin on arduino uno and nano are pin 2 and pin 3.
// 0 means the pin2 and 1 means pin3
volatile boolean ledon=false;
void setup()
{
	pinMode(13,OUTPUT);
	pinMode(2,INPUT);
	attachInterrupt(0,buttonPressed,RISING);
}


void loop()
{

}

void buttonPressed()
{
	if (ledon)
	{
		ledon=false;
		digitalWrite(13,LOW);
	}
	else
	{
		ledon=true;
		digitalWrite(13,HIGH);
	}
}