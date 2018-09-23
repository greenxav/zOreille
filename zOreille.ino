#include "configuration.h"


Adafruit_NeoPixel anneauLeds = Adafruit_NeoPixel(nbLeds, brocheLeds, NEO_RGB + NEO_KHZ800);

void setup() {
  prepaEEPROM;
  
  Serial.begin(9600);
  // Lecture du capteur
  valeurCapteurMicro = analogRead(brocheMicro);
  outputValue = map(valeurCapteurMicro, 0, 1023, 0, 255);
  minimumCapteurMicro = outputValue;
  maximumCapteurMicro = outputValue;
  
  anneauLeds.begin();
  anneauLeds.show();
  anneauLeds.setBrightness(luminosite);
  anneauLeds.setPixelColor(1, anneauLeds.Color(255,0,0));//Vert
  anneauLeds.show();
  delay(1000);

  anneauLeds.setPixelColor(2, anneauLeds.Color(0,255,0));//Rouge
  anneauLeds.show();
  delay(1000);

  anneauLeds.setPixelColor(3, anneauLeds.Color(0,0,255));//Bleu
  anneauLeds.show();
  delay(1000);

  anneauLeds.setPixelColor(4, anneauLeds.Color(255,255,0));//Jaune
  anneauLeds.show();
  delay(5000);

  rainbow(20, anneauLeds);

  
  for(int i=0;i<anneauLeds.numPixels();i++){
    anneauLeds.setPixelColor(i, anneauLeds.Color(255,0,0));
  }
  anneauLeds.show();
  delay(5000);
  
  // On remplit le tableau d'échantillons avec des 0
  for (int i = 0; i < nbEchantillons; i++) {
    echantillon[i] = 0;
  }
}

void loop() {
  // Ecoute du port série pour les commandes éventuelles
  ecoutePortSerie;
  
  // Soustraction de l'echantillon précédent
  totalEchantillons = totalEchantillons - echantillon[indiceEchantillons];
  
  // Lecture du capteur
  valeurCapteurMicro = analogRead(brocheMicro);
  outputValue = map(valeurCapteurMicro, 0, 1023, 0, 255);
  if (outputValue < minimumCapteurMicro) {
    minimumCapteurMicro = outputValue;
    }
  else if (outputValue> maximumCapteurMicro) {
    maximumCapteurMicro = outputValue;    
    }
  echantillon[indiceEchantillons] = map(outputValue-minimumCapteurMicro,0,maximumCapteurMicro,0,255);
  
  // Ajout du dernier echantillon
  totalEchantillons = totalEchantillons + echantillon[indiceEchantillons];

  // Incrémentation de l'indice
  indiceEchantillons++;
  // si on est à la fin du tableau ...
  if (indiceEchantillons >= nbEchantillons) {
    // ...retour au début
    indiceEchantillons = 0;
  }
 
  // calcul de la moyenne
  moyenneCapteurMicro = totalEchantillons / nbEchantillons;

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(valeurCapteurMicro);
  Serial.print("\t output = ");
  Serial.print(outputValue);
  Serial.print("\t minimum = ");
  Serial.print(minimumCapteurMicro);
  Serial.print("\t maximum = ");
  Serial.print(maximumCapteurMicro);
  Serial.print("\t echantillon = ");
  Serial.print(echantillon[indiceEchantillons]);
  Serial.print("\t Moyenne = ");
  Serial.println(moyenneCapteurMicro);
  
  for(int i=0;i<anneauLeds.numPixels();i++){
    
    anneauLeds.setPixelColor(i, anneauLeds.Color(255,moyenneCapteurMicro,0));
  }
  anneauLeds.show();

}
/*void faded(g1,r1,b1,g2,r2,b2) {
  
  
}*/






void rainbow1(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<anneauLeds.numPixels(); i++) {
      anneauLeds.setPixelColor(i, Wheel1((i+j) & 255));
    }
    anneauLeds.show();
    delay(wait);
  }
}
uint32_t Wheel1(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return anneauLeds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return anneauLeds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return anneauLeds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
