// 定義七段顯示器各段對應 Arduino 腳位 (請依實際接線修改)
const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;
const int leftDigit = 9;   // 左位數控制腳 (PNP 電晶體基極)
const int rightDigit = 10; // 右位數控制腳 (PNP 電晶體基極)
const int tempPin = A0;

// 共陽極七段顯示器數字編碼 (0=亮, 1=暗)
const byte digitPattern[10] = {
    // ABCDEFG 
    0b0000001, // 0
    0b1111001, // 1 (B+C 亮)
    0b0010010, // 2
    0b0000110, // 3
    0b1001100, // 4
    0b0100100, // 5
    0b0100000, // 6
    0b0001111, // 7
    0b0000000, // 8
    0b0000100  // 9
};



void displaySetup(){
      // 設定段控制腳為輸出
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

void setSegments(int number) {
    number = constrain(number, 0, 9);
    byte pattern = digitPattern[number];
    
    // 依編碼設定各段 (注意高位元對應段順序)
    digitalWrite(segA, bitRead(pattern, 6)); // A 對應 bit6
    digitalWrite(segB, bitRead(pattern, 5)); // B 對應 bit5
    digitalWrite(segC, bitRead(pattern, 4)); // C 對應 bit4
    digitalWrite(segD, bitRead(pattern, 3)); // D 對應 bit3
    digitalWrite(segE, bitRead(pattern, 2)); // E 對應 bit2
    digitalWrite(segF, bitRead(pattern, 1)); // F 對應 bit1
    digitalWrite(segG, bitRead(pattern, 0)); // G 對應 bit0
}

void displayNumber(int tens,int ones) {
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
      setSegments(tens);      // 設定十位數段碼
      digitalWrite(leftDigit, LOW); // 開啟左位數
      digitPos = 1;
    } else {
      setSegments(ones);       // 設定個位數段碼
      digitalWrite(rightDigit, LOW); // 開啟右位數
      digitPos = 0;
    }
}
