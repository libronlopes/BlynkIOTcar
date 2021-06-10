/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App project setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "iRCRDJOPofRPWNEXwWeWeNeWA*****";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID_NAME";
char pass[] = "WIFI_PASS";

#include<AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ); 
AF_DCMotor motor4(4, MOTOR12_1KHZ);

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(A0, A1); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

BLYNK_WRITE(V1) 
{
int x = param[0].asInt();
int y = param[1].asInt();
// Do something with x and y

if(y>220)
{
  forward();
  Blynk.virtualWrite(V4,"Forward");
}
else if(y<35)
{
  backward();
  Blynk.virtualWrite(V4,"backward");
}
else if(x>220)
{
right();
Blynk.virtualWrite(V4,"right");
}
else if(x<35)
{
left();
Blynk.virtualWrite(V4,"left");
}
else
Stop();
}
void loop()
{
Blynk.run();
timer.run();
}
void forward()
{
motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD);
}

void backward()
{
motor1.setSpeed(255); 
motor1.run(BACKWARD); 
motor2.setSpeed(255); 
motor2.run(BACKWARD); 
motor3.setSpeed(255); 
motor3.run(BACKWARD); 
motor4.setSpeed(255); 
motor4.run(BACKWARD); 
}

void left()
{
motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(255);
motor3.run(BACKWARD); 
motor4.setSpeed(255);
motor4.run(BACKWARD); 



}

void right()
{
motor1.setSpeed(255);
motor1.run(BACKWARD); 
motor2.setSpeed(255);
motor2.run(BACKWARD); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD); 


}

void Stop()
{
motor1.setSpeed(0);
motor1.run(RELEASE); 
motor2.setSpeed(0);
motor2.run(RELEASE); 
motor3.setSpeed(0);
motor3.run(RELEASE);
motor4.setSpeed(0);
motor4.run(RELEASE); 
}
