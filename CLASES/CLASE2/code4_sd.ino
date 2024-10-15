#include "FS.h"
#include "SD_MMC.h"
unsigned long t = 0;
int valueCount = 0;
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
  if(millis()-t>10000){
    //Abrimos el archivo para escribir
    File file = SD_MMC.open("/datos.txt",FILE_APPEND);
    if(!file)
      {
        Serial.println("Error a labrir el archivo para escribir");
        return;
      }
    //Escribe "Hola en el archivo"
    valueCount++;
    file.print("Valor ");
    file.print(valueCount);
    file.print("\n");
    Serial.print("Valor escrito en el archivo: Valor ");
    Serial.println(valueCount);
    //Cierre el archivo
    file.close();
    Serial.println("Archivo cerrado.");
    t = millis();
  }

}
