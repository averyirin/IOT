/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */

int sensorPin = 2; //A2 on ATtiny85
int ledPin = 0;   //D0 on ATtiny85
int fullPin = 2; //D1 on ATtiny85
int halfPin = 1; //D0 on ATtiny85
int distVal = 0; //var distance
int halfNum = 375; // half threshold
int emptyNum = 250; //empty threshold
void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(fullPin, OUTPUT);  // declare the fullPin as an OUTPUT
  pinMode(halfPin, OUTPUT);  // declare the halfPin as an OUTPUT
}

void loop() {
  //read 
  distVal = analogRead(sensorPin);
  if(distVal > halfNum ){
    digitalWrite(fullPin,HIGH);
    digitalWrite(halfPin,HIGH);
    digitalWrite(ledPin, LOW);
  }else if(distVal > emptyNum && distVal <= halfNum){
    digitalWrite(fullPin,LOW);
    digitalWrite(halfPin,HIGH);
    digitalWrite(ledPin, LOW);
  }
  else if(distVal <= emptyNum){
    digitalWrite(fullPin,LOW);
    digitalWrite(halfPin,LOW);    
    digitalWrite(ledPin, HIGH);
  }
  delay(1000);
}
