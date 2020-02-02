int l_segment[4] = {2,3,4,5}; // Adding left segment pins
int r_segment[4] = {6,7,8,9}; // Adding right segment pins
int number,l_seg,r_seg;

void calculate(int);
void data_write(int,int);


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
    }
}


void loop()
{
    for(number=60;number>=0;number--)
    {
        Serial.println(number);
        calculate(number);
        delay(1000);
    }
}

void calculate(int number)
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
    data_write(l_seg,r_seg);

}
void data_write(int l_seg,int r_seg)
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
