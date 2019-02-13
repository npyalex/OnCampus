/*
  Are you here?
  Ambient information systems exploration
  
  for Body-centric Technologies
  profs Lee Jones & Kate Hartman
  by Nick Alexander
  OCADU Digital Futures MDes 2019

  Based on DIY Analog Input
  http://www.arduino.cc/en/Tutorial/AnalogInput
  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe
  and
  Adafruit IO Digital Input Example
  https://learn.adafruit.com/adafruit-io-basics-digital-input
*/

#include "config.h" // change local wifi settings in the config.h tab

int flagPin = 12;      //  pin for the shape-memory alloy element
int PMW = 99;         //  value for limiting the power going into the shape-memory alloy
                      //  min 0 max 255
                      //  change this depending on the size of your SMAs

//monitor Adafruit IO Feeds
AdafruitIO_Group *group = io.group("OnCampus"); 

void setup() {
  // any pin setup happens here
  pinMode(flagPin, OUTPUT);
  // start the serial connection
  // note that it's 115200
  Serial.begin(115200);
  // wait for the connection to Adafruit IO  
  while(!Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  //run the function whenever a message is recieved from each feed
  group->onMessage("OnCampus.arrived", theyArrived);
  group->onMessage("OnCampus.gone", theyGone);
  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // confirm connection
  Serial.println();
  Serial.println(io.statusText());

  group->get();
}

void loop() {
  //io.run() is required at the top of the loop
  io.run();
}

void theyArrived(AdafruitIO_Data *data){
  //when the Arrived data is received from Adafruit IO
  //control the voltage being sent to the shape-memory alloy via transistor.
  //Adjust the strength of the pulse-width modulation above
//  int go = data->toInt();
//  if (go==1){
  analogWrite(flagPin, PMW);
//  }
}

void theyGone(AdafruitIO_Data *data){
  //when the Gone data is received from Adafruit IO
  //cut the flow of power and turn off the shape-memory alloy
//  int go = data->toInt();
//  if (go==1){
  analogWrite(flagPin,0);
//  }
}
