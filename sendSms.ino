#include <SoftwareSerial.h>

//Create software serial object to communicate with the gsm modules
SoftwareSerial mySerial(10,11); // Tx & Rx is connected to Arduino #10 & #11

String message = "Example of message to be sent";
String phone_number = "XXXXXXXXXX";

void setup()                 
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and gsm module
  mySerial.begin(9600);
  Serial.println("Waiting..."); // leave time to initialize the communication
  delay(1000);
  mySerial.println("AT"); //test if the communication is established between the Arduino and the gsm module
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
   mySerial.println("AT+CNMI=1,2,0,0,0"); // Configuring TEXT mode
  updateSerial();
}

void loop()
{
  sendSMS(message);
}

String sendSMS(String message){
  mySerial.println("AT+CMGS=\"phone_number\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(message); //text content
  updateSerial();
  mySerial.write(26);
}


//function to refresh the data displayed in the Serial monitor and routing into the communication port
void updateSerial()
{
  delay(500);
  while (Serial.available()) //while there is a value in the Serial monitor
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) //while there is a value received in the communication port
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
 
