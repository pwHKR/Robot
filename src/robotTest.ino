#include <IRremoteInt.h>
#include <IRremote.h>
#include <Arduino.h>


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




void setup() {



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

 //testRemote();

 inputListener();

 if(playSiren){

   cSiren();
 }




}

void GoForward(){

    ChannelAFullSpeed(true);
    ChannelBFullSpeed(true);








}

void GoBackward(){

    ChannelAFullSpeed(false);
    ChannelBFullSpeed(false);

}




void TurnLeft(){

    GoForward();
    analogWrite(spinLeft,0);



}

void TurnRight(){

    GoForward();
    analogWrite(spinRight,0);



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
            cLightBlue();
              break;
        case STOP:
            Stop();
            cOff();
            break;

        case LEFT:
            TurnLeft();
            cRed();
            break;

       case RIGHT:
            TurnRight();
            cGreen();
            break;

       case BACKWARD:
           GoBackward();
           cLightGreen();
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
delay(200);;

}
