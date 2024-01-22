/* Garbage Detection and Collection Robot using Image Processing
   Device used: Arduino Mega 2560
   This code represents the mechanism of the hardwares of the robot
   Code includes two mode: Human controlled
                           Autonomous

   Functions:    Robot Movement, Robotic Hand Functions, Basket Rotation,
                 Error Detections, Alert System, Security

   Coded By:     Moin Shahriyar
                 B.Sc. in CSE
                 North South University

   Supported By: Farjana Alam
                 B.Sc. in CSE
                 North South University

   Other Members:Sarhan Osman Bhuiyan
                 B.Sc. in CSE
                 North South University

                 Md. Muhabullah
                 B.Sc. in CSE
                 North South University
*/

#include <VarSpeedServo.h>
#include <elapsedMillis.h>



//from below to upwards (1-3)
VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
VarSpeedServo servo5;
VarSpeedServo servo6;


VarSpeedServo basketServo;
VarSpeedServo camServo;


//vcc pin
const int vcc_1 = 13;

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
const int servo_1 = 7;
const int servo_2 = 6;
const int servo_3 = 5;
const int servo_4 = 4;
const int servo_5 = 3;
const int servo_6 = 2;

const int basket_servo = 8;
const int cam_servo = 9;


//sonar for grabbing
const int grab_trigPin = 34;
const int grab_echoPin = 35;

//sonar for obstacle avoidance
//right sonar
const int obs_trigPin_1 = 36;
const int obs_echoPin_1 = 37;

//left sonar
const int obs_trigPin_2 = 38;
const int obs_echoPin_2 = 39;

//time diff for turning at an angle
elapsedMillis timeDiff = 0;

//random movement time
const int moveTime = 3000; //3000 millisec = 3 sec

//rotation time for moving at an angle
const int rotateTime = 415;
/*this robot takes 32~33 sec for 10 rotation of 360 degree
   so 1 rotation of 360 degree needs 3.2~3.3 sec
   so 45 degree of rotation needs (3.3/8)=0.4125 sec ~ 412.5 millisec
   Note: This was measured with fully charged battery.
   If voltage decreases time for rotation will increase.
*/





void setup() {
  Serial.begin(9600);

  //vcc pin
  pinMode(vcc_1, OUTPUT);
  digitalWrite(vcc_1, HIGH);

  //motor_setup
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);

  //all relays set to high to deactivate
  reset_relay();


  //control signals from raspberry pi

  //servo_setup
  //default_hand_code
  default_hand();

  //cam servo
  camServo.attach(cam_servo);
  camServo.write(90, 10, true);

  //basket servo
  basketServo.attach(basket_servo);
  basketServo.write(90, 10, true);

  //sonar for grabbing
  pinMode(grab_trigPin, OUTPUT);

  //sonar for obstacle avoidance
  pinMode(obs_trigPin_1, OUTPUT);
  pinMode(obs_trigPin_2, OUTPUT);



  Serial.println("Setup Completed");

}

void loop() {
  if (digitalRead(auto_mode) == HIGH) {
    auto_bot();
  }
  else {
    human_control();
  }

}

void auto_bot() {
  //auto drive code goes here
  default_hand();
  reset_relay();
  timeDiff = 0;
  Serial.println(timeDiff);
  while (timeDiff < rotateTime) {
    move_left();
  }
  reset_relay();
  delay(5000);
  timeDiff = 0;

  while (timeDiff < rotateTime) {
    move_right();
  }
  reset_relay();
  delay(5000);
  timeDiff = 0;

  while (timeDiff < rotateTime) {
    move_right();
  }
  reset_relay();
  delay(5000);
  timeDiff = 0;
  while (timeDiff < rotateTime) {
    move_left();
  }
  reset_relay();
  delay(5000);
  timeDiff = 0;
  //max distance of object
  /*int dist = 0;



    //random movement [idea & code from "FARJANA ALAM"]
    int rand_array[] = {forward, left, right};
    int movement = 0;


    //intiate pi cam servo and get angle
    int camAngle = cam_angle();

    if (camAngle < 0) {
    //random movement
    movement = rand_array[random(0, 3)]; //excluding max value
    if (movement == forward) {
      while (timeDiff < moveTime) {
        move_forward();
      }
      timeDiff = 0;
    }
    else if (movement == left) {
      while (timeDiff < rotateTime) {
        move_left();
      }
      timeDiff = 0;
      while (timeDiff < moveTime) {
        move_forward();
      }
      timeDiff = 0;
    }
    else if (movement == right) {
      while (timeDiff < rotateTime) {
        move_right();
      }
      timeDiff = 0;
      while (timeDiff < moveTime) {
        move_forward();
      }
      timeDiff = 0;
    }
    }
    else if (camAngle == 0) {
    //rotate 45 degree left
    while (timeDiff < rotateTime) {
      move_left();
    }
    timeDiff = 0;

    dist = check_distance(grab_trigPin, grab_echoPin);
    if (dist > 15 && dist < 250) {
      move_forward();
    }
    //else condition will be applied
    }

    else if (camAngle == 45) {
    //move forward
    dist = check_distance(grab_trigPin, grab_echoPin);
    if (dist > 15 && dist < 250) {
      move_forward();
    }
    }
    else if (camAngle == 90) {
    //move 45 degree right
    while (timeDiff < rotateTime) {
      move_right();
    }
    timeDiff = 0;
    dist = check_distance(grab_trigPin, grab_echoPin);
    if (dist > 15 && dist < 250) {
      move_forward();
    }
    }



    //algo for auto_bot (later add)*/

  Serial.println("auto_bot");
}

