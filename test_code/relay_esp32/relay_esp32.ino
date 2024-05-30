const int PIN_RELAY_1 = 18; // Chân GPIO27 của ESP32 kết nối đến chân IN1 của mô-đun relay
const int PIN_RELAY_2 = 5; // Chân GPIO26 của ESP32 kết nối đến chân IN2 của mô-đun relay
const int PIN_RELAY_3 = 19; // Chân GPIO25 của ESP32 kết nối đến chân IN3 của mô-đun relay
const int PIN_RELAY_4 = 1; // Chân GPIO33 của ESP32 kết nối đến chân IN4 của mô-đun relay

// Hàm setup() chạy một lần khi bạn nhấn nút reset hoặc cung cấp nguồn cho board
void setup() {
  Serial.begin(9600);

  // Khởi tạo chân GPIO là đầu ra.
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  pinMode(PIN_RELAY_3, OUTPUT);
  pinMode(PIN_RELAY_4, OUTPUT);
}

// Hàm loop() chạy liên tục
void loop() {
  Serial.println("Bật tất cả");
  digitalWrite(PIN_RELAY_1, HIGH);
  digitalWrite(PIN_RELAY_2, HIGH);
  digitalWrite(PIN_RELAY_3, HIGH);
  digitalWrite(PIN_RELAY_4, HIGH);
  delay(1000);

  Serial.println("Tắt tất cả");
  digitalWrite(PIN_RELAY_1, LOW);
  digitalWrite(PIN_RELAY_2, LOW);
  digitalWrite(PIN_RELAY_3, LOW);
  digitalWrite(PIN_RELAY_4, LOW);
  delay(1000);
} 


