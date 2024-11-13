#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Base64.h>
//Incluimos pinout
#include "pinout.h"
const char *serverURL = "http://192.168.1.5/dashboard/DATOS/upload.php";
void captureSend(){
  //Tomar una foto con la cámara
  camera_fb_t *fb = esp_camera_fb_get(); //captura una imagen (frame buffer)
  if(!fb){
    Serial.println("Fallo la captura");
    return;
  }
  /*************************  BASE 64  ****************************/
  String imageBase64 = "data:image/jpeg;base64," + base64::encode((const uint8_t *)fb->buf,fb->len);
  /**************************  HTTP  ******************************/
  HTTPClient http;
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");
  //Creamos un String JSON
  String jsonPayload = "{\"imageData\":\"" + imageBase64 + "\"}";
  int code = http.POST(jsonPayload);
  if (code > 0){
    String response = http.getString();
    Serial.println(response);
  }
  http.end();
  /****************************************************************/
  esp_camera_fb_return(fb);//Liberar recursos
}

void setup() {
  setup_wifi();
  //Inicializa la cámara
  Serial.println("Iniciando el módulo de la camera...");
  configuracionCamara();
  Serial.println("camera OK!");
}

void loop() {
  delay(15000);
  captureSend();
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
