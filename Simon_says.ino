/*
  Simon says

  created 25 May 2018
  by Guillaume SARRAMEGNA
  
  This example code is part of the public domain.
*/

// Déclaration des entrées/sorties
const int redLed = 2;
const int redButton = 3;
const int greenLed = 4;
const int greenButton = 5;
const int blueLed = 6;
const int blueButton = 7;
const int yellowLed = 8;
const int yellowButton = 9;
const int speaker = 10;

// Autres variables
int notes[] = {261, 330, 392, 523};
//             Do,  Mi,  Sol, Do
bool mute = false;

// 50 éléments max
int sequence[50];

void setup() {
  Serial.begin(9600);
  
  // Définition des pin d'entrée
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(yellowButton, INPUT);
  
  // Définition des pin de sortie
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  
  pinMode(speaker, OUTPUT);
}

void loop() {
  Serial.println("Intializing game");
  
  // On utilise randomSeed sur un pin analogique non connecté pour initialiser une valeur aléatoire
  randomSeed(analogRead(A0));
  
  // On allume les leds pour dire qu'on est prêt
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  
  // On attend la pression d'un bouton
  if(readButton() != 1) {
    mute = true;
  } else {
    mute = false;
  }
  
  // On éteint les leds
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(yellowLed, LOW);

  // Mélodie de lancement du jeu
  startMelody();
  delay(2000);
  
  // Début du jeu
  boolean gameOver = false;
  int level = 0;
    
  while (!gameOver) {
    
    addNote(level);
    playSequence(level);
    
    for (int i = 0; i < level + 1; i++) {
      switch (sequence[i]) {
        case 1:
          Serial.println("Expect red note");
          break;
        case 2:
          Serial.println("Expect green note");
          break;
        case 3:
          Serial.println("Expect blue note");
          break;
        case 4:
          Serial.println("Expect yellow note");
          break;
      }

      int buttonPressed = readButton();
      
      // Si le bouton appuyé est celui actuel de la séquence
      if (buttonPressed == sequence[i]) {
        playNote(buttonPressed);
      } else {
        gameOver = true;
        // Mélodie de fin du jeu
        gameOverMelody();
      }
      
      // On arrête le jeu
      if (gameOver) {
        break;
      }
    }
    
    level++;
    delay(1000);
  }
}

void addNote(int level) {
  int randomNote = random(1, 5);
  
  switch (randomNote) {
    case 1:
      Serial.println("Adding red note to sequence");
      break;
    case 2:
      Serial.println("Adding green note to sequence");
      break;
    case 3:
      Serial.println("Adding blue note to sequence");
      break;
    case 4:
      Serial.println("Adding yellow note to sequence");
      break;
  }
  
  sequence[level] = randomNote;
}

void playSequence(int level) {
  Serial.println("Playing sequence");
  
  for (int i = 0; i <= level; i++) {
    playNote(sequence[i]);
  }
}

int readButton() {
  Serial.println("Waiting for input");
  
  int buttonPressed = 0;
  
  while (!buttonPressed) {
    if (digitalRead(redButton) == HIGH) {
      Serial.println("Red button pressed");
      buttonPressed = 1;
    } else if (digitalRead(greenButton) == HIGH) {
      Serial.println("Green button pressed");
      buttonPressed = 2;
    } else if (digitalRead(blueButton) == HIGH) {
      Serial.println("Blue button pressed");
      buttonPressed = 3;
    } else if (digitalRead(yellowButton) == HIGH) {
      Serial.println("Yellow button pressed");
      buttonPressed = 4;
    }
  }
  
  return buttonPressed;
}

void playNote(int buttonPressed) {
  switch (buttonPressed) {
    case 1:
      Serial.println("Playing red note");
      digitalWrite(redLed, HIGH);
      break;
    case 2:
      Serial.println("Playing green note");
      digitalWrite(greenLed, HIGH);
      break;
    case 3:
      Serial.println("Playing blue note");
      digitalWrite(blueLed, HIGH);
      break;
    case 4:
      Serial.println("Playing yellow note");
      digitalWrite(yellowLed, HIGH);
      break;
  }
  playTone(notes[buttonPressed - 1]);
  delay(700);
  
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(yellowLed, LOW);
  noTone(speaker);
  delay(100);
}

void playTone(int note) {
  if (!mute) {
    tone(speaker, note);
  }
}

void startMelody() {
  Serial.println("Starting new game");
  
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  playTone(notes[0]);
  delay(300);
  playTone(notes[1]);
  delay(300);
  playTone(notes[2]);
  delay(300);
  playTone(notes[3]);
  delay(300);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(yellowLed, LOW);
  noTone(speaker);
}

void gameOverMelody() {
  Serial.println("Game over");
  
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  playTone(notes[3]);
  delay(150);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(yellowLed, LOW);
  delay(150);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  playTone(notes[2]);
  delay(150);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(yellowLed, LOW);
  playTone(notes[1]);
  delay(150);
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  playTone(notes[0]);
  delay(150);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(yellowLed, LOW);
  delay(500);
  noTone(speaker);
}