#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;

void setup() {
  setup_wifi();
  http.begin("https://www.google.com/");
  int code = http.GET();
  Serial.println(code);
  http.end();
}

void loop() {

}

void setup_wifi(){
  Serial.begin(9600);
  WiFi.begin("MOVISTAR_78A8","NS2ajtQJ7TtDt9m");//DHCP
  while(WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
  Serial.println(WiFi.localIP());
}
