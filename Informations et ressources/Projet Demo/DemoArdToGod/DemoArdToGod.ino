//Lecture d'un bouton en pulldown : https://arduinofactory.fr/bouton-poussoir/
//Lecture d'un potentiomètre : https://mataucarre.fr/index.php/2019/03/09/utiliser-un-potentiometre-avec-un-arduino/
// Lecture d'un piezzo :
//Lecture d'un capteur ultrason : https://arduinofactory.fr/capteur-de-distance/

// DECLARATION DES CONSTANTES ET DES VARIABLES GLOBALES

 // La chaine de caractère dans laquelle sera stockée toute les valeurs de capteur à envoyer à Godot

String valeursCapteurs = "";

// Définition des broches physiques pour chaques capteurs

unsigned long previous_time = 0; // Variable pour stocker le temps précédent

const int declencheurUltrason = 9; // Broche de déclenchement du capteur ultrason
const int echoUltrason = 10; // Broche de réception du capteur ultrason
const int brochePotentiometre = A0; // Broche du potentiomère rotatif
const int brocheVibreur = 11; // Broche du vibreur

// Définition des variables liées aux capteurs

long duration;  // Durée de l'impulsion du capteur ultrason
int distance;   // Stock la distance entre entre le capteur ultrason et l'objet

int valeurPotentiometre;

// Dans le setup vous devez lancer la communication série et définir si les broches
// declarées plus haut sont des entrées ou des sorties.

void setup() {

  Serial.begin(9600);  // Assurez vous que la valeur entre les parenthèse est la même dans l'initialisation de la communication dans Godot.

  pinMode(declencheurUltrason, OUTPUT);  // Le pin declencheurUltrason est une sortie (quand la sortie est haute, le capteur capture une valeur de distance)
  pinMode(echoUltrason, INPUT);   // le pin echoUltrason est une entrée (quand le capteur capture une valeur, elle est lu par l'arduino sur ce pin)
  pinMode(brochePotentiometre, INPUT);   // le pin echoUltrason est une entrée (quand le capteur capture une valeur, elle est lu par l'arduino sur ce pin)
  pinMode(brocheVibreur, OUTPUT);   // le pin vibreurPin est une sortie (quand la carte reçoit une valeur de Godot, l'arduino interprète la valeur et active ou désactive le vibreur pour simuler les pas)
}

void loop() {
  unsigned long current_time = millis();
  misAJourCapteurs();
  lectureMessageGodot();
  delay(10); // Delai extrêmement important pour ne pas surcharger la mémoire tampon de Godot et causer un ralentissement exponentiel du traitement des données reçues.
}

void misAJourCapteurs() {
  valeursCapteurs = "";  // Remise a zero de la chaine de caractère

  // Dans la chaine de caractères, les valeurs doivent être séparées par ":",
  // il ne doit pas y avoir de séparateur après la dernière valeur ni devant la première.

  valeursCapteurs += String(misAJourUltrason()) + ":";     // Sera à la position 0 dans la chaine de caractère
  valeursCapteurs += String(misAJourPotentiometre());      // Sera à la position 1 dans la chaine de caractère

  Serial.println(valeursCapteurs);  // Envoi des valeurs sous forme d'une chaine de caractères.
}

int misAJourUltrason() {
  digitalWrite(declencheurUltrason, LOW);
  delayMicroseconds(2);
  digitalWrite(declencheurUltrason, HIGH);
  delayMicroseconds(10);
  digitalWrite(declencheurUltrason, LOW);
  
  // Mesure la durée de l'impulsion retournée par le capteur
  duration = pulseIn(echoUltrason, HIGH);
  
  // Calcule la distance en fonction de la durée mesurée
  distance = duration*0.034/2;
  return distance;
}

void lectureMessageGodot(){
  char temp = Serial.read();        // Lecture du port série pour voir si Godot a envoyé de l'information
  if(temp == '1'){
    digitalWrite(brocheVibreur, HIGH); // Allumer la LED 
  }else if(temp == '0'){
    digitalWrite(brocheVibreur, LOW); // Eteindre la LED
  }
}

int misAJourPotentiometre() {
  valeurPotentiometre = analogRead(brochePotentiometre);
  return valeurPotentiometre;
}



