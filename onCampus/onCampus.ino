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

int flagPin = 7;      //  pin for the shape-memory alloy element
int PMW = 99;         //  value for limiting the power going into the shape-memory alloy
                      //  min 0 max 255

//monitor Adafruit IO Feeds
AdafruitIO_Feed *arrived = io.feed("arrived"); 
AdafruitIO_Feed *gone = io.feed.("gone");

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
  arrived->onMessage(theyArrived);
  gone->onMessage(theyGone);
  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // confirm connection
  Serial.println();
  Serial.println(io.statusText());

  // the information element is off by default
  digitialWrite(flagPin, LOW);
}

void loop() {
  //io.run() is required at the top of the loop
  io.run();
}

void theyArrived(AdafruitIO_Data *data){
  digitalWrite(flagPin, PMW);
}

void theyGone(AdafruitIO_Data *data){
  digitalWrite(flagPin, LOW);
}
