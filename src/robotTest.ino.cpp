# 1 "/var/folders/n8/6k37mj4x3l53s9b9nyrkbr_m0000gn/T/tmpcB0sKo"
#include <Arduino.h>
# 1 "/Users/woojen/Documents/PlatformIO/Projects/171219-095036-uno/src/robotTest.ino"
#include <IRremoteInt.h>
#include <IRremote.h>
#include <Arduino.h>



#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>




#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);







boolean isAutoPilot = false;

int ran;



int echo = A3;
int trig =A2;




const int honk = 4;




boolean playSiren = false;
const int blueLed = 7;
const int greenLed = 6;
const int redLed = 5;





const int leftMotor = 12;
const int leftBreak = 9;
 const int spinLeft = 3;


const int rightMotor = 13;
const int rightBreak = 8;
 const int spinRight = 11;




 long duration;
 int distance;





int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;





const int FORWARD = 0xE0E006F9;
const int BACKWARD = 0xE0E08679;
const int LEFT = 0xE0E0A659;
const int RIGHT =0xE0E046B9;
const int STOP= 0xE0E016E9;
const int COLORFLOW =0xE0E09E61;
const int LEDPOWER = 0xE0E040BF;
const int HONK = 0xE0E0F807;
const int SPEED_UP= 0xE0E0E01F;
const int SPEED_DOWN= 0xE0E0D02F;
const int AUTOPILOT = 0xDAEA83EC;
const int MANUAL = 0xE0E020DF;
void setup();
void loop();
void GoForward();
void GoBackward();
void TurnLeft();
void TurnRight();
void Stop();
void doHonk();
void distanceCheck();
void ChannelAFullSpeed(boolean direction);
void ChannelBFullSpeed(boolean direction);
void autoPilot();
void testRemote();
void inputListener();
void cGreen();
void cRed();
void cLightBlue();
void cLightGreen();
void cOff();
void cSiren();
void colorFlow();
void CalcDistance();
void QuitAutoPilot();
void SetAutoPilot();
#line 90 "/Users/woojen/Documents/PlatformIO/Projects/171219-095036-uno/src/robotTest.ino"
void setup() {

  display.begin(SSD1306_SWITCHCAPVCC,0x3D);
# 105 "/Users/woojen/Documents/PlatformIO/Projects/171219-095036-uno/src/robotTest.ino"
 randomSeed(analogRead(0));



pinMode(trig, OUTPUT);
pinMode(echo, INPUT);





  pinMode(honk,OUTPUT);




  Serial.begin(9600);
  irrecv.enableIRIn();




  pinMode(A0,OUTPUT);






    pinMode(12, OUTPUT);
    pinMode(9, OUTPUT);


    pinMode(13, OUTPUT);
    pinMode(8, OUTPUT);




    pinMode(redLed,OUTPUT);
    pinMode(greenLed,OUTPUT);
    pinMode(blueLed,OUTPUT);


}

void loop()

{







display.display();

delay(2000);
# 208 "/Users/woojen/Documents/PlatformIO/Projects/171219-095036-uno/src/robotTest.ino"
}

void GoForward(){

    ChannelAFullSpeed(true);
    ChannelBFullSpeed(true);
    cGreen();

}

void GoBackward(){

    ChannelAFullSpeed(false);
    ChannelBFullSpeed(false);
    cRed();

}




void TurnLeft(){

    GoForward();
    analogWrite(spinLeft,0);
    cLightBlue();

}

void TurnRight(){

    GoForward();
    analogWrite(spinRight,0);
    cLightGreen();

}

void Stop(){


analogWrite(spinLeft,0);
analogWrite(spinRight,0);

}

void doHonk(){

digitalWrite(honk,HIGH);

delay(500);

digitalWrite(honk,LOW);







}





void distanceCheck(){

  if(distance <= 5){



    delay(200);
    Stop();
  }


}






