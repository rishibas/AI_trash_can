#include <Arduino.h>
#include <ESP32Servo.h>
#include <iostream>
#include <WiFi.h>

const char *ssid = "ESP32_AP";
const char *password = "200312301";

WiFiServer server(8000);

#define DEBUG_LED 2 //IO2に接続

const int servoPin = 14;
const int servoPin2 = 27;

Servo rotateServo; //sorting rotate motor
Servo tiltServo; //drop gate motor

void setup(){
    Serial.begin(115200);
    delay(500);

    Serial.println("[setup] serial started");

    pinMode(DEBUG_LED, OUTPUT);
    digitalWrite(DEBUG_LED, HIGH);

    rotateServo.attach(servoPin);
    tiltServo.attach(servoPin2);

    //Wifiネットワークを作成
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    server.begin(); //サーバーを起動
}

void   ThrowAwayThePlastic(){

    //モーター1を＋90度回転させる．
    for (int pos = 0; pos <= 45; pos += 15)
        rotateServo.write(pos);
    
    delay(100); 
    //モーター2を＋90度数回転させる
    for (int pos = 0; pos <= 90; pos += 30)
        tiltServo.write(pos);

    for (int pos = 90; pos >= 0; pos -= 30)
    tiltServo.write(pos);

    delay(500);

    // //モーター2を－90度に回転させるa
    
    delay(100);

    // //モーター1を－90度に回転させる    
    for (int pos = 45; pos >= 0; pos -= 15)
        rotateServo.write(pos);
}

void    ThrowAwayTheCan(){
    digitalWrite(DEBUG_LED, LOW);
    //モーター1を＋90度回転させる．
    for (int pos = 180; pos >= 90; pos -= 30)
        rotateServo.write(pos);
    
    for (int pos = 90; pos >= 0; pos -= 30)
        tiltServo.write(pos);

    delay(500);

    // //モーター2を－90度に回転させるa
    for (int pos = 90; pos <= 180; pos += 30)
        tiltServo.write(pos);
    
    // //モーター1を－90度に回転させる    
    for (int pos = 0; pos <= 180; pos += 30)
        rotateServo.write(pos);
}

void    ThrowAwayThePaper(){
    digitalWrite(DEBUG_LED, LOW);
    //モーター2を-90度回転させる
    for (int pos = 180; pos >= 90; pos -= 30)
        tiltServo.write(pos);
    
    delay(500);

    //モーター2を90度回転させる．
    for (int pos = 90; pos <= 150; pos += 30)
        tiltServo.write(pos);
}

void    PaperInit(){
    rotateServo.write(180);
    delay(100);
    tiltServo.write(90);
    delay(500);
}

void    PlasticInit(){
    rotateServo.write(0);
    delay(100);
    tiltServo.write(0);
    delay(500);
}

void    CanInit(){
    rotateServo.write(180);
    delay(100);
    tiltServo.write(90);
    delay(500);
}

void    loop(){
    char data;

    WiFiClient client = server.available(); //接続の待機
    if (client){
        Serial.println("New Client");
        while (client.connected()){ //接続されている間はデータの受信を続ける
            if (client.available()){
                digitalWrite(DEBUG_LED, HIGH);
                char request = client.read();
                Serial.println("Received: " + request);
                if (request == 'C')
                    ThrowAwayTheCan();
                else if (request == 'P')
                    ThrowAwayThePlastic();
                if (request == 'K')
                    ThrowAwayThePaper();
                else if (request == 'a')
                    PaperInit();
                else if (request == 'b')
                    PlasticInit();
                else if (request == 'd')
                    CanInit();
                else if (request == 'F'){
                    client.stop();//接続を閉じる
                    Serial.println("Client desconnected.");
                    break;
                }
                delay(500);
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