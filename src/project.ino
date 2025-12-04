#include <Arduino.h>
#include <ESP32Servo.h>
#include <iostream>
#include <WiFi.h>
const char *ssid = "ESP32_AP";
const char *password = "200312301";

WiFiServer server(8000);

#define DEBUG_LED 2 //IO2に接続

const int servoPin = 14;

Servo rotateServo; //sorting rotate motor
Servo tiltServo; //drop gate motor

void setup(){
    Serial.begin(115200);
    delay(500);

    Serial.println("[setup] serial started");

    pinMode(DEBUG_LED, OUTPUT);
    digitalWrite(DEBUG_LED, HIGH);
    rotateServo.attach(servoPin);

    //Wifiネットワークを作成
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    server.begin(); //サーバーを起動
}

void loop(){
    char data;

    WiFiClient client = server.available(); //接続の待機
    if (client){
        Serial.println("New Client");
        while (client.connected()){ //接続されている間はデータの受信を続ける
            if (client.available()){
                //String request = client.readStringUntil('\r'); //リクエストの読み込み
                char request = client.read();
                Serial.println("Received: " + request);
                if (request == 'C'){
                    digitalWrite(DEBUG_LED, HIGH);
                    for (int pos = 0; pos <= 180; pos += 10){
                        rotateServo.write(pos);
                        delay(100);
                    }
                }
                else if (request == 'F'){
                    client.stop();//接続を閉じる
                    Serial.println("Client desconnected.");
                    break;
                }
            }
        }
    }
    else {
        // no client — print heartbeat occasionally so user knows MCU is alive
        static unsigned long last = 0;
        if (millis() - last > 2000) {
            last = millis();
            Serial.println("[loop] waiting for client...");
        }
    }
}