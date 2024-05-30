//~~~~~~~~~~~~~~~~~~~Địa_chỉ_BLYNK_và_WIFI~~~~~~~~~~~~~~~~~~~~~~~~
/* Fill-in your Template ID (only if using Blynk.Cloud) *///     ~
#define BLYNK_TEMPLATE_ID "TMPL69ZwsxwdD"//                      ~
#define BLYNK_TEMPLATE_NAME "ESP32 Automation"//                 ~
#define BLYNK_AUTH_TOKEN "WFAehKOsaXP1FgseY2lAw3YUNECjzzvS"//    ~
//                                                               ~
// Đăng nhập tên wift và mật khẩu                                ~
char ssid[] = "TOTOLINK_N350RT";//                               ~
char pass[] = "09040704";//                                      ~
//~~~~~~~~~~~~~~~~~~~Địa_chỉ_BLYNK_và_WIFI~~~~~~~~~~~~~~~~~~~~~~~~


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>



char auth[] = BLYNK_AUTH_TOKEN;

void setup()
{
  // Kết nối với mạng Wi-Fi
  WiFi.begin(ssid, pass);
  Serial.begin(9600);
  
  // Đợi kết nối thành công
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Kết nối đến Blynk Server
  Blynk.begin(auth, ssid, pass);
  Serial.println("Blynk connected");
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
  } else if (!Blynk.connected()) {
    Serial.println("Blynk not connected");
  } else {
    Blynk.run();
  }
  delay(1000); // Đợi 1 giây trước khi kiểm tra lại
  
}
