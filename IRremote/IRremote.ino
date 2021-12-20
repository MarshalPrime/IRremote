#include"IRremote/IRremote.h"
#include <IRremote.h>
#include <Servo.h>
#define Button_1 0xFD08F7
#define Button_2 0xFD8877
#define Button_3 0xFD48B7
#define Button_4 0xFD28D7
Servo servo;
const int RECV = 3;//sensor pin
int lastvalue;

// IR Receiver and Results
IRrecv irrecv(RECV);
decode_results results;


void setup(){
  Serial.begin(9600);// serial monitor 9600
  irrecv.enableIRIn();//enable
  pinMode(5,OUTPUT);// led pin
  pinMode(4,OUTPUT);// greenled
  pinMode(6,OUTPUT);// yellowled
  servo.attach(2);// servopin
  servo.write(0);// start point
  delay(2000);
}

void loop(){
  if (irrecv.decode(&results)){
    if (results.value==0xFFFFFFFF){
          results.value=lastvalue;
  }
    switch(results.value){

      case Button_1: digitalWrite(5,HIGH);
      servo.write(90);
      break;
      case Button_2:
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(6,LOW);
      servo.write(0);
      break;
      case Button_3: digitalWrite(4,HIGH);
      break;
      case Button_4: digitalWrite(6,HIGH);
      break;
    }
          Serial.println(results.value, HEX);// hex number
        irrecv.resume();
  }
}
