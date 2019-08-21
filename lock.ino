#define BLYNK_PRINT Serial
#include <Servo.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX
#define ESP8266_BAUD 9600
ESP8266 wifi(&Serial);

#define lockedState 0
#define unlockedState 1200

//WiFi Connection
char    ssid[32]        = "EE-IOT-Platform-02"; 
char    pass[32]        = "dUQQE?&W44x7";
char    auth[256]  = "63db023049e54d099f544e216df2d938";   // For FYDE projects only
bool    locked = false;

Servo servo;

//===== Servo Sweep Switch Function =====
BLYNK_WRITE(V0) // Switch Widget
{
  if (param.asInt() == 0) {     //UNLOCK
    servo.attach(9);
    servo.write(unlockedState);
    Blynk.notify("Door has been unlocked!");
    locked  = false;
    delay(1500);
  } else if(!locked) {
    servo.attach(9);
    servo.write(lockedState);
    Blynk.notify("Door has been locked!");
    locked = true;
    delay(1500);
    servo.detach();
  } else 
    servo.detach();
} 


void setup() {
  // Debug console
  Serial.begin(9600);
  delay(10);
  // Set ESP8266 baud rate
  Serial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
}

void loop() {
  Blynk.run();
}





