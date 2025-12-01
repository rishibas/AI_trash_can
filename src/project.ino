#include <Arduino.h>
#include <ESP32Servo.h>
#include <iostream>

#define DEBUG_LED 2 //IO2に接続

const int servoPin = 23;

Servo rotateServo; //sorting rotate motor
Servo tiltServo; //drop gate motor

void setup(){
    Serial.begin(115200);
    pinMode(DEBUG_LED, OUTPUT);
    rotateServo.attach(servoPin);
}

void loop(){
    char data;

    // for (int pos = 0; pos <= 180; pos++){
    //     rotateServo.write(pos);
    //     delay(100);
    // }
    // delay(500);
    // for (int pos = 180; pos >= 0; pos--){
    //     rotateServo.write(pos);
    //     delay(100);
    // }
    digitalWrite(DEBUG_LED, HIGH);
    if (Serial.available() > 0){
        digitalWrite(DEBUG_LED, LOW);
        data = Serial.read();
        if (data == '1'){
            // Echo for debug so host can confirm receipt
            for (int pos = 0; pos <= 180; pos++){
                rotateServo.write(pos);
                delay(80);
            }
        }
    }
    delay(300);
    digitalWrite(DEBUG_LED, HIGH);
}