#include <Servo.h>
#define A 10
#define B 11
#define C 12
#define D 13
#define tr 6
#define br 7
#define bl 8
#define tl 9
Servo ser_tr, ser_br, ser_bl, ser_tl; //tr = top right, br = bottom right, bl = bottom left, tl = top left, 
int control_signal =0;
//control the speed of the motor
void speed_up(int right_motors, int left_motors){
    int speed = 0;  //control the speed of the motors
    while(speed < 25)
    {
        analogWrite(right_motors, speed);   //write signal to pin controlling right motors
        analogWrite(left_motors, speed);    //write signal to pin controlling left motors
        delay(1000);    //wait 1s
        ++speed;    //increase speed by 1 
    }
}

//control the high and low current into the L298
void motor(int hi_right, int lo_right, int hi_left, int lo_left){
    //hi and lo current into the right motors
    digitalWrite(hi_right, 1);
    digitalWrite(lo_right, 0);
    //hi and lo current into the left motors
    digitalWrite(hi_left, 1);
    digitalWrite(lo_left, 0);
}

//function to move the motor
void move(){
    int speed = 0;
    if (digitalRead(A) == 1 && digitalRead(C) == 1)     //equivalant to B = 0, D = 0
    {
        speed_up(A, C); //motors set to go straight ahead, use A and C to control the motors
    }
    else if (digitalRead(A) == 0 && digitalRead(C) == 0)    //equivalant to B = 1, D = 1
    {
        speed_up(B, D); //motors set to go backward, use B and D to control the motors
    }
    else if (digitalRead(A) == 0 && digitalRead(C) == 1)    //equivalant to B = 1, D = 0
    {
        speed_up(B, C); //left motors go straight and right motors go backward => tank rotation
    }
}

//function to control the angle of the servo
void steer(int ang_right, int ang_left){
    //ang_x = angle of each servo
    ser_tr.write(ang_right);
    ser_br.write(ang_right);
    ser_bl.write(ang_left);
    ser_tl.write(ang_left);
}

void setup()
{   
    //setup pins
    Serial.begin(9600);
    pinMode(A, OUTPUT);    //right motor A 
    pinMode(B, OUTPUT);    //right motor B
    pinMode(C, OUTPUT);    //left motor C
    pinMode(D, OUTPUT);    //left motor D
    //initialize pin motors to 0 => no movements
    digitalWrite(A, 0);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    ser_tr.attach(tr);   //top right servo
    ser_br.attach(br);   //bottom right servo
    ser_bl.attach(bl);   //bottom left servo
    ser_tl.attach(tl);   //top left servo
    steer(0, 0);    //initialize angles of the servos at 0 degree
}

void loop()
{
    int data_in = Serial.read();
    if (data_in != -1 && data_in != control_signal)
    control_signal = data_in;
    Serial.print(control_signal);
    Serial.print("\n");
    delay(1000);
    /*switch(control_signal){
        case 8:     //go straight
            motor(A, B, C, D);
            steer(0, 0);
            move();
            break;
        case 9:     //turn right straight 
            motor(A, B, C, D);
            steer(45, 18);
            move();
            break;
        case 10:    //turn left straight
            motor(A, B, C, D);
            steer(18, 45);
            move();
            break;
        case 4:     //go backward
            motor(B, A, D, C);
            steer(0, 0);
            move();
            break;
        case 5:     //turn right backward
            motor(B, A, D, C);
            steer(45, 18);
            move();
            break;
        case 6:     //turn left backward 
            motor(B, A, D, C);
            steer(18, 45);
            move();
            break;
        case 12:    //tank rotation
            motor(B, A, C, D);
            steer(0, 0);
            move();
            break;
        default:    //nothing happens
            digitalWrite(A, 0);
            digitalWrite(B, 0);
            digitalWrite(C, 0);
            digitalWrite(D, 0);
            steer(0, 0);
    }*/
}
