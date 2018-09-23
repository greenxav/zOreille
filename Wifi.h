
static const unsigned long STRUCT_MAGIC = 123456789; /* Le nombre magique */

struct StructureConfWifi { /* La structure qui contient les données */
  unsigned long magic;
  char ssid[20];
  char motDePasse[30];
};
StructureConfWifi ConfWifi ; /* L'instance de la structure, globale, car utilisé dans plusieurs endroits du programme */



void chargeConfWifi() { /* Charge le contenu de la mémoire EEPROM dans la structure ConfWifi */
  // Lit la mémoire EEPROM
  EEPROM.get(0, ConfWifi);
  
  // Détection d'une mémoire non initialisée
  byte erreur = ConfWifi.magic != STRUCT_MAGIC;
  if (erreur) {// Valeurs par défaut
    strcpy(ConfWifi.ssid, "Livebox-1930");
    strcpy(ConfWifi.motDePasse, "19D134E65446296254DD39C27E");
  }
  // Sauvegarde les nouvelles données
  sauvegardeConfWifi();
}


void sauvegardeConfWifi() { /** Sauvegarde en mémoire EEPROM le contenu actuel de la structure */
  // Met à jour le nombre magic avant l'écriture
  ConfWifi.magic = STRUCT_MAGIC;
  EEPROM.put(0, ConfWifi);
}
