#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30

#define TFT_CS         7
#define TFT_RST        40
#define TFT_DC         39

#define TFT_MOSI 35  // Data out
#define TFT_SCLK 36  // Clock out

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
SCD30 airSensor;

void setup()
{
  // I2C power management
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  // TFT Backlight on
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  
  delay (200);
  
  Serial.begin(115200);
  Serial.println("SCD30 Example");
  Wire.begin();


  if (airSensor.begin() == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  //The SCD30 has data ready every two seconds

  //initializer for 1.14" 240x135 TFT:
  tft.init(135, 240);           // Init ST7789 240x135
  
  //tft.setSPISpeed(40000000);
  tft.fillScreen(ST77XX_BLACK);
  
  tft.setTextWrap(false);
  tft.setRotation(3);
}

void loop()
{
  if (airSensor.dataAvailable())
  {
    Serial.print("co2(ppm):");
    Serial.print(airSensor.getCO2());

    Serial.print(" temp(C):");
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(" humidity(%):");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();
    

    if (airSensor.getCO2() < 800){
      tft.fillScreen(ST77XX_GREEN);
    } else
       if (airSensor.getCO2() < 1000){
         tft.fillScreen(ST77XX_YELLOW);
       } else
          {
            tft.fillScreen(ST77XX_RED);
          }

    tft.setTextColor(ST77XX_WHITE);
    
    tft.setCursor(60, 50);  
    tft.setTextSize(5);
    tft.println(airSensor.getCO2());

    tft.setCursor(20, 50);  
    tft.setTextSize(2);
    tft.println("ppm");

  }
  else
    Serial.println("Waiting for new data");

  delay(500);
}
