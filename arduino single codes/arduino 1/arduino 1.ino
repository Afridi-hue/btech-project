//NOTE
/*
pedestrain and vehicle led should be connected using the inverting IC
>>>>Code for reading data from the pinMode
    if(Serial.available())
    {         
    // Reading data from the pi
    data = Serial.read();
    Serial.println(data); // Printing the data
    }
*/

// Adding the external libraries
#include <Servo.h>

// 7 segment pins 
int l_segment[4] = {2,3,4,5}; // Adding left segment pins
int r_segment[4] = {6,7,8,9}; // Adding right segment pins

// Declaring functions
void calculate(int);
void data_write(int,int);
int number,l_seg,r_seg;

// External connections
int em_pin=10; // Pin for activating the emergency case
int ped_pin=11 // Pin for activating the pedestrain crossing
int em_state,ped_state; // Variable for storing the state of the em and ped
int buzzer=12; // Pin to connect the buzzer
int vehicle_led_green=13;   // Pin to connect the vehicle led green
int ped_led_green=A0; // Pin to connect the pedestrain led green
int vehicle_led_red=A1;   // Pin to connect the vehicle led green
int ped_led_red=A2; // Pin to connect the pedestrain led green
// Servo objects
Servo in_servo;
Servo out_servo;
Servo gate_servo;
// Servo pins
int in_servo_pin=A3; // Pin to connect the inner servo
int out_servo_pin=A4;  // Pin to connect the outer servo
int gate_servo_pin=A5;   // Pin to connect the gate servo


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


// Functions
void emergency_case();
void pedestrain_case();
void vehicle_case();

void setup()
{
 serial.begin(9600) ;
 // Attaching the servo
 in_servo.attach(in_servo_pin);
 out_servo.attach(out_servo_pin);
 gate_servo.attach(gate_servo_pin);

 for(int i=0;i<4;i++)
    {
    pinMode(l_segment[i],OUTPUT);
    pinMode(r_segment[i],OUTPUT);
    } 
    pinMode(buzzer,OUTPUT);
    pinMode(ped_led_green,OUTPUT);
    pinMode(vehicle_led_green,OUTPUT);
    pinMode(ped_led_red,OUTPUT);
    pinMode(vehicle_led_red,OUTPUT);
    pinMode(em_pin,INPUT_PULLUP);
    pinMode(ped_pin,INPUT_PULLUP);

}
void loop()
{
  
 delay(300);
 Serial.println(em_state);
 Serial.println(ped_state);
 if (em_state==1)
 {
     emergency_case();
 }
 else if (ped_state==1)
 {
     pedestrain_case();
 }
 else
 {
     vehicle_case();
 }
 
 }




void emergency_case()
{
    digitalWrite(ped_led_red,1);
    digitalWrite(buzzer,1);
    out_servo.write(0);
    //led segment off
    delay(5000);
    in_servo.write(0);
    digitalWrite(buzzer,0);
    out_servo.write(90);
    
    //

 
    // closing the outer gate
    // timer starts for crossing
    //second gate close
    in_servo.write(0);
    //opening the main barrier
    gate_servo.write(90);

}
void pedestrain_case()
{
    // main gate close
// other gates open
// traffic light red
//activates the timer

}
void vehicle_case()
{
    //main barrier open
    //other gates close
    //signal green time

}





 



// Zebra crossing code starts

int em_veh_pin=2;
int 
void left_indication(int);
void right_indication(int);
void open_gate_l(int);
void close_gate_1(int);
void open_gate_r(int);
void close_gate_(int);
void setup()
{

}

void loop()
{
    
}
// Zebra crossing code ends

















void calculateLeft(int); //functions for calculating the left of score board
void calculateRight(int);//functions for calculating the right of score board
void left_data_write(int,int);   //functions for writing left and right segment
void right_data_write(int,int);



void setup()
{
    pinMode(left_up_pin,INPUT);
    pinMode(left_down_pin,INPUT);
    pinMode(right_up_pin,INPUT);
    pinMode(right_down_pin,INPUT);

    //setting all pins as output
    for(int i=0;i<4;i++)
    {
    pinMode(la[i],OUTPUT);
    pinMode(lb[i],OUTPUT);
    pinMode(ra[i],OUTPUT);
    pinMode(rb[i],OUTPUT);
    }

}
void loop()
{
    left_read_up=digitalRead(left_up_pin);
    left_read_down=digitalRead(left_down_pin);
    right_read_up=digitalRead(right_up_pin);
    right_read_down=digitalRead(right_down_pin);
    
    if (left_read_up==1)
    {   
        left_score+=1;
        left_read_up=0;
        calculateLeft(left_score);
    }
    else if (left_read_down==1)
    {   
        left_score-=1;
        left_read_down=0;
        calculateLeft(left_score);
    }


    else if (right_read_up==1)
    {   
        right_score+=1;
        right_read_up=0;
        calculateRight(right_score);
    }
    else if (right_read_down==1)
    {   
        right_score-=1;
        right_read_down=0;
        calculateRight(right_score);
    }
}

void calculateLeft(int left_score)
{
    if (left_score<10)
    {
        lb_score=left_score;
        la_score=0;
    }
    else
    {
        lb_score=left_score % 10;
        la_score=left_score/10;
    }
    //clear_data();
    left_data_write(la_score,lb_score);
    
    
}
void calculateRight(int right_score)
{
    if (right_score<10)
    {
        ra_score=right_score;
        rb_score=0;
    }
    else
    {
        ra_score=right_score % 10;
        rb_score=right_score/10;
    }
    //clear_data();
    right_data_write(ra_score,rb_score);
    
}
//function to clear the data on the segment
/*void clear_data()
{
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(l_pins[j],0);
    }
 
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(r_pins[j],0);
    }
}*/



void left_data_write(int left,int right) 
{
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(la[j], BCD[left+1][j]);
    }
 
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(lb[j], BCD[right+1][j]);
    }
  
}
void right_data_write(int left,int right) 
{
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(ra[j], BCD[left+1][j]);
    }
 
    for (int j=0; j < 4; j++) 
    {
        digitalWrite(rb[j], BCD[right+1][j]);
    }
  
}