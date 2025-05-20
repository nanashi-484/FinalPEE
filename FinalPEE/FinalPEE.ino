#include "echo.h"
#include "7_display.h"
#include "temperatrue.h"

void setup() {
  Serial.begin(9600);
  displaySetup();
  echoSetup();
  setupButton();

  // 設定溫度讀取
  pinMode(tempPin, INPUT);

}

void loop() {
  updateDisplay();
  echoCalculate();
  readTemp();
  readButton();
}
