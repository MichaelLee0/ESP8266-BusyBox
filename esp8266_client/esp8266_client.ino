//esp8266_client - Michael's Board

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//Info for WiFi
const char* host = "10.8.8.11";
const char* ssid = "dd-wrt";
const char* password = "frysisking123";
const int ID = 2;   //In order of Dad,Mom,Michael,Emily; 

//Vars for board info
const int red_1 = 13; //D7 -> Dad
const int red_2 = 12; //D6 pin -> Mom
const int red_3 = 14; //D5 -> Emily
const int green_1 = 15; //D8
const int buttInput = 5; //D1 hahaha

int counter = 1; //counter that ticks up for every press
int buttState = 0; //check for press
int buttState2 = 0; //check against to register long press
int supercount = 0; //tells to hold under the long pause

int storeVal1 = 0;  //Dad
int storeVal2 = 0;  //Mom
int storeVal3 = 0;  //Emily

String payload;
String payloadPast;
String whosBusy;
//String Dad;
//String Mom;
//String Michael;
//String Emily;

int timeBefore;
const long interval = 30000;

int cycles = 60;


//




void setup() 
{

  WiFi.mode(WIFI_STA);
  
   //INPUT OUTPUT PINS
     pinMode(red_1,OUTPUT);
     pinMode(red_2, OUTPUT);
     pinMode(red_3, OUTPUT);
     pinMode(green_1, OUTPUT);
     pinMode(buttInput, INPUT);

   //CONNECT TO WIFI
     Serial.begin(115200);
     Serial.println();

     Serial.printf("Connecting to %s ", ssid);
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
       }
     Serial.println(" connected");
}

void setLights() {
  
  
   //FLIPPY FLIPPY PART OF THE PROGRAM. ONLY RUNS IF NOT HOLDING
  if(digitalRead(buttInput) == 1 && supercount == 0)  //Read and see if this is a long press
    { 
      buttState = digitalRead(buttInput);
      Serial.println("buttonState is");
      Serial.println(buttState);
      delay(500);
      buttState2 = digitalRead(buttInput);

      if (buttState == 1 && buttState2 == 0)    //If it's a short press run this:
        {
          counter = counter + 1;
          Serial.println("counter is");
          Serial.println(counter);
          if (counter == 5)
            {
              counter = 1;
              Serial.println("counter is");
              Serial.println(counter);
             }
        }
  
      if (buttState == 1 && buttState2 == 1)   //If it's a long press run this -> shut off all lights and give me a fourth option
        {
          digitalWrite(red_1, LOW);
          digitalWrite(red_2, LOW);
          digitalWrite(red_3, LOW);
          digitalWrite(green_1, HIGH);
          buttState = 0;
          supercount = 1;
        }
  
      else    //if not, turn on the lights biatches
        {
          if (counter == 1) 
            {
              digitalWrite(red_1, HIGH);
              digitalWrite(red_3, LOW);
            }
          if (counter == 2) 
            {
              digitalWrite(red_2, HIGH);
              digitalWrite(red_1, LOW);
            }
          if (counter == 3) 
            {
              digitalWrite(red_3, HIGH);
              digitalWrite(red_2, LOW);
            }
          if (counter == 4) 
            {
              digitalWrite(red_3, LOW);
            }
        }
    }

  if(digitalRead(buttInput) == 1 && supercount == 1)      //to get out of the third option, hold it
    {
      delay(500);
      buttState2 = digitalRead(buttInput);
      if (buttState2 == 1) 
        {
          Serial.println("FUCK");
          digitalWrite(green_1,LOW);
          supercount = 0;
        }
     }
     
  buttState = 0;      //Reset the buttonstate variables
  buttState2 = 0;
  
  if ( millis() - timeBefore == interval)   //Stay in this function until a certain interval.
    {
      return;
    }
}

String assignVal() //Takes the string returned from get request and seperates it into our messages.
{
   int first = payload.indexOf('{');  //Determine Delimiters TURN FOLLOWING INTO OWN FUNCTION
   int last = payload.indexOf('}',1);
      // Serial.println(first);
      // Serial.println(last);

   whosBusy = payload.substring(1,5);      //Processes strings
   return(whosBusy);

      //   Dad = payload.substring(6,9);
      //   Mom = payload.substring(10,13);
      //   Michael = payload.substring(14,17);
      //   Emily = payload.substring(18,21);
}

String cutOut(String toCut, int index)     //Compares the past string and the recently fetched string. if difference in 'other' blocks then changes. returns the log.
{
  String cutString;
  for (int i = index; i < toCut.length(); i++)
    {
      cutString = cutString + toCut[i];
    }
  return cutString;
}



void loop()
{
  Serial.println("Another Loop");
  
//  if(WiFi.status() == WL_CONNECTED)   //Fetch data
//    {
//      HTTPClient http;
//      http.begin(host, 80, "/test.html");
//      int httpCode = http.GET();
////    Serial.println(httpCode);
////    Serial.println("REQEUST MADE");
//      if (httpCode > 0)
//        {
////        Serial.println("STRING HERE");
//          payload = http.getString();
////        Serial.println(payload);
//        }
//       delay(3000);
//    }       
//  else
//    {
//      Serial.println("[DISCONNECTED]");
//    }
//  Serial.println("[DISCONNECTED]");
//  
//  whosBusy = assignVal();  //Parse the incoming Data
//  String restOfPayload = cutOut(payload, 6);      //Cuts off the top part of the payload to transplant int Put request.
//  if (SCbefore != supercount)
//    {
//      whosBusy[ID] = supercount;
//    }
//  

  if(WiFi.status () == WL_CONNECTED)      //Put Request
    {     
      HTTPClient http;
      http.begin(host, 80, "/PutTest.html");
      http.addHeader("Content-Type", "text/plain");

      String toPut = "This Works";
      
//      String toPut = String("< "+ whosBusy + restOfPayload);
      int httpResponseCode = http.PUT(toPut);
      if(httpResponseCode > 0)
        {
          String response = http.getString();
          Serial.println(httpResponseCode);
          Serial.println(response);
        }
      else
        {
          Serial.print("Error on sending Put Request");
          Serial.println(httpResponseCode);
        }
      http.end();
    }
    
   else
    {
      Serial.println("Error in Wifi Connection");
    }

   delay(10000);
// 
//  Serial.println(whosBusy[0]);  //Test to see if the correct LEDs are lighting
//  Serial.println(whosBusy[1]);
//  Serial.println(whosBusy[3]);
//
//
//  
//  if (whosBusy[0] == '1')    //Check through Emily, Dad and Mom's 'call' data. Light up their light if it's on.
//    {
//      digitalWrite(red_1, HIGH);
//    }
//  if (whosBusy[1] == '1')
//    {
//      digitalWrite(red_2, HIGH);
//    }
//  if (whosBusy[3] == '1'){
//      digitalWrite(red_3, HIGH);
//    }
//
//    delay(15000);
//  
////  Serial.println(cycles);
//  
//  timeBefore = millis();    //check if anything has been pressed
//  SCBefore = supercount;
//  setLights();
//
//  

}
