#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid     = "EnGeniusE37C98"; //change this to your SSI from Your Wireless LAN Netowork
const char* password = "elecnet123"; //change this to your PASSWORD from Your Wireless LAN Netowork
//ตรงนี้ ต้องระวังไม่ต้องใส่ https นะครับ ให้ใช้ http เฉยๆ 
const char* host = "http://maew-linebot-php.herokuapp.com/bot.php";//change this to your linebot server ex.http://numpapick-linebot.herokuapp.com/bot.php
#define APPID   "maewbot"     //change this to your APPID from netpie ตรงนี้ ใช้ของเว็บ netpie
#define KEY     "R6Qxt5GF4FLe10S"     //change this to your KEY from netpie ตรงนี้ ใช้ของเว็บ netpie
#define SECRET  "LCvB4UmI5H99ShPKh4ypUXhP9"     //change this to your SECRET from netpie ตรงนี้ ใช้ของเว็บ netpie

#define ALIAS   "NodeMCU1" //set name of drvice
#define TargetWeb "switch" //set target name of web

WiFiClient client;
String uid = "";
String text_in = "";
int timer = 0;
MicroGear microgear(client);
void beep(int i){
    int cnt = 0;
     for(cnt=0;cnt<=i;cnt++){
        digitalWrite(LED_BUILTIN, HIGH);   
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
     }
}

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) { // 
    Serial.print("\n Incoming message -->");
    
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    text_in = (char *)msg;
    if(*(char *)msg == '1'){
        digitalWrite(LED_BUILTIN, LOW);   // LED on
        Serial.println("\n=>");Serial.print("LED On1\n");Serial.print(text_in);
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
          send_json("ESP LED ON");
    }else if(*(char *)msg ==  'On'){
        digitalWrite(LED_BUILTIN, LOW);   // LED on
        Serial.println("=>");Serial.print("LED On2\n");
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }else if(*(char *)msg == '0'){
        digitalWrite(LED_BUILTIN, HIGH);  // LED off
        Serial.println("=>");Serial.print("LED Off1\n");
    //  microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP LED OFF");
    }else if(*(char *)msg ==  'OFF' ){
        digitalWrite(LED_BUILTIN, HIGH);   // LED off
        Serial.println("=>");Serial.print("LED Off2\n");
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_OFF");
        send_json("ESP LED OFF");
    }else if(text_in == "m1" || "s1"){
        beep(5);
        Serial.println("=>");Serial.print("Function 1 Show Temp\n");
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }else if(text_in == "m2"|| "s2"){
        beep(3);
        Serial.println("=>");Serial.print("Function 2 Show image\n");
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }else if(text_in == "m3" || "s3"){
        beep(5);
        Serial.println("=>");Serial.print("Function 3 on lamp \n");
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }else if(text_in == "m4"|| "s4"){
        beep(3);
        Serial.println("=>");Serial.print("Function 4 off LAmp \n");
       // microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setName(ALIAS);
}


void setup() {
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    pinMode(LED_BUILTIN, OUTPUT);
  
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
    digitalWrite(LED_BUILTIN, HIGH);   // LED on
}

void send_json(String data){
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["ESP"] = data;
 
    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
    values.add(20); //Add value to array
    values.add(21); //Add value to array
    values.add(23); //Add value to array
 
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin(host);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
}
void loop() {
    if (microgear.connected()) {
        Serial.print("."); 
        microgear.loop();
        timer = 0;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID); 
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