void ChannelAFullSpeed(boolean direction){



    if (direction){
        digitalWrite(leftMotor,HIGH);}


    else { digitalWrite(leftMotor,LOW);}


    digitalWrite(leftBreak, LOW);
    analogWrite(spinLeft, 255);

}
void ChannelBFullSpeed(boolean direction){

    if (direction){
        digitalWrite(rightMotor,HIGH);}


    else { digitalWrite(rightMotor,LOW);}
    digitalWrite(rightBreak, LOW);
    analogWrite(spinRight, 255);

}


void autoPilot(){



  ran = random(1, 2);

GoForward();

CalcDistance();

if(distance <4){

  GoBackward();
  delay(500);
  GoForward();
}


  if (distance <= 10){

      if(ran == 1){
        TurnLeft();
        delay(1000);
      }

      if(ran == 2){
        TurnRight();
          delay(1000);

      }


  }
}





void testRemote(){


  if (irrecv.decode(&results))
  {
   Serial.println(results.value, HEX);
   irrecv.resume();
  }

  }



void inputListener() {



    if (irrecv.decode(&results)) {



      Serial.println(results.value, HEX);

      int curr = (results.value);
      Serial.println(curr);



     switch (curr) {
       case FORWARD:
            GoForward();
              break;
        case STOP:
            Stop();
            cOff();
            break;

        case LEFT:
            TurnLeft();
            break;

       case RIGHT:
            TurnRight();
            break;

       case BACKWARD:
           GoBackward();
            break;

       case COLORFLOW:
            playSiren = true;
            break;

       case LEDPOWER:
            cOff();
            break;

       case HONK:
            doHonk();
            break;

       case AUTOPILOT:
            SetAutoPilot();
            break;

       case MANUAL:
            QuitAutoPilot();
            break;


     }



      irrecv.resume();

          }

 }





 void cBlue(){
   digitalWrite (redLed, LOW);
   digitalWrite (greenLed, LOW);
   digitalWrite (blueLed, LOW);


digitalWrite (redLed, LOW);
digitalWrite (greenLed, LOW);
digitalWrite (blueLed, HIGH);

          }

void cGreen(){
       digitalWrite (redLed, LOW);
       digitalWrite (greenLed, LOW);
       digitalWrite (blueLed, LOW);


digitalWrite (redLed, LOW);
digitalWrite (greenLed, HIGH);
digitalWrite (blueLed, LOW);

          }

void cRed(){
                     digitalWrite (redLed, LOW);
                     digitalWrite (greenLed, LOW);
                     digitalWrite (blueLed, LOW);


digitalWrite (redLed, HIGH);
digitalWrite (greenLed, LOW);
digitalWrite (blueLed, LOW);

          }


void cLightBlue(){

  digitalWrite (redLed, LOW);
  digitalWrite (greenLed, LOW);
  digitalWrite (blueLed, LOW);




digitalWrite (redLed, HIGH);
digitalWrite (greenLed, LOW);
digitalWrite (blueLed, HIGH);

          }



void cLightGreen(){

  digitalWrite (redLed, LOW);
  digitalWrite (greenLed, LOW);
  digitalWrite (blueLed, LOW);




digitalWrite (redLed, HIGH);
digitalWrite (greenLed, HIGH);
digitalWrite (blueLed, HIGH);

}




void cOff(){


playSiren = false;


digitalWrite (redLed, LOW);
digitalWrite (greenLed, LOW);
digitalWrite (blueLed, LOW);

}

void cSiren(){

  digitalWrite(blueLed,HIGH);
  digitalWrite(redLed,LOW);
  digitalWrite(4,HIGH);
  delay(75);
  digitalWrite(blueLed,LOW);
  digitalWrite(redLed,HIGH);
  delay(75);
  digitalWrite(4,LOW);
  delay(75);


}



void colorFlow(){
cLightBlue();
delay(500);
cGreen();
delay(300);
cRed();
delay(400);


cLightGreen();
delay(200);}

void CalcDistance(){




  digitalWrite(trig, LOW);
  delayMicroseconds(2);


  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance= duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);

}

void QuitAutoPilot(){

  isAutoPilot = false;
  Stop();
}

void SetAutoPilot(){

  isAutoPilot = true;
  Stop();
}