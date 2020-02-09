// Adding interrupt on the 2 and 3
/*
Using MAX7219
    pin 2 is connected to LOAD
    pin 3 is connected to the CLK
    pin 4 is connected to the DataIn    
    servo connections 
        inner_servo=5
        outer_servo=6
        veh_servo=7
    led
        veh_led_green=8;
        veh_led_red=9;
        ped_led_green=10;
        ped_led_red=11;
    buzzer
        buzzer=12;
    input from pi
        ped_input=A0;
        em_input=A1;
        
*/

// Including the library for MAX7219 and servo
#include "LedControl.h"
#include <Servo.h>

//variables
int number,l_seg,r_seg;
int ped_delay=10;
int veh_delay=30;
int em_delay=60;

// functions
void ped_cross();
void em_cross();
void veh_cross();

// Function for calculate left and right value of a number
void calculate_left_right(int);

// turning the indicator light and buzzer
// veh_g,veh_r,ped_g,ped_r,buzzer
void indicator_and_buzzer(int,int,int,int,int);

// writing to the 4 seven segment
void data_write_display(int,int,int,int,int);

// Servo objects
Servo inner_servo,outer_servo,veh_servo;

// input from raspberry pi
int ped_input=A0;
int em_input=A1;

// led
int veh_led_green=8;
int veh_led_red=9;
int ped_led_green=10;
int ped_led_red=11;

// buzzer
int buzzer=12;

// MAX7219 object
LedControl lc=LedControl(4,3,2,1);  // data_in,clk,load,no_of_ic

void setup() {
    Serial.begin(9600);

    // servo connections
    inner_servo.attach(5);
    outer_servo.attach(6);
    veh_servo.attach(7);
    
    // making gate in down position
    inner_servo.write(0);
    outer_servo.write(0);
    veh_servo.write(0);
    // setting led and buzzer as output
    for(int i=8;i<=12;i++)
    {
        pinMode(i, OUTPUT);
    }
    
    // setting input from pi
    // initially the pin will be high always...
    pinMode(ped_input, INPUT_PULLUP);
    pinMode(em_input, INPUT_PULLUP);

    // The MAX72XX is in power-saving mode on startup,
    // we have to do a wakeup call
    lc.shutdown(0,false);
    // Set the brightness to a medium values
    lc.setIntensity(0,8);
    //and clear the display
    lc.clearDisplay(0);
    delay(1000);
}




void loop() 
{
    
    int ped_value=digitalRead(ped_input);
    int em_value=digitalRead(em_input);
    Serial.println(ped_value);
    Serial.println(em_value);
  	if (ped_value==0)
  	{
     Serial.println("ped_cross");
      ped_cross();
      
  	}
  	else if(em_value==0)
  	{
     Serial.println("em_cross");
      em_cross();
      
  	}
  	else if (em_value==1 && ped_value==1)
  	{
     Serial.println("veh_cross");
     veh_cross();
      
  	}
    delay(300);
}

void ped_cross()
{
    indicator_and_buzzer(0,1,1,0,0);

    // set the delay for the ped crossing
    for(int i=ped_delay;i>=0;i--)
    {
        calculate_left_right(i);
        data_write_display(l_seg,r_seg,0,0,1000);
    }
    
}
void em_cross()
{
    indicator_and_buzzer(0,1,0,1,1);
     // set the delay for the em_veh crossing
    for(int i=em_delay;i>=0;i--)
    {
        calculate_left_right(i);
        data_write_display(l_seg,r_seg,l_seg,r_seg,1000);
    }

   
}
void veh_cross()
{
   indicator_and_buzzer(1,0,0,1,0);
     // set the delay for the veh crossing
    for(int i=veh_delay;i>=0;i--)
    {
        calculate_left_right(i);
        data_write_display(0,0,l_seg,r_seg,1000);
    }

}


void calculate_left_right(int number)
{
  Serial.println(number);
    if (number<10)
    {
        l_seg=0;
        r_seg=number;     
    }
    else
    {
      l_seg=number/10;
      r_seg=number % 10;   
    }

}


// Function for on/off the indicator and buzzer
void indicator_and_buzzer(int vg,int vr,int pg,int pr,int bz)
{
	
	digitalWrite(veh_led_green,vg);
	digitalWrite(veh_led_red,vr);
	digitalWrite(ped_led_green,pg);
	digitalWrite(ped_led_red,pr);
	digitalWrite(buzzer,bz);

}


// Function to display delay in the seven segment display
void data_write_display(int a, int b,int c,int d,int time_delay)
{
    lc.setDigit(0,0,a,false);	// false for not including the dp
	lc.setDigit(0,1,b,false);
    lc.setDigit(0,2,c,false);
    lc.setDigit(0,3,d,false);
    delay(1000);
}
