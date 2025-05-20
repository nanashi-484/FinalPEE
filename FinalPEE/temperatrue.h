#include "Global_define.h"

void readTemp(){
    temp = analogRead(tempPin)/2;
    // Serial.println(temp);

    tempText[1] = temp/10;

    tempText[2] = temp - int(temp/10)*10 ;

    tempText[3] = temp*10 - int(temp)*10 ;
}

void setupButton(){
    pinMode(Button , INPUT_PULLUP);
}

void readButton(){
    static bool lastButton = 0;
    if(lastButton==0 && digitalRead(Button)==1){
        if(mode == ECHO) mode = TEMPETURE;
        else mode = ECHO;
        lastButton=1;
    }
    else if(lastButton==1 && digitalRead(Button)==0) {
        lastButton=0;
    }
}
