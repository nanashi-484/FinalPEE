const int trigPin = 11;
const int echoPin = 12;

unsigned long echo_lastTime = 0;

void echoSetup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void echoCalculate(){
    long duration;
    static long distance;
    // 掃描頻率控制 (約 500ms 讀取一次距離)
    if(millis() - echo_lastTime < 500) return;
    
    if(millis() - echo_lastTime < 510){
        // Clear trigger pin
        digitalWrite(trigPin, LOW);
        return;
    }
    
    // delayMicroseconds(2);
    
    // Send ultrasonic pulse
    if(millis() - echo_lastTime < 520){
        digitalWrite(trigPin, HIGH);
        return;
    }
    // digitalWrite(trigPin, HIGH);
    // delayMicroseconds(10);

    if(millis() - echo_lastTime < 530){
        digitalWrite(trigPin, LOW);
        return;
    }
    // digitalWrite(trigPin, LOW);
    
    // Measure the pulse duration
    if(millis() - echo_lastTime < 537){
        duration = pulseIn(echoPin, HIGH);
        return;
    }
    // duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance in cm
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println(echo_lastTime);

    echo_lastTime = millis();
}
