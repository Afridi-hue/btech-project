/*
  Using MAX7219
	input from pi
        ped_input=2;
        em_input=3;
    pin 4 is connected to LOAD
    pin 5 is connected to the CLK
    pin 6 is connected to the DataIn
    servo connections
        inner_servo=7
        outer_servo=8
        veh_servo=9
    led
        veh_led_green=10;
        veh_led_red=11;
        ped_led_green=12;
        ped_led_red=13;
    buzzer
        buzzer=A0;

*/

// Including the library for MAX7219 and servo
#include "LedControl.h"
#include <Servo.h>

// Variables
ctions
void ped_cross();int number, l_seg, r_seg;
int ped_delay = 10;
int veh_delay = 20;
int em_delay = 30;

// Fun
void em_cross();
void veh_cross();

// Function for calculate left and right value of a number
void calculate_left_right(int);

// turning the indicator light and buzzer and servo
// veh_g,veh_r,ped_g,ped_r,buzzer,inner_servo,outer_servo,veh_servo
void indicator_and_buzzer(int, int, int, int, int, int, int, int);

// Writing to the 4 seven segment
void data_write_display(int, int, int, int, int);

// Servo objects
Servo inner_servo, outer_servo, veh_servo;

// Input from raspberry pi
int ped_input = 2;
int em_input = 3;

// Led
int veh_led_green = 10;
int veh_led_red = 11;
int ped_led_green = 12;
int ped_led_red = 13;

// Buzzer
int buzzer = A0;

// MAX7219 object
LedControl lc = LedControl(6, 5, 4, 1); // data_in,clk,load,no_of_ic

void setup()
{
  Serial.begin(9600);

  // Adding interrupt on the 2 and 3
  pinMode(ped_input, INPUT);
  pinMode(em_input, INPUT);

  // Adding the interrupt function when interrupt has occured
  attachInterrupt(0, ped_cross, RISING);
  attachInterrupt(1, em_cross, RISING);

  // Servo connections
  inner_servo.attach(7);
  outer_servo.attach(8);
  veh_servo.attach(9);

  // Making gate in down position
  inner_servo.write(0);
  outer_servo.write(0);
  veh_servo.write(0);

  // Setting led and buzzer as output
  for (int i = 10; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(buzzer, OUTPUT);

  // The MAX72XX is in power-saving mode on startup,
  // We have to do a wakeup call
  lc.shutdown(0, false);

  // Set the brightness to a medium values
  lc.setIntensity(0, 8);

  // And clear the display
  lc.clearDisplay(0);
  delay(2000);
}




void loop()
{
  Serial.println("ped_cross");
  ped_cross();
  delay(1000);
  Serial.println("veh_cross");
  veh_cross();
  delay(1000);
  Serial.println("em_cross");
  em_cross();
  delay(1000);
}

void ped_cross()
{
  indicator_and_buzzer(0, 1, 1, 0, 0, 90, 90, 0);

  // Set the delay for the ped crossing
  for (int i = ped_delay; i >= 0; i--)
  {
    calculate_left_right(i);
    data_write_display(l_seg, r_seg, 0, 0, 1000);
  }

}
void em_cross()
{
  indicator_and_buzzer(0, 1, 0, 1, 1, 0, 0, 0);
  // Set the delay for the em_veh crossing
  for (int i = em_delay; i >= 0; i--)
  {
    calculate_left_right(i);
    data_write_display(l_seg, r_seg, l_seg, r_seg, 1000);
  }


}
void veh_cross()
{
  indicator_and_buzzer(1, 0, 0, 1, 0, 0, 0, 90);
  // Set the delay for the veh crossing
  for (int i = veh_delay; i >= 0; i--)
  {
    calculate_left_right(i);
    data_write_display(0, 0, l_seg, r_seg, 1000);
  }

}


void calculate_left_right(int number)
{

  Serial.println(number);
  if (number < 10)
  {
    l_seg = 0;
    r_seg = number;
  }
  else
  {
    l_seg = number / 10;
    r_seg = number % 10;
  }

}


// Function for on/off the indicator and buzzer
void indicator_and_buzzer(int vg, int vr, int pg, int pr, int bz, int is, int os, int vs)
{

  digitalWrite(veh_led_green, vg);
  digitalWrite(veh_led_red, vr);
  digitalWrite(ped_led_green, pg);
  digitalWrite(ped_led_red, pr);
  digitalWrite(buzzer, bz);
  inner_servo.write(is);
  outer_servo.write(os);
  veh_servo.write(vs);

}


// Function to display delay in the seven segment display
void data_write_display(int a, int b, int c, int d, int time_delay)
{
  lc.setDigit(0, 0, a, false);	// false for not including the dp
  lc.setDigit(0, 1, b, false);
  lc.setDigit(0, 2, c, false);
  lc.setDigit(0, 3, d, false);
  delay(1000);
}
