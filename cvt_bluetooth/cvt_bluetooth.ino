/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
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
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  
  rpm = 0; 
  sensorVal = 0; 
  sensorpin = 4; 
  samplePeriod = 10; 
  samples = 0;
  lastSampleTime = 0; 
  readyToSend = false;
  pinMode(sensorpin, INPUT); 
  BTserial.begin(38400);  
  Serial.println("BTserial started at 9600");
  mlx.begin();  
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);
  if ((millis() - lastSampleTime) >= samplePeriod) {
      lastSampleTime = millis();
      sensorVal = digitalRead(sensorpin);
      if (sensorVal != 1 && lastVal == 1) { //different as
        period = samples * samplePeriod;
        rpm = 60000/period; 
        c = char(mlx.readObjectTempF()); 
        samples = 0;
        readyToSend = true;
        Serial.println(period);
      }
      else { 
        samples++;
      }
      lastVal = sensorVal;
      if (readyToSend) {
          BTserial.write(mlx.readObjectTempF());  
          Serial.println(mlx.readObjectTempF());
      }
       readyToSend = false;
    }
}

