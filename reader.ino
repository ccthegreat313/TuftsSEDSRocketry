 #include <SPI.h>
#include <SD.h> 
#include <Arduino_LSM9DS1.h>
#include <ArduinoBLE.h>

const int chipSelect = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial)
  {
    ;
  }
  if(!SD.begin(chipSelect))
  {
    Serial.println("Card failed");
    while(1);
  }
  File myFile; 
  myFile = SD.open("data_new.txt");
  if(myFile)
  {
    Serial.println("data_new.txt");
    while(myFile.available())
    {
      Serial.write(myFile.read());
      
    }
    myFile.close();
  }
  else
  {
    Serial.println("Didn't find file");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
