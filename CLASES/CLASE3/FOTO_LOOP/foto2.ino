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
unsigned long t = 0;

void setup() {
  Serial.begin(115200);
  setup_cam();//Iniciar camara
  initMicroSDCard();//Iniciamos la MicroSD
  Serial.println("Iniciando EEPROM...");
  //Iniciamos EEPROM con tamaño definido
  EEPROM.begin(EEPROM_SIZE);
  contadorFoto = EEPROM.read(0) + 1;
  //Esperar un momento antes de entrar al modo suspensión
  delay(1000);
  //esp_deep_sleep_start();
}

void loop() {
   if(millis()-t>10000){
        //tomar y guardar foto
        String path = "/foto" + String(contadorFoto)+ ".jpg";
        takeNewPhoto(path);
        //Actualizar el contador de números de imagen en EEPROM
        EEPROM.write(0,contadorFoto); //Escribe un nuevo valror en la dirección 0 de la EEPROM
        EEPROM.commit();//Guarda los cambios
        contadorFoto++;
        t = millis();
   }
}
