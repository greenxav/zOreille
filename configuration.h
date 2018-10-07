// Les librairies nécessaires à notre montage
#include "EEPROM.h"
#include "NeoPixel.h"
#include "serial.h"
#include "Wifi.h"
#include "calcule.h"


// Les librairies de notre projet (Attention à l'ordre)
#include "EEPROM.h"
//#include "NeoPixel.ino"
//#include "Wifi.ino"


//Le brochage et les caractéristiques de nos capteurs
const int brocheLeds = 5; // D1 sur ESP8266
const int nbLeds = 12;
const int luminosite = 50;

int valeurCapteurMicro = 0;       // value read from the pot
const int brocheMicro = A0; //A0
int outputValue = 0;

//Variables pour la moyenne mobile
const int nbEchantillons = 10;    // le nombre d'échantillons (max 128)
int echantillon[nbEchantillons];  // un tableau pour stocker les échantillons lus
int indiceEchantillons = 0;       // l'indice de l'échantillon courant
int totalEchantillons = 0;      // la somme des échantillons mémorisés
int moyenneCapteurMicro = 0;      // la moyenne des échantillons mémorisés
int minimumCapteurMicro = 0;      // le minimum des échantillons mémorisés
int maximumCapteurMicro = 0;      // le maximum des échantillons mémorisés

int seuilBas=255;
int seuilHaut=767;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;
long bruit =0;
