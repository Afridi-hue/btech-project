// 7 segment pins
int l_seg[4] = {2,3,4,5}; // Adding left segment pins
int r_seg[4] = {6,7,8,9}; // Adding right segment pins

// External connections
int em_pin=2; // pin for activating the emergency case
int ped_pin=3 // pin for activating the pedestrain crossing
int in_servo=10; // Pin to connect the inner servo
int out_servo=11;  // Pin to connect the outer servo
int gate1=12;   // Pin to connect the gate pin
int buzzer=13; // Pin to connect the buzzer

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
 for(int i=0;i<4;i++)
    {
    pinMode(l_seg[i],OUTPUT);
    pinMode(r_seg[i],OUTPUT);
    } 
    pinMode(in_servo,OUTPUT);
    pinMode(out_servo,OUTPUT);
    pinMode(gate1,OUTPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(em_pin,INPUT);
    pinMode(ped_pin,INPUT);

}
void loop()
{
 if(Serial.available())
    {         
    // Reading data from the pi
    data = Serial.read();
    Serial.println(data); // Printing the data
    }
}




void emergency_case()
{
    digitalWrite(buzzer,1);
    // closing the outer gate
    // timer starts for crossing
    //second gate close
    //opening the main barrier

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