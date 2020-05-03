#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "dd-wrt";
const char* password = "frysisking123";

const char* host = "10.8.8.11";



String payload;
String whosBusy;
String Dad;
String Mom;
String Michael;
String Emily;




void setup()
{
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

void HTTPReq(){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(host, 80, "/test.html");
    int httpCode = http.GET();
//    Serial.println(httpCode);
//    Serial.println("REQEUST MADE");

    if (httpCode > 0){
//      Serial.println("STRING HERE");
      payload = http.getString();
//      Serial.println(payload);
      }

    delay(3000);
    } 
   else{
    Serial.println("[DISCONNECTED]");
   }
   Serial.println("[DISCONNECTED]");
  }


void loop()
{
 HTTPReq();
// Serial.println("payload below");
 Serial.println(payload);
// String test = "{ hello }";
// Serial.println(test.indexOf('}',3));

 
 int first = payload.indexOf('{');  //Determine Delimiters TURN FOLLOWING INTO OWN FUNCTION
 int last = payload.indexOf('}',1);
// Serial.println(first);
// Serial.println(last);

  whosBusy = payload.substring(1,5);
  Dad = payload.substring(6,9);
  Mom = payload.substring(10,13);
  Michael = payload.substring(14,17);
  Emily = payload.substring(18,21);
    
  Serial.println(whosBusy);
  Serial.println(Dad);
  Serial.println(Mom);
  Serial.println(Michael);
  Serial.println(Emily);
  


  delay(5000);
}
