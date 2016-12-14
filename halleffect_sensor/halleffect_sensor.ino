int sensorpin; 
byte sensorVal;
byte lastVal;
word samples; 
unsigned long lastSampleTime; 
byte samplePeriod;
word period;

void setup() {
  // put your setup code here, to run once:
sensorVal = 0; 
sensorpin = 4; 
samplePeriod = 10; 
samples = 0;
lastSampleTime = 0; 
pinMode(sensorpin, INPUT); 
Serial.begin(9600); 

}

void loop() {
   if ((millis() - lastSampleTime) >= samplePeriod) {
      lastSampleTime = millis();
      sensorVal = digitalRead(sensorpin);
      if (sensorVal != 1 && lastVal == 1) { //different as
        period = samples * samplePeriod;
        samples = 0;
        Serial.println(period);
      }
      else { 
        samples++;
      }
      lastVal = sensorVal;
    }
}
