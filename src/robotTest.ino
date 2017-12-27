#include <IRremoteInt.h>
#include <IRremote.h>
#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



// display object
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);





// Auto Pilot var

boolean isAutoPilot = false;

int ran;

// Distance messure - Ultra sound

int echo = A3;
int trig =A2;


// honk pin

const int honk = 4;


// led color pins

boolean playSiren = false;
const int blueLed = 7;
const int greenLed = 6;
const int redLed = 5;




// Motor var
const int leftMotor = 12; // Channel A
const int leftBreak = 9; // Channel A break
 const int spinLeft = 3; // 3


const int rightMotor = 13; // Channel B
const int rightBreak = 8; // Channel B break
 const int spinRight = 11;



 // Distance messure var
 long duration;
 int distance;



// IR var

int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN); //
decode_results results; //




// Hex values for button on the IR remote controll IR
const int FORWARD = 0xE0E006F9;
const int BACKWARD = 0xE0E08679;
const int LEFT = 0xE0E0A659;
const int RIGHT =0xE0E046B9;
const int STOP= 0xE0E016E9;
const int COLORFLOW =0xE0E09E61;
const int LEDPOWER = 0xE0E040BF;
const int HONK = 0xE0E0F807;
const int SPEED_UP= 0xE0E0E01F; // currently not used - vol+ on remote
const int SPEED_DOWN= 0xE0E0D02F; // currently not used vol- on remote
const int AUTOPILOT = 0xDAEA83EC;
const int MANUAL = 0xE0E020DF;



void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done



  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.





 randomSeed(analogRead(0)); // generate random number

// Distance messure Setup

pinMode(trig, OUTPUT); // Sets the trigPin as an Output
pinMode(echo, INPUT); // Sets the echoPin as an Input



  // honk Setup

  pinMode(honk,OUTPUT);


   // IR setup

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver // comment here


  // Horn Setup

  pinMode(A0,OUTPUT);



  // Motor Setup

    //Setup Channel A
    pinMode(12, OUTPUT); //Initiates Motor Channel A pin
    pinMode(9, OUTPUT); //Initiates Brake Channel A pin

    //Setup Channel B
    pinMode(13, OUTPUT); //Initiates Motor Channel B pin
    pinMode(8, OUTPUT);  //Initiates Brake Channel B pin


    // Color chaning led

    pinMode(redLed,OUTPUT);
    pinMode(greenLed,OUTPUT);
    pinMode(blueLed,OUTPUT);


}

void loop()

{





display.display();


delay(2000);





 //testRemote();

 /*

inputListener();

if(isAutoPilot == false){


 CalcDistance();



 distanceCheck();
}

else{autoPilot();}













 //If the boolean is true the police siren will start
 if(playSiren){

   cSiren();
 }
*/



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

  //  GoBackward();

    delay(200);
    Stop();
  }


}






void ChannelAFullSpeed(boolean direction){

    //Motor A forward @ full speed

    if (direction){
        digitalWrite(leftMotor,HIGH);}


    else { digitalWrite(leftMotor,LOW);}

    //Establishes forward direction of Channel A
    digitalWrite(leftBreak, LOW);   //Disengage the Brake for Channel A
    analogWrite(spinLeft, 255);   //Spins the motor on Channel A at full speed

}
void ChannelBFullSpeed(boolean direction){

    if (direction){
        digitalWrite(rightMotor,HIGH);}


    else { digitalWrite(rightMotor,LOW);}
    digitalWrite(rightBreak, LOW);   //Disengage the Brake for Channel A
    analogWrite(spinRight, 255);   //Spins the motor on Channel A at full speed

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
   irrecv.resume(); // Receive the next value
  } // Receive the next value

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



      irrecv.resume(); // Receive the next value

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

// This code is taken from the web. Look in to this more!

  // Clears the trigPin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
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
