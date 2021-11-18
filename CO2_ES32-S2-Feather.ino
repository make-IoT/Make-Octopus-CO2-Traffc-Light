/*
  Reading CO2, humidity and temperature from the SCD30
  By: Nathan Seidle
  SparkFun Electronics
  Date: May 22nd, 2018
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/15112

  This example prints the current CO2 level, relative humidity, and temperature in C.

  Hardware Connections:
  Attach RedBoard to computer using a USB cable.
  Connect SCD30 to RedBoard using Qwiic cable.
  Open Serial Monitor at 115200 baud.
*/

#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30
#include <Adafruit_NeoPixel.h>

int CO2 = 0 ;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2,11,NEO_GRBW + NEO_KHZ800);

SCD30 airSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("SCD30 Example");

  pixels.begin();//-------------- Initialisierung Neopixel
  delay(1);
  pixels.show();
  pixels.setPixelColor(0,0,0,0,0); // alle aus
  pixels.setPixelColor(1,0,0,0,0);
  pixels.show(); 
  
  Wire.begin();

  if (airSensor.begin() == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  //The SCD30 has data ready every two seconds
}

void loop()
{
  if (airSensor.dataAvailable())
  {
    CO2 = airSensor.getCO2();
    Serial.print("co2(ppm):");
    Serial.print(CO2);

    Serial.print(" temp(C):");
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(" humidity(%):");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();

  if (( ( CO2 ) < ( 800 ) ))
  {
    pixels.setPixelColor(0,0,30,0,0);
    pixels.show();
    pixels.setPixelColor(1,0,30,0,0);
    pixels.show();
  }
  else
  {
    if (( ( CO2 ) < ( 1000 ) ))
    {
      pixels.setPixelColor(0,30,30,0,0);
      pixels.show();
      pixels.setPixelColor(1,30,30,0,0);
      pixels.show();
    }
    else
    {
      pixels.setPixelColor(0,40,0,0,0);
      pixels.show();
      pixels.setPixelColor(1,40,0,0,0);
      pixels.show();
    }
  }
    
  }
  else
    Serial.println("Waiting for new data");

  delay(500);
}
