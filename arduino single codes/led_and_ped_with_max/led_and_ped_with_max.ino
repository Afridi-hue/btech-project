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
void ped_cross();
void calculate_em(int);
void data_write_em(int,int);
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
    pinMode(ped_input, INPUT_PULLUP);
    pinMode(em_input, INPUT_PULLUP);

    // The MAX72XX is in power-saving mode on startup,
    // we have to do a wakeup call
    lc.shutdown(0,false);
    // Set the brightness to a medium values
    lc.setIntensity(0,8);
    //and clear the display
    lc.clearDisplay(0);
    delay(3000);
}




void loop() 
{
    
    int ped_value=digitalRead(ped_input);
    int em_value=digitalRead(em_input);
    if (ped_value==1)
    {
        ped_cross();
    }
    else if(em_value==1)
    {
        em_cross();
    }
    else
    {
        veh_cross();
    }
}

void ped_cross()
{
    digitalWrite(veh_led_green,0);
    digitalWrite(veh_led_red,1);
    digitalWrite(ped_led_green,1);
    digitalWrite(ped_led_red,0);
    // set the delay for the ped crossing
    for(int i=ped_delay;i>=0;i--)
    {
        calculate_ped(i);
    }
    
}
void em_cross()
{
    digitalWrite(veh_led_green,0);
    digitalWrite(veh_led_red,1);
    digitalWrite(ped_led_green,0);
    digitalWrite(ped_led_red,1);
     // set the delay for the em_veh crossing
    for(int i=em_delay;i>=0;i--)
    {
        calculate_em(i);
    }
   
}
void veh_cross()
{
    digitalWrite(veh_led_green,1);
    digitalWrite(veh_led_red,0);
    digitalWrite(ped_led_green,0);
    digitalWrite(ped_led_red,1);
     // set the delay for the veh crossing
    for(int i=veh_delay;i>=0;i--)
    {
        calculate_veh(i);
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
    data_write_veh(l_seg,r_seg);

}

void calculate_em(int number)
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
    data_write_em(l_seg,r_seg); 
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
    data_write_ped(l_seg,r_seg);
    
}


void data_write_veh(int l_seg, int r_seg)
{
    
    lc.setDigit(0,3,r_seg,false);
    lc.setDigit(0,2,l_seg,false);
    lc.setDigit(0,1,0,false);
    lc.setDigit(0,0,0,false);
    delay(1000);
}

void data_write_ped(int l_seg, int r_seg)
{
    lc.setDigit(0,3,0,false);
    lc.setDigit(0,2,0,false);
    lc.setDigit(0,1,r_seg,false);
    lc.setDigit(0,0,l_seg,false);
    delay(1000);   
}


void data_write_em(int l_seg, int r_seg)
{
    lc.setDigit(0,3,0,false);
    lc.setDigit(0,2,0,false);
    lc.setDigit(0,1,0,false);
    lc.setDigit(0,0,0,false);
    delay(1000); 
}


























//int veh_led_green=A2;
//int ped_led_red=A3;
//
//void calculate_veh(int);
//void data_write_veh(int,int);
//void calculate_ped(int);
//void data_write_ped(int);
//
//
//// Binary value for 0 to 9
//int BCD[10][4] ={
//{0,0,0,0},
//{0,0,0,1},
//{0,0,1,0},
//{0,0,1,1},
//{0,1,0,0},
//{0,1,0,1},
//{0,1,1,0},
//{0,1,1,1},
//{1,0,0,0},
//{1,0,0,1}}; //BCD code
//
//
//void setup()
//{
// Serial.begin(9600) ;
// for(int i=0;i<4;i++)
//    {
//    pinMode(l_segment[i],OUTPUT);
//    pinMode(r_segment[i],OUTPUT);
//    pinMode(ped_segment[i],OUTPUT);
//    }
//    
//}
//
//
//void loop()
//{
//    analogWrite(veh_led_green,255);
//    analogWrite(ped_led_red,0);
//    for(number=15;number>=0;number--)
//    {
//        Serial.println(number);
//        calculate_veh(number);
//        delay(1000);
//    }
//
//    analogWrite(veh_led_green,0);
//    analogWrite(ped_led_red,255);
//    for(number=9;number>=0;number--)
//    {
//        Serial.println(number);
//        calculate_ped(number);
//        delay(1000);
//    }
//}
//
//void calculate_veh(int number)
//{
//
//    if (number<10)
//    {
//        l_seg=0;
//        r_seg=number;
//        
//    }
//    else
//    {
//      l_seg=number/10;
//        r_seg=number % 10;
//        
//    }
//    Serial.println(l_seg);
//    Serial.println(r_seg);
//    data_write_veh(l_seg,r_seg);
//
//}
//void calculate_ped(int number)
//{
//
//    if (number<10)
//    {
//        l_seg=0;
//        r_seg=number;
//        
//    }
//    else
//    {
//      l_seg=number/10;
//        r_seg=number % 10;
//        
//    }
//    Serial.println(l_seg);
//    Serial.println(r_seg);
//    data_write_ped(r_seg);
//
//}
//
//void data_write_veh(int l_seg,int r_seg)
//{
//
//
//     for (int j=0; j < 4; j++) 
//    {
//        digitalWrite(l_segment[j], BCD[l_seg][j]);
//    }
// 
//    for (int j=0; j < 4; j++) 
//    {
//        digitalWrite(r_segment[j], BCD[r_seg][j]);
//    }
//  
//}
//
//
//void data_write_ped(int r_seg)
//{
//
//
//     for (int j=0; j < 4; j++) 
//    {
//        digitalWrite(ped_segment[j], BCD[r_seg][j]);
//    }
//
//  
//}
