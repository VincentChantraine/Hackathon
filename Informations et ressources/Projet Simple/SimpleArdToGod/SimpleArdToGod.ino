const int buttonPin = 2;
int buttonState = 0;
int increment = 0;

int derniereActivation = 0;
int tempsEcoule = 0;

void setup() {
  Serial.begin(9600); //make sure this is the same as the Baud Rate in Godot, should be 9600.

  pinMode(buttonPin, INPUT_PULLUP);   // Définir la broche pour le test avec le bouton
  pinMode(LED_BUILTIN, OUTPUT);       // Permet de définir la sortie pour la LED integrée à la carte
}

void loop() {
  buttonState = digitalRead(buttonPin);           // Lire le bouton, lorsqu'il est appuyé, envoi à godot un incrément de 1 à l'infini
  tempsEcoule = millis() - derniereActivation;    // Calculer le temps qui s'est écoulé entre le dernier envoi à Godot et le temps actuel

  if(buttonState == LOW || tempsEcoule > 3000){   // Si on appuie sur un bouton ou que 3 secondes se sont écoulées depuis le dernier envoi,
    Serial.println(increment);                    // On envoi une valeur qui s'incrémente à chaque fois
    increment++;
    derniereActivation = millis();
  }

  char temp = Serial.read();          // Lecture du port série pour voir si Godot a envoyé de l'information
  if(temp == '1'){                    // Si la valeur est 1, on allume la Led
    digitalWrite(LED_BUILTIN, HIGH);  // Allumer la LED 
  }else if(temp == '0'){              // Si la valeur est 0, on éteint la Led
    digitalWrite(LED_BUILTIN, LOW);   // Eteindre la LED
  }
}