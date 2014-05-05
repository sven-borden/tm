#define A 12 // define input pin "A"
#define B 11 // define input pin "B"
#define E 10 // define enable pin "E"

byte i;

void setup(){

// tous les pins sont des "OUTPUT", ils vont contoler le moteur

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(E, OUTPUT);
}

void loop(){

// boucles faisant varier la vitesse lineairement en avant et en arriere

  for(i = 0; i < 200; i++){
    forward(A, B, E, i);
    delay(50);
  }
  for(i = 200; i > 0; i--){
    forward(A, B, E, i);
    delay(50);
  }
  for(i = 0; i < 200; i++){
    backward(A, B, E, i);
    delay(50);
  }
  for(i = 200; i > 0; i--){
    backward(A, B, E, i);
    delay(50);
  }
}

//methode globale pour controler le moteur, fait appel aux
//methodes halt, backward et forward.
void motor(int speedo){
  if (abs(speedo) > 255){
    halt(A,B);
    break;
  }
  else if (speedo > 0){
   forward(A, B, E, speedo);
  }
  else if (speedo < 0){
    backward(A, B, E, speedo);
  }
  else if (speedo == 0){
    halt (A, B);
  }
}

//fonction faisant tourner le moteur en avant ou l'inverse d'en arriere.
void forward(byte pin1, byte pin2, byte pinEnable, byte speedo){
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  analogWrite(pinEnable, speedo);
}

//fonction faisant tourner le moteur en arriere ou l'inverse d'en avant.
void backward(byte pin1, byte pin2, byte pinEnable, byte speedo){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  analogWrite(pinEnable, speedo);
}

//fonction servant a arreter le moteur.
void halt(byte pin1, byte pin2){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}
