#include "echo.h"
#include "7_display.h"

int temp;//溫度

void setup() {
  Serial.begin(9600);
  displaySetup();
  echoSetup();
  // 設定溫度讀取
  pinMode(tempPin, INPUT);

}

void loop() {
  displayNumber(temp/10,temp%10);
  echoCalculate();
  readTemp();
}

void readTemp(){
  temp = analogRead(tempPin)/2;
  // Serial.println(temp);
}
