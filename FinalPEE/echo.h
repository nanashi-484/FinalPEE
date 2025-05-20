#include "Global_define.h"

void echoSetup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

unsigned long echo_lastTime = 0;
void echoCalculate(){
    
    // 掃描頻率控制 (約 3s 讀取一次距離)
    if(millis() - echo_lastTime < 3000) return;
    echo_lastTime = millis();

    long duration;
    static long distance;
  
    // Clear trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Send ultrasonic pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Measure the pulse duration
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance in cm
    distance = duration * 0.034 / 2;

    if(distance >= 100) echoText[1] = distance/100;
    else echoText[1] = 13;

    if(distance >= 10) echoText[2] = (distance/10)%10;
    else echoText[2] = 13;

    echoText[3] = distance%10;
    

    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");
    // Serial.println(echo_lastTime);
}
