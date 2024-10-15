#include "FS.h"
#include "SD_MMC.h"
unsigned long t = 0;

void setup() {
  Serial.begin(9600);
  //incializa la SD
  if(!SD_MMC.begin())
    {
      Serial.println("Error al inicial la SD!");
      return;
    }
    Serial.println("Tarjeta SD inicializada");  
    //Abrimos el archivo para escribir
    File file = SD_MMC.open("/datos.txt",FILE_WRITE);
    if(!file)
      {
        Serial.println("Error a labrir el archivo para escribir");
        return;
      }
    //Escribe "Hola en el archivo"
    if(file.print("Hola"))
      {
        Serial.println("Escrito en el archivo: Hola");
      }
    else{
      Serial.println("Error al escribir en el archivo!");
    }
    //Cierre el archivo
    file.close();
    Serial.println("Archivo cerrado.");
}

void loop() {
  if(millis()-t>10000){
    Serial.println("Hola");
    t = millis();
  }

}
