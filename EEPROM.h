// L'écriture dans une EEPROM se fait uniquement par octet
// Il n'y a que 512 octets ( de 0 à 511)
#include <EEPROM.h>


void prepaEEPROM() {
  EEPROM.begin(512);
}

void arretEEPROM() {
  EEPROM.end();
}

void effacerEEPROM() {
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
}

void EcritureEEPROM (int adresse, byte valeur){
  EEPROM.write(adresse, valeur);
  EEPROM.commit();
}

int LectureEEPROM (int adresse){
  return EEPROM.read(adresse);  
}
