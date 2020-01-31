int l_segment[4] = {2,3,4,5}; // Adding left segment pins
int r_segment[4] = {6,7,8,9}; // Adding right segment pins
int ped_segment[4] = {10,11,12,13}; // pedestarin pins
int number,l_seg,r_seg;
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
    pinMode(veh_led_green,OUTPUT);
    pinMode(ped_led_red,OUTPUT);
}


void loop()
{
    analogWrite(veh_led_green,255);
    analogWrite(ped_led_red,0);
    for(int i=15;i>=0;i--)
    {
        number=i;
        Serial.println(number);
        calculate_veh(number);
        delay(1000);
    }

    analogWrite(veh_led_green,0);
    analogWrite(ped_led_red,255);
    for(int i=9;i>=0;i--)
    {
        number=i;
        Serial.println(number);
        calculate_ped(number);
        delay(1000);
    }
}

void calculate_veh(int number)
{

    if (number<10)
    {
        r_seg=number;
        l_seg=0;
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
        r_seg=number;
        l_seg=0;
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
