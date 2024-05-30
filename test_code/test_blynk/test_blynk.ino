
//~~~~~~~~~~~~~~~~~~~Địa_chỉ_BLYNK_và_WIFI~~~~~~~~~~~~~~~~~~~~~~~~
/* Fill-in your Template ID (only if using Blynk.Cloud) *///     ~
#define BLYNK_TEMPLATE_ID "TMPL69ZwsxwdD"//                      ~
#define BLYNK_TEMPLATE_NAME "ESP32 Automation"//                 ~
#define BLYNK_AUTH_TOKEN "WFAehKOsaXP1FgseY2lAw3YUNECjzzvS"//    ~

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
// Đăng nhập tên wift và mật khẩu                                ~
char ssid[] = "TOTOLINK_N350RT";//                               ~
char pass[] = "09040704";//                                      ~
//~~~~~~~~~~~~~~~~~~~Địa_chỉ_BLYNK_và_WIFI~~~~~~~~~~~~~~~~~~~~~~~~



void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}