#include <VarSpeedServo.h>
//from below to upwards (1-3)
VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
VarSpeedServo servo5;

VarSpeedServo camServo;


//vcc pin
const int vcc_1 = 13;
const int vcc_2 = 12;

//read pins
const int auto_mode = 23;

const int forward = 25;
const int backward = 27;
const int left = 29;
const int right = 31;

const int grab = 33;

const int glass = 37;
const int metal = 39;
const int paper = 41;
const int plastic = 43;

//write pins
const int relay_1 = 22;
const int relay_2 = 24;
const int relay_3 = 26;
const int relay_4 = 28;

//pwm pins
const int servo_1 = 6;
const int servo_2 = 5;
const int servo_3 = 4;
const int servo_4 = 3;
const int servo_5 = 2;

const int cam_servo=7;

//sonar for grabbing
const int trigPin = 34;
const int echoPin = 35;





void setup() {
  //vcc pin
  pinMode(vcc_1,OUTPUT);
  digitalWrite(vcc_1,HIGH);
  pinMode(vcc_2,OUTPUT);
  digitalWrite(vcc_2,HIGH);
  
  //motor_setup
  pinMode(relay_1,OUTPUT);
  pinMode(relay_2,OUTPUT);
  pinMode(relay_3,OUTPUT);
  pinMode(relay_4,OUTPUT);

  pinMode(forward,INPUT);
  pinMode(backward,INPUT);
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  

  digitalWrite(relay_1,HIGH);
  digitalWrite(relay_2,HIGH);
  digitalWrite(relay_3,HIGH);
  digitalWrite(relay_4,HIGH);

  /*digitalWrite(forward,LOW);
  digitalWrite(backward,LOW);
  digitalWrite(left,LOW);
  digitalWrite(right,LOW);*/
  
  digitalWrite(auto_mode,LOW); //check if it is unnecessary
  
  //control signals from raspberry pi
  
  //servo_setup
  //default_hand_code
  default_hand();

  //cam servo
  camServo.attach(cam_servo);
  camServo.write(90,10,true);

  //sonar for grabbing
  pinMode(trigPin, OUTPUT);
  
  
  Serial.begin(9600);
  Serial.println("Setup Completed");

}

void loop() {
  if(digitalRead(auto_mode)==HIGH){
    auto_bot();
  }
  else{
    human_control();
  }

}

void auto_bot(){
  //auto drive code goes here
  //grabbing should releasr 1st 
  servo5.write(20,90,true);
  delay(2000);
  default_hand(); //to avoid collision if auto_mode is pressing during human_mode grabbing function

  //algo for auto_bot (later add)
  
  Serial.println("auto_bot");
}

void human_control(){
  //reset_relay();
  if(digitalRead(forward)==HIGH){
    move_forward();
    //reset_relay();
  }
  else if(digitalRead(backward)==HIGH){
    move_backward();
   //reset_relay();
  }
  else if(digitalRead(left)==HIGH){
    move_left();
    //reset_relay();
  }
  else if(digitalRead(right)==HIGH){
    move_right();
    //reset_relay();
  }
  else{
    reset_relay();
  }
  if (digitalRead(grab)==HIGH){
    int dist=check_distance();
    if(dist >= 8 && dist <= 12){
      grab_object();
  }else{
    Serial.println("Insufficient Distance");
  }
    
  }
  
}

void move_forward(){
  digitalWrite(relay_1,HIGH);
  digitalWrite(relay_2,LOW);
  digitalWrite(relay_3,HIGH);
  digitalWrite(relay_4,LOW);
  Serial.println("forward");
}
void move_backward(){
  digitalWrite(relay_1,LOW);
  digitalWrite(relay_2,HIGH);
  digitalWrite(relay_3,LOW);
  digitalWrite(relay_4,HIGH);
  Serial.println("backward");
}
void move_left(){
  digitalWrite(relay_1,HIGH);
  digitalWrite(relay_2,LOW);
  digitalWrite(relay_3,HIGH);
  digitalWrite(relay_4,HIGH);
  Serial.println("left");
}
void move_right(){
  digitalWrite(relay_1,HIGH);
  digitalWrite(relay_2,HIGH);
  digitalWrite(relay_3,HIGH);
  digitalWrite(relay_4,LOW);
  Serial.println("right");
}
void grab_object(){
  //robot_hand function goes here
  Serial.println("grabbing");
  
  //grab
  /*servo1.write(180,50,true);
  delay(1000);
  servo2.write(10,50,true);
  delay(1000);*/
  servo3.write(10,50,true);
  delay(1000);
  /*servo4.write(90,50,true);
  delay(1000);
  servo5.write(20,50,true);
  delay(5000);
  servo5.write(90,50,true);
  delay(1000);*/
  servo3.write(90,50,true);
  delay(1000);
  /*servo2.write(90,50,true);
  delay(1000);*/

  Serial.println("Grabbing Complete");

  //store
  /*servo1.write(0,50,true);
  delay(1000);
  servo3.write(20,50,true);
  delay(1000);
  servo5.write(20,50,true);
  delay(2000);
  servo5.write(90,50,true);
  delay(1000);*/
  servo3.write(90,50,true);
  delay(1000);

  Serial.println("Storing Complete");

  default_hand();
  
  
  
}

void default_hand(){
  Serial.println("Default hand");
  servo1.attach(servo_1);
  servo1.write(90,50,true);
  servo2.attach(servo_2);
  servo2.write(90,50,true);
  servo3.attach(servo_3);
  servo3.write(90,50,true);
  servo4.attach(servo_3);
  servo4.write(90,50,true);
  servo5.attach(servo_3);
  servo5.write(90,50,true);
  
  delay(6000);
}

int check_distance(){
  long duration;
  int distance; 
  //make sure trig pin is clear
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //start measuring distance using duration
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  return distance;
  
}

//auto_bot function
int cam_angle(){
  while(true){
    camServo.write(0,90,true);
    delay(5000);
    if(check_type()==1){
      //turn left 45 degree and approach there
    }
    camServo.write(45,90,true);
    delay(5000);
    if(check_type()==1){
      //move forward and approach there
    }
    camServo.write(90,90,true);
    delay(5000);
    if(check_type()==1){
      //turn right and approach there
    }
  }
  
}

int check_type(){
  if(digitalRead(glass) == HIGH){
    //rotate basket servo
    return 1;
  }
  else if(digitalRead(metal) == HIGH){
    //rotate basket servo
    return 1;
  }
  else if(digitalRead(paper) == HIGH){
    //rotate basket servo
    return 1;
  }
  else if(digitalRead(plastic) == HIGH){
    //rotate basket servo
    return 1;
  }
  else{
    return 0;
  }
  
}

void reset_relay(){
  digitalWrite(relay_1,HIGH);
  digitalWrite(relay_2,HIGH);
  digitalWrite(relay_3,HIGH);
  digitalWrite(relay_4,HIGH);
}
