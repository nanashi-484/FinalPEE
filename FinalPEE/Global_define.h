#ifndef VALUE
#define VALUE

enum Mode {
    ECHO,
    TEMPETURE
};

Mode mode = TEMPETURE;

// 定義七段顯示器各段對應 Arduino 腳位 (請依實際接線修改)
const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;
const int segDot = 13;
const int leftDigit = 9;   // 左位數控制腳 (PNP 電晶體基極)
const int rightDigit = 10; // 右位數控制腳 (PNP 電晶體基極)
const int tempPin = A0;

const int Button = A5;

// 共陽極七段顯示器數字編碼 (0=亮, 1=暗)
const byte digitPattern[14] = {
    // Dot ABCDEFG 
    0b0000001, // 0
    0b1111001, // 1 (B+C 亮)
    0b0010010, // 2
    0b0000110, // 3
    0b1001100, // 4
    0b0100100, // 5
    0b0100000, // 6
    0b0001111, // 7
    0b0000000, // 8
    0b0000100, // 9
    0b0011100, // o
    0b0110001, // C
    0b1101010, // n
    0b1111111  // NULL
};

const int trigPin = 11;
const int echoPin = 12;

float temp;//溫度

int tempText[7] = {13,0,0,0,10,11,13};
bool tempText_dot[7] = {0,0,1,0,0,0,0};
int echoText[7] = {13,0,0,0,11,12,13};
bool echoText_dot[7] = {0,0,0,0,0,0,0};

int display_position = 0; // 0~5

int display_currentNumber[2];
bool display_currentDot[2];

#endif
