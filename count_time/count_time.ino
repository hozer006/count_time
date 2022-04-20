#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define FIREBASE_HOST "https://donwtime-86bcd-default-rtdb.firebaseio.com/" //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "d52Xevx6iFeLYM08pF1exB9seQdjZESgKDMAzS06" //--> Your firebase database secret code.

#define WIFI_SSID "Jandahan" 
#define WIFI_PASSWORD "0963711131"

const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;
FirebaseData firebaseData;

String GAS_ID = "AKfycbwkzJU7u6hOglWcl22vFCx8DbBgY5dni0olT9DTzVzgG61Lf8dS_niCChIQJYx_RekW";

long time_now;
long time_before;
long time_after;
int count;
bool val;
void setup() {
   pinMode(D0,INPUT);
   Serial.begin(115200);
   Firebase_connection();
   client.setInsecure();

}

void Firebase_connection() {
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
 WiFi.status() != WL_CONNECTED;
 time_now = millis();
 int num = digitalRead(D0);
 if (val) {
      val = false;
    Firebase.setInt(firebaseData, "L1/Link", 1);
    }else{
      val = true;
    Firebase.setInt(firebaseData, "L1/Link", 0);
  }
 if(num == 0){
  if(time_after > 0){
      hours(time_after);
      count = count+1;
      Firebase.setInt(firebaseData,"L1/Count",  count);
      Serial.print("Count : ");
      Serial.println(count);
      time_after = 0;
    }
  time_before = time_now;
 }
 else{
  time_after = time_now-time_before;
  Serial.println(time_after);
 }
  
 delay(1000);
}

void hours(long times){
   times = times/1000;
   int times_hours = times/3600;
   int times_minutes = (times-(times_hours*3600))/60;
   int times_seconds = (times-((times_minutes*60)+(times_hours*3600)));
   Serial.print(times_hours);
   Firebase.setInt(firebaseData,"L1/Hours",  times_hours);
   Serial.print(" hours ");
   Serial.print(times_minutes);
   Firebase.setInt(firebaseData,"L1/Minutes",  times_minutes);
   Serial.print(" minutes ");
   Serial.print(times_seconds);
   Firebase.setInt(firebaseData,"L1/Seconds",  times_seconds);
   Serial.println(" seconds");
   if (!client.connect(host, httpsPort)) {Serial.print("fall ");}
    String url = "/macros/s/" + GAS_ID + "/exec?Count=" + count + "&Hours=" + times_hours + "&Minutes=" + times_minutes + "&Secondes=" + times_seconds;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: BuildFailureDetectorESP8266\r\n" +
                 "Connection: close\r\n\r\n");
}

//void sendData() {
//  
////  else{
////    Serial.print("fall ");  
////  }
//}
