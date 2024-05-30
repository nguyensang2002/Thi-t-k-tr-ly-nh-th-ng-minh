
// ID Mẫu, Tên Thiết bị và Mã Xác thực được cung cấp bởi Blynk Cloud
// Xem tab Thông tin Thiết bị hoặc cài đặt Mẫu
#define BLYNK_TEMPLATE_ID "TMPL69ZwsxwdD"
#define BLYNK_TEMPLATE_NAME "ESP32 Automation"
#define BLYNK_AUTH_TOKEN "WFAehKOsaXP1FgseY2lAw3YUNECjzzvS"


// Bỏ comment dòng này để tắt in ra và tiết kiệm không gian
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h> // Thư viện hỗ trợ cảm biến từ Adafruit                               +
#include <Adafruit_BME280.h> // Thư viện để tương tác với cảm biến BME280   
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


char auth[] = BLYNK_AUTH_TOKEN;

// Tên và mật khẩu WiFi của bạn.
// Đặt mật khẩu thành "" cho các mạng mở.
char ssid[] = "Tao";
char pass[] = "88884444";


/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
unsigned long delayTime;

bool fetch_blynk_state = true;  //true or false

BlynkTimer timer;

#define wifiLed   15 

#define button1_pin 27
#define button2_pin 14
#define button3_pin 12
#define button4_pin 13

#define relay1_pin 18
#define relay2_pin 17
#define relay3_pin 5
#define relay4_pin 19

int   wifiFlag = 0;
int relay1_state = 0; // giá trị ban đầu là 0. Biến này sẽ lưu trữ trạng thái của relay 1: 0 cho trạng thái tắt và 1 (hoặc bất kỳ giá trị khác 0) cho trạng thái bật.
int relay2_state = 0;
int relay3_state = 0;
int relay4_state = 0;
float temperature1 = 0;
float humidity1   = 0;
float pressure1 = 0;
float altitude1   = 0;

// Đổi các chân ảo tương ứng với các phòng
#define button1_vpin    V1
#define button2_vpin    V2
#define button3_vpin    V3 
#define button4_vpin    V4
#define VPIN_TEMPERATURE V6
#define VPIN_HUMIDITY    V7
#define VPIN_Pressure    V8
#define VPIN_Altitude    V9

void setup_oled_bm280();

// Hàm này được gọi mỗi khi thiết bị kết nối với Blynk Cloud
// Yêu cầu trạng thái mới nhất từ máy chủ
BLYNK_CONNECTED() {
	if (fetch_blynk_state){
      Blynk.syncVirtual(button1_vpin);
      Blynk.syncVirtual(button2_vpin);
      Blynk.syncVirtual(button3_vpin);
      Blynk.syncVirtual(button4_vpin);
	}
  
  Blynk.syncVirtual(VPIN_TEMPERATURE);
  Blynk.syncVirtual(VPIN_HUMIDITY);
  Blynk.syncVirtual(VPIN_Pressure);
  Blynk.syncVirtual(VPIN_Altitude);
}

void checkBlynkStatus() { // called every 2 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    wifiFlag = 1;
    Serial.println("Blynk Not Connected");
    digitalWrite(wifiLed, LOW);
  }
  if (isconnected == true) {
    wifiFlag = 0;
    
    digitalWrite(wifiLed, HIGH);
    //Serial.println("Blynk Connected");
  }
}


// Hàm này được gọi mỗi khi trạng thái của Chân ảo thay đổi
// tức là khi cài đặt từ App Blynk hoặc Trang tổ chức Blynk Web
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}

BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}

BLYNK_WRITE(button3_vpin) {
  relay3_state = param.asInt();
  digitalWrite(relay3_pin, relay3_state);
}

BLYNK_WRITE(button4_vpin) {
  relay4_state = param.asInt();
  digitalWrite(relay4_pin, relay4_state);
}

void readSensor(){
  float h = bme.readHumidity();
  float t = bme.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  float p = bme.readPressure();
  float a = bme.readAltitude(SEALEVELPRESSURE_HPA);
  
  humidity1 = h;
  temperature1 = t;
  pressure1 = p;
  altitude1 = a;
   // Serial.println(temperature1);
   // Serial.println(humidity1);

   // In dữ liệu áp suất ra Serial Monitor
  Serial.print("Pressure from BME280: ");
  Serial.println(pressure1);
  
}

