#include "configuration.h"


Adafruit_NeoPixel anneauLeds = Adafruit_NeoPixel(nbLeds, brocheLeds, NEO_RGB + NEO_KHZ800);

void setup() {
  prepaEEPROM;

  Serial.begin(9600);
  pinMode(A0, INPUT);

  // Lecture du capteur
  valeurCapteurMicro = analogRead(brocheMicro);

  anneauLeds.begin();
  anneauLeds.show();
  anneauLeds.setBrightness(luminosite);
  //Test anneau
  anneauLeds.setPixelColor(1, anneauLeds.Color(255,0,0));anneauLeds.show();//Vert
  delay(1000);
  anneauLeds.setPixelColor(2, anneauLeds.Color(0,255,0));anneauLeds.show();//Rouge
  delay(1000);
  anneauLeds.setPixelColor(3, anneauLeds.Color(0,0,255));anneauLeds.show();//Bleu
  delay(1000);
  anneauLeds.setPixelColor(4, anneauLeds.Color(255,255,0));anneauLeds.show();//Jaune
  delay(1000);
  rainbow(20, anneauLeds);

  // On initialise le tableau d'échantillons à 0
  for (int i = 0; i < nbEchantillons; i++)
    {echantillon[i] = 0;}
//Fin setup
}

void loop() {
  // Ecoute du port série pour les commandes éventuelles
  ecoutePortSerie;//rien

  // Soustraction de l'echantillon précédent
  totalEchantillons = totalEchantillons - echantillon[indiceEchantillons];

  // Lecture du capteur
  valeurCapteurMicro = analogRead(brocheMicro);
  // calcul de la moyenne
  moyenneCapteurMicro = calculMoyenneMobile(valeurCapteurMicro);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(valeurCapteurMicro);
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
