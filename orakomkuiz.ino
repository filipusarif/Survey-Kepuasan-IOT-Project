#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif
#define push1 15
#define push2 2
#define push3 0
#define led1  5
#define led2  18
#define led3  19

const char *ssid = "HEHE";  //Nama Wifi
const char *password = "11223344"; // pass wifi

bool presed = 0;

int data1;
int data2;
int data3;



void setup() {
    // Setup esp32s
    delay(1000);
    Serial.begin(115200);
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);
  
    WiFi.begin(ssid, password);
    Serial.println("");
  
    Serial.print("Connecting");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  
    pinMode(push1, INPUT_PULLUP);
    pinMode(push2, INPUT_PULLUP);
    pinMode(push3, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    
}

void loop() {
  bool state1 = digitalRead(push1);
  bool state2 = digitalRead(push2);
  bool state3 = digitalRead(push3);
  
  // code pushbutton & led Start
  while(state1 == presed){
    Serial.println(data1 += 1);
    digitalWrite(led1, HIGH);
    kirim();
    digitalWrite(led1, LOW);
    delay(1000);
    break;
  } 
  
  while(state2 == presed){
    Serial.println(data2 += 1);
    digitalWrite(led2, HIGH);
    kirim();
    digitalWrite(led2, LOW);
    delay(1000);
    break;
  } 
  
  while(state3 == presed){
    Serial.println(data3 += 1);
    digitalWrite(led3, HIGH);
    kirim();
    digitalWrite(led3, LOW);
    delay(1000);
    break;
  }
  
  //  Code pushbutton & led End
}





void kirim() {
  
  String postData = (String)"data1=" + data1 + "&data2=" + data2
                    + "&data3=" + data3;
                    

  HTTPClient http;
  http.begin("http://192.168.43.222/orakom/api.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  auto httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.println(postData);
  Serial.println(payload);
  
  http.end();
}
