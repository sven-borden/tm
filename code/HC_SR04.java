//HC_SR04
//Authors: Eric Brunner & Sven Borden
//Inspired by example code on trollmaker.com
//more at: 
//http://trollmaker.com/article3/arduino-and-hc-sr04-ultrasonic-sensor

#define trigPin 7
#define echoPin 8

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {	
  long microseconds, cm;
  
  /*Pour que le signal declencheur HAUT soit propre,
  on commence par lancer un court signal BAS*/
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  
  //Ensuite le signal que attend le senseur!
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  
  /*On enregistre la longueure du signal HAUT
  renvoye par le senseur*/
  microseconds = pulseIn(echoPin, HIGH);
  
  //la distance en cm est calculee puis...
  cm = (microseconds/2) / 29.1;
  //...affichee
  Serial.println(cm);
  
  delay(100);
  
}