void sendSensor()
{
  readSensor();
  // Bạn có thể gửi bất kỳ giá trị nào vào bất kỳ lúc nào.
   // Vui lòng không gửi nhiều hơn 10 giá trị mỗi giây.
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity1);
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature1);
  Blynk.virtualWrite(VPIN_Pressure, pressure1);
  Blynk.virtualWrite(VPIN_Altitude, altitude1);

  
}

void setup() {
  // Bảng ghi chú Debug
  Serial.begin(115200);
  
  setup_oled_bm280(); 
  digitalWrite(wifiLed, LOW);
  
  
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);
  
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay4_pin, OUTPUT);
  
  digitalWrite(relay1_pin, HIGH);
  digitalWrite(relay2_pin, HIGH);
  digitalWrite(relay3_pin, HIGH);
  digitalWrite(relay4_pin, HIGH);
  
  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
  timer.setInterval(1000L, sendSensor); // Sending Sensor Data to Blynk Cloud every 1 second
  Blynk.config(auth);
  delay(1000);
}

void loop() {
  Blynk.run();
  timer.run();
  
  loop_oled();
  
  listen_push_buttons();
}

void loop_oled() {
    // Hàm này sẽ được gọi liên tục để đọc dữ liệu từ cảm biến BME280 và hiển thị lên màn hình OLED

    display.clearDisplay(); // Xóa màn hình để chuẩn bị vẽ dữ liệu mới

    float temperature = bme.readTemperature(); // Đọc nhiệt độ từ cảm biến BME280
    float pressure = bme.readPressure() / 100.0F; // Đọc áp suất từ cảm biến BME280 và chuyển đổi sang hPa
    float humidity = bme.readHumidity(); // Đọc độ ẩm từ cảm biến BME280
    float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); // Đọc độ cao từ cảm biến BME280 dựa trên áp suất biển

    // In các giá trị nhiệt độ, áp suất, độ ẩm và độ cao ra Serial Monitor
    Serial.print("Temperature = "); Serial.print(temperature); Serial.println("*C");
    Serial.print("Pressure = "); Serial.print(pressure); Serial.println("hPa");
    Serial.print("Humidity = "); Serial.print(humidity); Serial.println("%");
    Serial.print("Altitude = "); Serial.print(altitude); Serial.println("ft");

    // Hiển thị các giá trị nhiệt độ, áp suất, độ ẩm và độ cao lên màn hình OLED
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.print("Temperature: "); display.print(temperature); display.println("*C");
    display.print("Pressure: "); display.print(pressure); display.println("hPa");
    display.print("Humidity: "); display.print(humidity); display.println("%");
    display.print("Altitude: "); display.print(altitude); display.println("ft");

    display.display(); // Hiển thị dữ liệu đã vẽ lên màn hình
    delay(1000); // Chờ 1 giây trước khi lặp lại
}

void setup_oled_bm280()
{
  Serial.println(F("BME280 test"));
   
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.

  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
 //display.setContrast (0); // dim display
 
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, SH110X_WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();
  
  
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

void listen_push_buttons() {
  if(digitalRead(button1_pin) == LOW) {
    delay(200);
    control_relay(1);
    Blynk.virtualWrite(button1_vpin, relay1_state); // Cập nhật trạng thái nút
  }
  else if (digitalRead(button2_pin) == LOW) {
    delay(200);
    control_relay(2);
    Blynk.virtualWrite(button2_vpin, relay2_state); // Cập nhật trạng thái nút
  }
  else if (digitalRead(button3_pin) == LOW) {
    delay(200);
    control_relay(3);
    Blynk.virtualWrite(button3_vpin, relay3_state); // Cập nhật trạng thái nút
  }
  else if (digitalRead(button4_pin) == LOW) {
    delay(200);
    control_relay(4);
    Blynk.virtualWrite(button4_vpin, relay4_state); // Cập nhật trạng thái nút
  }
}

void control_relay(int relay) {
  if(relay == 1) {
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Trạng thái Relay1 = ");
    Serial.println(relay1_state);
    delay(50);
  }
  else if(relay == 2) {
    relay2_state = !relay2_state;
    digitalWrite(relay2_pin, relay2_state);
    delay(50);
  }
  else if(relay == 3) {
    relay3_state = !relay3_state;
    digitalWrite(relay3_pin, relay3_state);
    delay(50);
  }
  else if(relay == 4) {
    relay4_state = !relay4_state;
    digitalWrite(relay4_pin, relay4_state);
    delay(50);
  }
}
