// Librerías para la cámara
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"
// Librerías para la tarjeta MicroSD
#include "FS.h"
#include "SD_MMC.h"
// Librerías para la memoria EEPROM 
#include "EEPROM.h"
//Pinout cámara
#include "pinout.h"
// Utilice 1 byte de espacio EEPROM
#define EEPROM_SIZE 1
// Contador de número de imagen
unsigned int contadorFoto = 0;


void initMicroSDCard() {
  // Inicia la tarjeta MicroSD
  Serial.println("Montaje de la tarjeta MicroSD");
  if (!SD_MMC.begin()) {
    Serial.println("Error al montar la tarjeta MicroSD");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No se encontró ninguna tarjeta MicroSD");
    return;
  }
}

void takeNewPhoto(String path) {
  // Tomar una foto con la cámara
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Falló la captura de la cámara");
    return;
  }

  // Guardar imagen en la tarjeta microSD
  fs::FS &fs = SD_MMC;
  File file = fs.open(path.c_str(), FILE_WRITE);
  if (!file) {
    Serial.println("No se pudo abrir el archivo en modo de escritura");
  } else {
    file.write(fb->buf, fb->len); // payload (imagen), longitud del payload
    Serial.printf("Archivo guardado en la ruta: %s\n", path.c_str());
  }

  // Cerrar el archivo
  file.close();
  // Devolver el frame buffer al controlador para su reutilización
  esp_camera_fb_return(fb);
}

void setup() {
  // Desactivar el detector de caída de tensión
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  // Iniciar monitor serie
  Serial.begin(115200);

  // Inicializa la cámara
  Serial.print("Inicializando el módulo de la cámara...");
  configuracionCamara();
  Serial.println("Camera OK!");

  // Inicializa la MicroSD
  Serial.print("Inicializando el módulo de la tarjeta MicroSD... ");
  initMicroSDCard();

  // Inicializar EEPROM con tamaño predefinido
  EEPROM.begin(EEPROM_SIZE);
  contadorFoto = EEPROM.read(0) + 1;

  // Ruta donde se guardará la nueva imagen en la tarjeta SD
  String path = "/foto" + String(contadorFoto) + ".jpg";
  Serial.printf("Nombre del archivo de imagen: %s\n", path.c_str());

  // Tomar y guardar foto
  takeNewPhoto(path);

  // Actualizar el contador de números de imagen en EEPROM
  EEPROM.write(0, contadorFoto);
  EEPROM.commit();

  // Esperar un momento antes de entrar en modo de suspensión
  delay(1000);
  
  // Ingrese al modo de sueño profundo
  esp_deep_sleep_start();
}

void loop() {
  // No se necesita código en el loop
}
