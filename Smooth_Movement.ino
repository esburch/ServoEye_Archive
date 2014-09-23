/* 
 * Smooth servo rotation using a sinus square function.
 * more infos: http://letsmakerobots.com/node/31697
 * created by NilsB 
 */

#include <MsTimer2.h>
#include <Servo.h> 

const int timerInMillies = 60;
const int countSinusSquareLookupTableEntries = 10;
const int sinusSquareLookupTable[] = {
  49,60,71,82,93,
  105,116,126,136,145
};

int currentValueIndex = 0;
const int movmentIndicatorPin = 13;

Servo xServo;
Servo yServo;

/*
* This is the function that gets called periodically.
*/
void move()
{
  moveServoTo(angle());

  indicateMovement();
  
  incrementOrStop();
}

void moveServoTo(int angle){
  Serial.println(angle);
  xServo.write(angle);
  yServo.write(angle); 
}

int angle(){
  return sinusSquareLookupTable[currentValueIndex];
}

void indicateMovement()
{
  static boolean output = HIGH;
  
  digitalWrite(movmentIndicatorPin, output);
  output = !output;
}

void incrementOrStop(){
  currentValueIndex++;
  if(currentValueIndex == countSinusSquareLookupTableEntries - 1){
    stopMove();
  }
}

void stopMove(){
  MsTimer2::stop();
  xServo.detach();
  yServo.detach();
}

void setupMovementIndicator(){
  Serial.begin(9600);
  pinMode(movmentIndicatorPin, OUTPUT);
}

void setupTimer2(){
  MsTimer2::set(timerInMillies, move);
  MsTimer2::start();
}

void setupServo(){  
  xServo.attach(9);
  yServo.attach(10);
  xServo.write(0);
  yServo.write(0);
}

void setup(){
  setupMovementIndicator();
  setupServo();  
  setupTimer2();
}

/*
* The loop method is empty and can be used to
* read sensor data and feed the behaviors.
*/
void loop(){;}
