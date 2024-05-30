//++++++++++++++++++++++++++++++++++++++ Các thư viện+++++++++++++++++++++++++++++++++++++++++++++++

#include <Wire.h> // Thư viện để điều khiển giao tiếp I2C                                          +
#include <SPI.h> // Thư viện để điều khiển giao tiếp SPI                                           +
#include <Adafruit_Sensor.h> // Thư viện hỗ trợ cảm biến từ Adafruit                               +
#include <Adafruit_BME280.h> // Thư viện để tương tác với cảm biến BME280                          +
#include <Adafruit_GFX.h> // Thư viện đồ họa cơ bản từ Adafruit                                    +
#include <Adafruit_SSD1306.h> // Thư viện để điều khiển màn hình OLED sử dụng driver SSD1306       +
//++++++++++++++++++++++++++++++++++++++ Các thư viện+++++++++++++++++++++++++++++++++++++++++++++++

//--------------------------------------------------------------OLED_BME280---------------------------------------------------------------
/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
unsigned long delayTime;

void loop_oled()
{
  display.setCursor(0,0);
  display.clearDisplay();
  
  Serial.print("Temperature = "); Serial.print(bme.readTemperature()); Serial.println(" *C");
  display.print("Temperature: "); display.print(bme.readTemperature()); display.println(" *C");

  Serial.print("Pressure = "); Serial.print(bme.readPressure() / 100.0F); Serial.println(" hPa");
  display.print("Pressure: "); display.print(bme.readPressure() / 100.0F); display.println(" hPa");

  Serial.print("Humidity = "); Serial.print(bme.readHumidity()); Serial.println(" %");
  display.print("Humidity: "); display.print(bme.readHumidity()); display.println(" %");

  Serial.print("altitude = "); Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); Serial.println(" ft");
  display.print("altitude: "); display.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); display.println(" ft");

  Serial.println();
  display.display();
  delay(1000);
}

void setup_oled_bm280()
{
  Serial.println(F("BME280 test"));
   
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.1);
  display.setTextColor(WHITE);
  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}


//----------------------------------------------------------------OLED_BME280----------------------------------------------------

void setup() {
  Serial.begin(9600);
  
  setup_oled_bm280();  
  
}

void loop() {  
  loop_oled(); 
  
}