#include <SPI.h>
#include <SD.h>
#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>

const int chipSelect = 10;
File dataFile, dataCSV;
unsigned long timetime;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  if (!SD.begin(chipSelect)) {
    Serial.println("Card faied, or not present");
     while(1);

  }
  
  dataFile = SD.open("data_new.txt", FILE_WRITE);
  dataFile.close();
  Serial.println("Card initialized");

}

void loop() {
  float x, y, z, j, k, l, f, g, h;

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) {
    IMU.readAcceleration(x, y, z);
    IMU.readGyroscope(j, k, l);
    IMU.readMagneticField(f, g, h);

    dataCSV = SD.open("data_new.csv", FILE_WRITE);
    dataFile = SD.open("data_new.txt", FILE_WRITE);
    String dataString = "";
    if (dataFile)
    {
      dataString += String(x) + '\t';
      dataString += String(y) + '\t';
      dataString += String(z) + '\t';
      dataString += String(j) + '\t';
      dataString += String(k) + '\t';
      dataString += String(l) + '\t';
      dataString += String(f) + '\t';
      dataString += String(g) + '\t';
      dataString += String(h) + '\t';
      dataCSV.println(dataString);
      dataFile.println(dataString);
      Serial.println(dataString);
    }

  }
  else
  {
    Serial.println("Unavailable info");
  }
  dataFile.close();
  dataCSV.close();
}
