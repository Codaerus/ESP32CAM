#include "SD_MMC.h"

void setup() {
  Serial.begin(9600);
  //incializa la SD
  if(!SD_MMC.begin())
    {
      Serial.println("Error al inicial la SD!");
      return;
    }
    Serial.println("Tarjeta SD inicializada");  

}

void loop() {


}
