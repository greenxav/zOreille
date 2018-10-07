



int calculMoyenneMobile (int echantillon){
  echantillon[indiceEchantillons] = echantillon;
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
  return totalEchantillons / nbEchantillons;
}
