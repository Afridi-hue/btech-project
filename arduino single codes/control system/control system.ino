//4 segment connection
int la[4] = {17,14,15,16}; // left first
int lb[4] = {17,14,15,16}; // left second
int ra[4] = {17,14,15,16}; // right first
int rb[4] = {17,14,15,16}; // right first

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


 

//void clear_data(); //function for clearing the screen.




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

int left_up_pin=2; //button pin for increment the left score
int left_down_pin=3; //button pin for decrement the left score
int right_up_pin=4; //button pin for increment the right score
int right_down_pin=5; //button pin for decrement the right score


int left_read_down=0; //variable to read the state of the left down button
int left_read_up=0;  //variable to read the state of the left up button
int right_read_down=0; //variable to read the state of the right down button
int right_read_up=0;  //variable to read the state of the right up button

int left_score=0; //variable to store the actual score
int la_score=0; //variable to store the first digit of score
int lb_score=0;  //varible to store the second digit of score

int right_score=0; //variable to store the actual score
int ra_score=0; //variable to store the first digit of score
int rb_score=0;  //varible to store the second digit of score


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