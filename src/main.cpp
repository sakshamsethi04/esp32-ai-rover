#include <Arduino.h>
#include "secrets.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
const char* ssid = SSID_secret;
const char* password = PASSWORD_secret;
const char* api="generativelanguage.googleapis.com";
const char* certificate=R"EOF(-----BEGIN CERTIFICATE-----
MIIFCzCCAvOgAwIBAgIQf/AFoHxM3tEArZ1mpRB7mDANBgkqhkiG9w0BAQsFADBH
MQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExM
QzEUMBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMjMxMjEzMDkwMDAwWhcNMjkwMjIw
MTQwMDAwWjA7MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNl
cnZpY2VzMQwwCgYDVQQDEwNXUjIwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK
AoIBAQCp/5x/RR5wqFOfytnlDd5GV1d9vI+aWqxG8YSau5HbyfsvAfuSCQAWXqAc
+MGr+XgvSszYhaLYWTwO0xj7sfUkDSbutltkdnwUxy96zqhMt/TZCPzfhyM1IKji
aeKMTj+xWfpgoh6zySBTGYLKNlNtYE3pAJH8do1cCA8Kwtzxc2vFE24KT3rC8gIc
LrRjg9ox9i11MLL7q8Ju26nADrn5Z9TDJVd06wW06Y613ijNzHoU5HEDy01hLmFX
xRmpC5iEGuh5KdmyjS//V2pm4M6rlagplmNwEmceOuHbsCFx13ye/aoXbv4r+zgX
FNFmp6+atXDMyGOBOozAKql2N87jAgMBAAGjgf4wgfswDgYDVR0PAQH/BAQDAgGG
MB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/
AgEAMB0GA1UdDgQWBBTeGx7teRXUPjckwyG77DQ5bUKyMDAfBgNVHSMEGDAWgBTk
rysmcRorSCeFL1JmLO/wiRNxPjA0BggrBgEFBQcBAQQoMCYwJAYIKwYBBQUHMAKG
GGh0dHA6Ly9pLnBraS5nb29nL3IxLmNydDArBgNVHR8EJDAiMCCgHqAchhpodHRw
Oi8vYy5wa2kuZ29vZy9yL3IxLmNybDATBgNVHSAEDDAKMAgGBmeBDAECATANBgkq
hkiG9w0BAQsFAAOCAgEARXWL5R87RBOWGqtY8TXJbz3S0DNKhjO6V1FP7sQ02hYS
TL8Tnw3UVOlIecAwPJQl8hr0ujKUtjNyC4XuCRElNJThb0Lbgpt7fyqaqf9/qdLe
SiDLs/sDA7j4BwXaWZIvGEaYzq9yviQmsR4ATb0IrZNBRAq7x9UBhb+TV+PfdBJT
DhEl05vc3ssnbrPCuTNiOcLgNeFbpwkuGcuRKnZc8d/KI4RApW//mkHgte8y0YWu
ryUJ8GLFbsLIbjL9uNrizkqRSvOFVU6xddZIMy9vhNkSXJ/UcZhjJY1pXAprffJB
vei7j+Qi151lRehMCofa6WBmiA4fx+FOVsV2/7R6V2nyAiIJJkEd2nSi5SnzxJrl
Xdaqev3htytmOPvoKWa676ATL/hzfvDaQBEcXd2Ppvy+275W+DKcH0FBbX62xevG
iza3F4ydzxl6NJ8hk8R+dDXSqv1MbRT1ybB5W0k8878XSOjvmiYTDIfyc9acxVJr
Y/cykHipa+te1pOhv7wYPYtZ9orGBV5SGOJm4NrB3K1aJar0RfzxC3ikr7Dyc6Qw
qDTBU39CluVIQeuQRgwG3MuSxl7zRERDRilGoKb8uY45JzmxWuKxrfwT/478JuHU
/oTxUFqOl2stKnn7QGTq8z29W+GgBLCXSBxC9epaHM0myFH/FJlniXJfHeytWt0=
-----END CERTIFICATE-----)EOF";
String apikey=APIKEY_secret;
WiFiServer server(80);
WiFiClient clientbefore;
WiFiClientSecure aiclient;
LiquidCrystal lcd(19,18,17,16,26,27);
int ledleft=14;
int ledright=25;
class webpage{
  public:
  String newstring="";
    void Initializehtml(){
      clientbefore.println("HTTP/1.1 200 OK");
      clientbefore.println("Content-type: text/html");
      clientbefore.println();
      File file = LittleFS.open("/index.html" , "r");
      while(file.available()){
        clientbefore.write(file.read());
      }
      file.close();
      clientbefore.stop();
    }
    void Initializecss(){
      clientbefore.println("HTTP/1.1 200 OK");
      clientbefore.println("Content-type: text/css");
      clientbefore.println();
      File file = LittleFS.open("/style.css", "r");
      while(file.available()){
        clientbefore.write(file.read());
      }
      file.close();
      clientbefore.stop();
    }
    void Initializejs(){
      clientbefore.println("HTTP/1.1 200 OK");
      clientbefore.println("Content-type: application/javascript");
      clientbefore.println();
      File file = LittleFS.open("/script.js" , "r");
      while(file.available()){
        clientbefore.write(file.read());
      }
      file.close();
      clientbefore.stop();

    }
    void Initialize_connection_openai(String body){
      aiclient.println("POST /v1beta/models/gemini-3.1-flash-lite:generateContent HTTP/1.1");   
      aiclient.println("Host: generativelanguage.googleapis.com");
      aiclient.println("x-goog-api-key: " + String(apikey));
      aiclient.println("Content-Type: application/json");
      aiclient.println("Content-Length: " + String(body.length()));
      aiclient.println("Connection: close");
      aiclient.println();
    }
};
webpage page;
void setup(){
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("ORBIT");
  LittleFS.begin(true);
  WiFi.begin(ssid,password);
  Serial.println("connecting");
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("CONNECTED!");
  Serial.print("Connected to ");
  Serial.println(WiFi.localIP());
  server.begin();
  aiclient.setCACert(certificate);
  pinMode(ledleft,OUTPUT);
  pinMode(ledright,OUTPUT);
 
}
void loop(){
  WiFiClient client=server.available();
  clientbefore=client;
  if(!client){
    return;
  }
  while(client.available()){
    String request=client.readStringUntil('\r');
    if(request.indexOf("GET / ")!=-1){
      Serial.println("writing html");
      page.Initializehtml();
    }
    else if (request.indexOf("GET /style.css")!=-1){
      Serial.println("Writing css");
      page.Initializecss();
    }
    else if (request.indexOf("GET /script.js")!=-1){
      Serial.println("Writing Js");
      page.Initializejs();
    }
    else if(request.indexOf("GET /movedright")!=-1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU MOVED RIGHT");
      digitalWrite(ledright,HIGH);
      digitalWrite(ledleft,LOW);
      clientbefore.println("HTTP/1.1 200 OK");
      clientbefore.println("Access-Control-Allow-Origin: *");
    }
    else if(request.indexOf("GET /movedleft")!=-1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU MOVED LEFT");
      digitalWrite(ledleft,HIGH);
      digitalWrite(ledright,LOW);
      clientbefore.println("HTTP/1.1 200 OK");
      clientbefore.println("Access-Control-Allow-Origin: *"); 
    }
    if(request.indexOf("GET /chat?msg=")!=-1){
      String response="";
      int start=14;
      int end=request.indexOf(" HTTP/1.1");
      String message=request.substring(start,end);
      message.replace("%20" , " ");
      Serial.println(message);
      File file = LittleFS.open("/request.json","r");
      String temp="";
      while(file.available()){
        char c = file.read();
        temp+=c;
      }
      temp.replace("{{MESSAGE}}" , message);
      if (!aiclient.connect(api, 443)){
      Serial.println("connection to api failed");
      return;
}
      Serial.println("connected to api!");
      page.Initialize_connection_openai(temp);
      aiclient.print(temp);
      Serial.println("response coming");
      while(!aiclient.available()){
        delay(500);
        Serial.print(".");
      }
      while(aiclient.available()){
        char C=aiclient.read();
        response+=C;
      }
      String body;
      JsonDocument doc;
      int begin=response.indexOf("\r\n\r\n");
      body=response.substring(begin+4);
      int position=0;
      String json="";
      while(true){
      int chunksizelineend=body.indexOf("\r\n" , position);
      String hexasize=body.substring(position,chunksizelineend);
      int chunksize=strtol(hexasize.c_str(), NULL , 16);
      if (chunksize==0){
        break;
      }
      int jsonstart=chunksizelineend+2;
      String chunkdata=body.substring(jsonstart,jsonstart+chunksize);
      position=position+jsonstart+chunksize+2;
      json+=chunkdata;
    }
      deserializeJson(doc,json);
      String reply = doc["candidates"][0]["content"]["parts"][0]["text"];   
      Serial.println("\n" + reply);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(reply.substring(0,16));
      lcd.setCursor(0,1);
      lcd.print(reply.substring(16,32));
      aiclient.stop();
   }  
  }
}
