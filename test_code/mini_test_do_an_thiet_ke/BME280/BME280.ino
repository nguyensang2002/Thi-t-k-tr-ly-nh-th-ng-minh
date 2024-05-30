#include <Wire.h>  // Thư viện cho giao tiếp I2C
#include <Adafruit_Sensor.h>  // Thư viện cho các cảm biến Adafruit
#include <Adafruit_BME280.h>  // Thư viện cho cảm biến BME280

#define SEALEVELPRESSURE_HPA (1013.25)  // Định nghĩa áp suất mực nước biển tiêu chuẩn (hPa)

Adafruit_BME280 bme;  // Khai báo đối tượng của cảm biến BME280

void setup() {
	Serial.begin(115200);  // Khởi động giao tiếp serial với baud rate 9600

	if (!bme.begin(0x76)) {  // Khởi động cảm biến BME280 với địa chỉ I2C 0x76
		Serial.println("Could not find a valid BME280 sensor, check wiring!");  // In ra thông báo lỗi nếu không tìm thấy cảm biến
		while (1) delay(1000) ;  // Lặp vô hạn nếu không tìm thấy cảm biến
	}
}

void loop() {
	Serial.print("Temperature = ");  // In ra dòng "Temperature = "
	Serial.print(bme.readTemperature());  // Đọc và in ra nhiệt độ từ cảm biến BME280
	Serial.println("*C");  // In ra đơn vị đo nhiệt độ (độ C)

	Serial.print("Pressure = ");  // In ra dòng "Pressure = "
	Serial.print(bme.readPressure() / 100.0F);  // Đọc và in ra áp suất từ cảm biến BME280 và chuyển đổi sang hPa
	Serial.println("hPa");  // In ra đơn vị đo áp suất (hPa)

	Serial.print("Approx. Altitude = ");  // In ra dòng "Approx. Altitude = "
	Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));  // Đọc và in ra độ cao xấp xỉ từ cảm biến BME280
	Serial.println("m");  // In ra đơn vị đo độ cao (m)

	Serial.print("Humidity = ");  // In ra dòng "Humidity = "
	Serial.print(bme.readHumidity());  // Đọc và in ra độ ẩm từ cảm biến BME280
	Serial.println("%");  // In ra đơn vị đo độ ẩm (%)

	Serial.println();  // In ra một dòng trống
	delay(1000);  // Chờ 1 giây trước khi lặp lại quá trình
}
