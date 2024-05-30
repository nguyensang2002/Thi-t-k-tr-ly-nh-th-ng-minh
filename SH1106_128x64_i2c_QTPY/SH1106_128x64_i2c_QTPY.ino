
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

float temperature, humidity, pressure, altitude;



/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup()   {

  Serial.begin(9600);
 
  delay(250); // Đợi màn hình OLED khởi động

  bme.begin(0x76);
  display.begin(i2c_Address, true); // Khởi động màn hình OLED với địa chỉ I2C đã xác định
  display.display();
  delay(2000);
  display.clearDisplay(); // Xóa màn hình
  
 
 }

  
 
void loop() {

  // handle_OnConnect();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  
}


// void handle_OnConnect() {
//   temperature = bme.readTemperature();
//   humidity = bme.readHumidity();
//   pressure = bme.readPressure() / 100.0F;
//   altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

//   if (isnan(temperature) || isnan(humidity) ||isnan(pressure) || isnan(altitude)) {
//     Serial.println("Failed to read from BME280 sensor!");
//   }
//   // clear display
//   display.clearDisplay();

//   // display temperature
//   display.setTextSize(1);
//   display.setCursor(0,0);
//   display.print("Temperature: ");
//   display.setTextSize(1);
//   display.setCursor(0,10);
//   display.print(temperature);
//   display.print(" ");
//   display.setTextSize(1);
//   display.cp437(true);
//   display.write(167);
//   display.setTextSize(1);
//   display.print("C");
  
//   // display humidity
//   display.setTextSize(1);
//   display.setCursor(0, 35);
//   display.print("Humidity: ");
//   display.setTextSize(1);
//   display.setCursor(0, 45);
//   display.print(humidity);
//   display.print(" %"); 
  
//   display.display(); 
  
// }


