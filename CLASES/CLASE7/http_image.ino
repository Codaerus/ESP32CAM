#include "esp_camera.h"
#include "driver/rtc_io.h"
//Librerías para la tarjeta MicroSD
#include "FS.h"
#include "SD_MMC.h"
//Librería para la EEPROM
#include "EEPROM.h"
//Incluimos pinout
#include "pinout.h"
//Utilizamos 1 bytes para la EEPROM
#define EEPROM_SIZE 1
//Contador de número de imagen
unsigned int contadorFoto = 0;
//Bibliotecas para la conexión WiFi y HTTP
#include <WiFi.h>
#include <HTTPClient.h>

void takeNewPhoto(String path){
  //Tomar una foto con la cámara
  camera_fb_t *fb = esp_camera_fb_get(); //captura una imagen (frame buffer)
  if(!fb){
    Serial.println("Fallo la captura");
    return;
  }
  //Guardar la imagen en la tarjeta microSD
  fs::FS &fs = SD_MMC;
  File file = fs.open(path.c_str(), FILE_WRITE);
  if (!file){
    Serial.println("No se pudo cear el archivo");
  }else{
    file.write(fb->buf,fb->len); //payload(imagen), longitud del payload
    Serial.printf("Archivo guardado en la ruta:%s\n",path.c_str());
  }
  //cerrar el archivo
  file.close();
  esp_camera_fb_return(fb);//Liberar recursos
}
void setup() {
  setup_wifi(); // serial a 9600
  //Desactivamos el detector de caída de tensión para evitar reinicios inesperados
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG,0);
  //Inicializa la cámara
  Serial.println("Iniciando el módulo de la camera...");
  configuracionCamara();
  Serial.println("camera OK!");
  //Iniciamos la MicroSD
  Serial.println("Iniciando el módulo de la tarjeta MicroSD...");
  initMicroSDCard();
  //Iniciamos EEPROM con tamaño definido
  EEPROM.begin(EEPROM_SIZE);
  contadorFoto = EEPROM.read(0) + 1;
  String path = "/foto" + String(contadorFoto)+ ".jpg";

  //tomar y guardar foto
  takeNewPhoto(path);
  //Enviar foto
  sendPhoto(path);
  //Actualizar el contador de números de imagen en EEPROM
  EEPROM.write(0,contadorFoto); //Escribe un nuevo valror en la dirección 0 de la EEPROM
  EEPROM.commit();//Guarda los cambios
  //Esperar un momento antes de entrar al modo suspensión
  delay(1000);
  esp_deep_sleep_start();
}

void loop() {

}

void sendPhoto(String path){

  //Guardar la imagen en la tarjeta microSD
  fs::FS &fs = SD_MMC;
  File file = fs.open(path.c_str());
  if (!file){
    Serial.println("No se pudo abrir el archivo");
    return;
  }

  HTTPClient http;
  http.begin("http://192.168.1.4:80/dashboard/FOTO/");
  http.addHeader("Content-Type","image/jpeg");
  int code = http.sendRequest("POST",&file,file.size());
  if(code > 0)
    {
      Serial.printf("Código de respuesta HTTP: %d\n",code);
    }
  http.end();
  //cerrar el archivo
  file.close();
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
