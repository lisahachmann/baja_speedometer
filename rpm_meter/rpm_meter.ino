int sensorpin; 
byte sensorVal;
byte lastVal;
word samples; 
unsigned long lastSampleTime; 
byte samplePeriod;
word period;
char c = ' '; 
int rpm;
bool readyToSend; 

#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
 
void setup() {
  // put your setup code here, to run once:
rpm = 0; 
sensorVal = 0; 
sensorpin = 4; 
samplePeriod = 10; 
samples = 0;
lastSampleTime = 0; 
readyToSend = false;
pinMode(sensorpin, INPUT); 
Serial.begin(9600); 
BTserial.begin(38400);  
Serial.println("BTserial started at 38400");
}

void loop() {
   if ((millis() - lastSampleTime) >= samplePeriod) {
      lastSampleTime = millis();
      sensorVal = digitalRead(sensorpin);
      if (sensorVal != 1 && lastVal == 1) { //different as
        period = samples * samplePeriod;
        rpm = 60000/period; 
        c = char(rpm); 
        samples = 0;
        readyToSend = true;
        Serial.println(period);
      }
      else { 
        samples++;
      }
      lastVal = sensorVal;

     // Keep reading from HC-05 and send to Arduino Serial Monitor
//    if (BTserial.available())
//    {  
//        c = BTserial.read();
//        Serial.write(c);
//    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
//    if (Serial.available())
//    {
       // c =  Serial.read();
 
        // mirror the commands back to the serial monitor
        // makes it easy to follow the commands
        //Serial.write(c);   
        if (readyToSend) {
          BTserial.write(rpm);  
          Serial.println(rpm);
        }
        readyToSend = false;
    }
}
