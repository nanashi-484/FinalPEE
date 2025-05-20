#include "Global_define.h"

void displayNumber(int tens,int ones,bool tens_dot,bool ones_dot);

void displaySetup(){
      // 設定段控制腳為輸出
    pinMode(segDot, OUTPUT);
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);

    // 設定位數控制腳為輸出
    pinMode(leftDigit, OUTPUT);
    pinMode(rightDigit, OUTPUT);

    // 初始關閉顯示
    digitalWrite(leftDigit, HIGH);  // PNP 電晶體需 LOW 導通
    digitalWrite(rightDigit, HIGH); // 共陽極需低電平開啟
}


void updateDisplay(){
    static unsigned long updateDisplay_lastTime = 0;

    displayNumber(display_currentNumber[1],display_currentNumber[0],display_currentDot[1],display_currentDot[0]);

    // 跑馬燈頻率控制 (約 ˙750ms 切換一次位數)
    if(millis() - updateDisplay_lastTime < 750) return;
    updateDisplay_lastTime = millis();

    if(display_position == 5) display_position = 0;
    else display_position ++ ;

    if(mode == ECHO){
        display_currentNumber[1] = echoText[display_position];
        display_currentNumber[0] = echoText[display_position+1];
        display_currentDot[1] = echoText_dot[display_position];
        display_currentDot[0] = echoText_dot[display_position+1];
    }
    else if(mode == TEMPETURE){
        display_currentNumber[1] = tempText[display_position];
        display_currentNumber[0] = tempText[display_position+1];
        display_currentDot[1] = tempText_dot[display_position];
        display_currentDot[0] = tempText_dot[display_position+1];
    }
    // Serial.print(display_currentNumber[1]);
    // Serial.print(display_currentNumber[0]);
    // Serial.print(display_currentDot[1]);
    // Serial.println(display_currentDot[0]);
}

void setSegments(int number,bool dot) {
    // number = constrain(number, 0, 9);
    byte pattern = digitPattern[number];
    
    // 依編碼設定各段 (注意高位元對應段順序)
    digitalWrite(segDot, !dot);
    digitalWrite(segA, bitRead(pattern, 6)); // A 對應 bit6
    digitalWrite(segB, bitRead(pattern, 5)); // B 對應 bit5
    digitalWrite(segC, bitRead(pattern, 4)); // C 對應 bit4
    digitalWrite(segD, bitRead(pattern, 3)); // D 對應 bit3
    digitalWrite(segE, bitRead(pattern, 2)); // E 對應 bit2
    digitalWrite(segF, bitRead(pattern, 1)); // F 對應 bit1
    digitalWrite(segG, bitRead(pattern, 0)); // G 對應 bit0
}

void displayNumber(int tens,int ones,bool tens_dot,bool ones_dot) {
    static unsigned long display_lastTime = 0;
    static int digitPos = 0;
    
    // 掃描頻率控制 (約 5ms 切換一次位數)
    if(millis() - display_lastTime < 5) return;
    display_lastTime = millis();
  
    // 關閉所有位數
    digitalWrite(leftDigit, HIGH);
    digitalWrite(rightDigit, HIGH);
  
    // 分離十位與個位數
  //  Serial.println(tens);
    // 交替顯示位數
    if(digitPos == 0) {
      setSegments(tens , tens_dot);      // 設定十位數段碼
      digitalWrite(leftDigit, LOW); // 開啟左位數
      digitPos = 1;
    } else {
      setSegments(ones , ones_dot);       // 設定個位數段碼
      digitalWrite(rightDigit, LOW); // 開啟右位數
      digitPos = 0;
    }
}
