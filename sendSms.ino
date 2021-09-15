#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(8,9); //A6 Tx & Rx is connected to Arduino #9 & #8

void setup()                 
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and A6
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
   mySerial.println("AT+CNMI=1,2,0,0,0"); // Configuring TEXT mode
  updateSerial();
  //mySerial.println("AT+CMGS=\"655765982\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  //updateSerial();
 
//  mySerial.print("Yoooooooooooo"); //text content
//  updateSerial();
  mySerial.write(26);
}

void loop()
{
   mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