void human_control() {
  if (digitalRead(forward) == HIGH &&
      check_distance(obs_trigPin_1, obs_echoPin_1) > 30 &&
      check_distance(obs_trigPin_2, obs_echoPin_2) > 30) {
    move_forward();
  }
  else if (digitalRead(backward) == HIGH) {
    move_backward();
  }
  else if (digitalRead(left) == HIGH &&
           check_distance(obs_trigPin_2, obs_echoPin_2) > 30) {
    move_left();
  }
  else if (digitalRead(right) == HIGH &&
           check_distance(obs_trigPin_1, obs_echoPin_1) > 30) {
    move_right();
  }
  else {
    reset_relay();
  }
  if (digitalRead(grab) == HIGH) {
    int dist = check_distance(grab_trigPin, grab_echoPin);
    if (dist >= 10 && dist <= 12) {
      grab_object();
    } else {
      Serial.println("Insufficient Distance");
    }

  }

}

void move_forward() {
  /*int dist_1 = check_distance(obs_trigPin_1, obs_echoPin_1);
    int dist_2 = check_distance(obs_trigPin_2, obs_echoPin_2);
    if (dist_1 > 30 && dist_2 > 30) {*/
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, LOW);
  Serial.println("forward");
  //}

}
void move_backward() {
  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, LOW);
  digitalWrite(relay_4, HIGH);
  Serial.println("backward");
}
void move_left() {
  /*int dist_2 = check_distance(obs_trigPin_2, obs_echoPin_2);
    if (dist_2 > 30) {*/
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_3, LOW);
  digitalWrite(relay_4, HIGH);
  Serial.println("left");
  //}
}
void move_right() {
  /*int dist_1 = check_distance(obs_trigPin_1, obs_echoPin_1);
  if (dist_1 > 30) {*/
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, HIGH);
    digitalWrite(relay_3, HIGH);
    digitalWrite(relay_4, LOW);
    Serial.println("right");
  //}
}
void grab_object() {
  reset_relay();      //bot should stop moving
  //robot_hand function goes here
  Serial.println("grabbing");

  //grab
  servo1.write(180, 50, true);
  delay(1000);
  servo2.write(60, 20, true);
  delay(1000);
  servo6.write(30, 50, true);
  delay(1000);
  servo3.write(160, 30, true);    //previous: 170
  delay(1000);
  servo5.write(90, 50, true);
  delay(1000);
  servo4.write(170, 50, true);
  delay(1000);


  servo6.write(90, 50, true);
  delay(1000);
  servo4.write(90, 50, true);
  delay(1000);
  servo3.write(90, 30, true);
  delay(1000);
  servo2.write(90, 20, true);
  delay(1000);

  Serial.println("Grabbing Complete");

  //store

  servo3.write(90, 30, true);
  delay(1000);
  servo4.write(50, 40, true);
  delay(1000);
  servo6.write(30, 50, true);
  delay(1000);
  servo6.write(90, 50, true);
  delay(1000);

  Serial.println("Storing Complete");

  default_hand();

}

void default_hand() {
  //should be upside down (6-1)
  Serial.println("Default hand");
  /*servo6.attach(servo_6);
    servo6.write(90, 50, true);
    delay(1000);
    servo5.attach(servo_5);
    servo5.write(90, 50, true);
    delay(1000);
    servo4.attach(servo_4);
    servo4.write(90, 50, true);
    delay(1000);
    servo3.attach(servo_3);
    servo3.write(90, 50, true);
    delay(1000);
    servo2.attach(servo_2);
    servo2.write(90, 50, true);
    delay(1000);
    servo1.attach(servo_1);
    servo1.write(90, 50, true);
    delay(6000);*/
}

int check_distance(int trigPin, int echoPin) {
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
  distance = duration * 0.034 / 2;

  return distance;

}

//auto_bot function
int cam_angle() {
  int camAngle = -1;          //nothing is found

  camServo.write(0, 90, true);
  delay(5000);
  if (check_type() == 1) {
    camAngle = 0;
    return camAngle;          //at 45 degree left garbage is found
  }
  camServo.write(45, 90, true);
  delay(5000);                //fix delay later if needed
  if (check_type() == 1) {
    camAngle = 45;
    return camAngle;          //at straight garbage is found
  }
  camServo.write(90, 90, true);
  delay(5000);
  if (check_type() == 1) {
    camAngle = 90;
    return camAngle;          //at 45 degree right garbage is found
  }
  return camAngle;            //nothing is found
}

int check_type() {
  if (digitalRead(glass) == HIGH) {
    //rotate basket servo
    return 1;
  }
  else if (digitalRead(metal) == HIGH) {
    //rotate basket servo
    return 1;
  }
  else if (digitalRead(paper) == HIGH) {
    //rotate basket servo
    return 1;
  }
  else if (digitalRead(plastic) == HIGH) {
    //rotate basket servo
    return 1;
  }
  else {
    return 0;
  }

}

void reset_relay() {
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  Serial.println("All Relays are reset");
}
