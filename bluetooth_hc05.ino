// Basic Bluetooth sketch HC-05_AT_MODE_01
// Communicate with a HC-05 using the serial monitor
//
// The HC-05 defaults to communication mode when first powered on you will need to manually enter AT mode
// The default baud rate for AT mode is 38400
// See www.martyncurrey.com for details
//
//BLUETOOTH CHIP 1 with heatshrink and blue light 
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// 
 
char c = ' ';
 
void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
 
    // HC-05 default serial speed for AT mode is 38400
    BTserial.begin(9600);  
}
 
void loop()
{
 
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
      Serial.println("BT serial available");
        c = BTserial.read();
        Serial.write(c);
        delay(10);
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
      Serial.println("Serial available");
        c =  Serial.read();
        BTserial.write(c);  
        delay(10);
    }
 
}
