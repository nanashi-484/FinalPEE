const int trigPin = 11;
const int echoPin = 12;

unsigned long echo_lastTime = 0;

void echoSetup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void echoCalculate(){
    
    // 掃描頻率控制 (約 500ms 讀取一次距離)
    if(millis() - echo_lastTime < 500) return;
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

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println(echo_lastTime);
}
