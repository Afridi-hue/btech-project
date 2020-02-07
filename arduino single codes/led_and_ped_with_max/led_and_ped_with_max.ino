/*
Using MAX7219
    pin 4 is connected to the DataIn 
    pin 3 is connected to the CLK 
    pin 2 is connected to LOAD
    servo connections 5,6,7
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

// Including the library for MAX7219
#include "LedControl.h"
#include <Servo.h>

//variables
int number,l_seg,r_seg;
// functions
void calculate_veh(int);
void data_write_veh(int,int);
void calculate_ped(int);
void data_write_ped(int);
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

// delay for ic
unsigned long delaytime=250;

void setup() {
    Serial.begin(9600);
    // servo connections
    inner_servo.attach(5);
    outer_servo.attach(6);
    veh_servo.attach(7);
    //setting led and buzzer as output
    for(int i=8;i<=12;i++)
    {
        pinMode(i, OUTPUT);
    }
    pinMode(ped_input, INPUT);
    pinMode(em_input, INPUT);
    // The MAX72XX is in power-saving mode on startup,
    // we have to do a wakeup call
    lc.shutdown(0,false);
    // Set the brightness to a medium values
    lc.setIntensity(0,8);
    //and clear the display
    lc.clearDisplay(0);
}



void scrollDigits() {
  for(int i=0;i<10;i++) {
    lc.setDigit(0,3,i,false);
    lc.setDigit(0,2,i+1,false);
    lc.setDigit(0,1,i+2,false);
    lc.setDigit(0,0,i+3,false);
    delay(delaytime*10);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() 
{
    int ped_value=digitalRead(em_input);
    int em_value=digitalRead(ped_iput);
    if (ped_value==1)
    {

    }
    elif(em_value==1)
    {

    }
    else
    {

    }
}
























int veh_led_green=A2;
int ped_led_red=A3;

void calculate_veh(int);
void data_write_veh(int,int);
void calculate_ped(int);
void data_write_ped(int);


// Binary value for 0 to 9
int BCD[10][4] ={
{0,0,0,0},
{0,0,0,1},
{0,0,1,0},
{0,0,1,1},
{0,1,0,0},
{0,1,0,1},
{0,1,1,0},
{0,1,1,1},
{1,0,0,0},
{1,0,0,1}}; //BCD code


void setup()
{
 Serial.begin(9600) ;
 for(int i=0;i<4;i++)
    {
    pinMode(l_segment[i],OUTPUT);
    pinMode(r_segment[i],OUTPUT);
    pinMode(ped_segment[i],OUTPUT);
    }
    
}


void loop()
{
    analogWrite(veh_led_green,255);
    analogWrite(ped_led_red,0);
    for(number=15;number>=0;number--)
    {
        Serial.println(number);
        calculate_veh(number);
        delay(1000);
    }

    analogWrite(veh_led_green,0);
    analogWrite(ped_led_red,255);
    for(number=9;number>=0;number--)
    {
        Serial.println(number);
        calculate_ped(number);
        delay(1000);
    }
}

void calculate_veh(int number)
{

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
    Serial.println(l_seg);
    Serial.println(r_seg);
    data_write_veh(l_seg,r_seg);

}
void calculate_ped(int number)
{

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
    Serial.println(l_seg);
    Serial.println(r_seg);
    data_write_ped(r_seg);

}

void data_write_veh(int l_seg,int r_seg)
{


     for (int j=0; j < 4; j++) 
    {
        digitalWrite(l_segment[j], BCD[l_seg][j]);
    }
 
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(r_segment[j], BCD[r_seg][j]);
    }
  
}


void data_write_ped(int r_seg)
{


     for (int j=0; j < 4; j++) 
    {
        digitalWrite(ped_segment[j], BCD[r_seg][j]);
    }

  
}
