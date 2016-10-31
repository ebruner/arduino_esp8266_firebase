#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST <FIREBASE URL>
#define FIREBASE_AUTH <AUTH TOKEN>
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define SVRPORT 9701
FirebaseArduino FirebaseStream;
int pin13 = 13;

  void blink3() {
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  void startWIFI() {
    delay(100);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.print("\nCONNECTED\n");
    digitalWrite(LED_BUILTIN, LOW);
  }


  void setup() {
    pinMode(pin13, OUTPUT);
    Serial.begin(9600);  
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    digitalWrite(LED_BUILTIN, HIGH);  //turn LED off
    delay(1000);
    // connect to wifi.
    startWIFI();
    Firebase.begin(FIREBASE_HOST);
    Firebase.stream("/scores/latest/score/score");

  }

void loop() {
    if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  if(Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();

     Serial.print("event: ");
     Serial.println(eventType);
     digitalWrite(pin13, HIGH);
     delay(1000);
     digitalWrite(pin13, LOW);
     delay(1000);

    digitalWrite(LED_BUILTIN, LOW);
  }
}
