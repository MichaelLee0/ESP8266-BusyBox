// Led_Test_esp8266

#include <ESP8266WiFi.h>


// WiFi.mode(WIFI_STA); -> USE THIS TO TRY TO GET THIS SHIT FROM NOT WORKING AS AN AP


const int red_1 = 13; //D7
const int red_2 = 12; //D6 pin
const int red_3 = 14; //D5
const int buttInput = 5; //D2 hahaha

int counter = 1; //counter that ticks up for every press
int buttState = 0; //check for press
int buttState2 = 0; //check against to register long press
int supercount = 0; //tells to hold under the long pause

void setup() {
  WiFi.mode(WIFI_STA);
  
  // Associate pins to output:

  pinMode(red_1,OUTPUT);
  pinMode(red_2, OUTPUT);
  pinMode(red_3, OUTPUT);
  pinMode(buttInput, INPUT);
  
  Serial.begin(9600);
}

void loop() {

  //FLIPPY FLIPPY PART OF THE PROGRAM. ONLY RUNS IF NOT HOLDING
if(digitalRead(buttInput) == 1 && supercount == 0){ //Read and see if this is a long press
  buttState = digitalRead(buttInput);
  Serial.println("buttonState is");
  Serial.println(buttState);
  delay(500);
  buttState2 = digitalRead(buttInput);


//If it's a short press run this:
  if (buttState == 1 && buttState2 == 0) {
    counter = counter + 1;
    Serial.println("counter is");
    Serial.println(counter);
    if (counter == 4){
      counter = 1;
      Serial.println("counter is");
      Serial.println(counter);
    }
  }
  
//If it's a long press run this -> shut off all lights and give me a fourth option
  if (buttState == 1 && buttState2 == 1) {
    digitalWrite(red_1, LOW);
    digitalWrite(red_2, LOW);
    digitalWrite(red_3, LOW);
    buttState = 0;
    supercount = 1;
  }
  //if not, turn on the lights biatches
    else{
      if (counter == 1) {
        digitalWrite(red_1, HIGH);
        digitalWrite(red_3, LOW);
      }
      if (counter == 2) {
        digitalWrite(red_2, HIGH);
        digitalWrite(red_1, LOW);
      }
      if (counter == 3) {
        digitalWrite(red_3, HIGH);
        digitalWrite(red_2, LOW);
    }
  }
}

//to get out of the third option, hold it
if(digitalRead(buttInput) == 1 && supercount == 1) {
  delay(500);
  buttState2 = digitalRead(buttInput);
  if (buttState2 == 1) {
    Serial.println("FUCK");
    supercount = 0;
  }
}
//Reset the buttonstate variables
buttState = 0;
buttState2 = 0;

}

//  
// digitalWrite(red_1, HIGH);
// delay(500);
// digitalWrite(red_2, HIGH);
// delay(500);
// digitalWrite(red_3, HIGH);
// delay(500);
// digitalWrite(red_1, LOW);
// delay(500);
// digitalWrite(red_2, LOW);
// delay(500);
// digitalWrite(red_3, LOW);
