#include <LiquidCrystal.h>

#define potentPin 14

const int pumpOne = 1000 * 60;

int val;

byte periodWater;
byte counter;
int lightTimeOn;
int lightTimeOff;
int pumpTime;

boolean buttWater;
boolean buttWaterVolume;
boolean buttLightOn;
boolean start;
boolean startFlag;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
    pinMode(10, INPUT_PULLUP); //start
    pinMode(11, INPUT_PULLUP); //buttWater
    pinMode(12, INPUT_PULLUP); //buttWaterVolume
    pinMode(13, INPUT_PULLUP); //buttLightOn
    pinMode(2, OUTPUT);        //light
    pinMode(3, OUTPUT);        //pump

    lcd.begin(16, 2);
}

void loop(){
    start = !digitalRead(10);
    buttWaterVolume = !digitalRead(12);
    buttWater = !digitalRead(11);
    buttLightOn = !digitalRead(13);

    lcd.setCursor(0, 1);

    if(buttWater == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 0, 7);
        constrain(val, 0, 7);
        periodWater = val;
        lcd.print(val);
    }

    if(buttWaterVolume == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 1, 10);
        constrain(val, 1, 10);
        pumpTime = pumpOne * val;
        lcd.print(val);
    }

    if(buttLightOn == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 1, 24);
        constrain(val, 1, 24);
        lightTimeOn = val;
        lightTimeOff = 24 - val;
        lcd.print(val);
    }

    if(start == 1 && startFlag == 0){
        startFlag == 1;
    }
    if(start == 1 && startFlag == 1){
        startFlag == 0;
    }



    if (start == 0 && startFlag == 1){
        digitalWrite(2, HIGH);
        if(counter == periodWater){
            digitalWrite(3, HIGH);
            delay(pumpTime);
            digitalWrite(3, LOW);
            counter++;
        }
        int lightTimeOnB = lightTimeOn * 60 * 60 * 1000 - pumpTime;
        delay(lightTimeOnB);
        digitalWrite(10, LOW);
        int lightTimeOffB = lightTimeOff * 60 * 60 * 1000; 
        delay(lightTimeOffB);
    }
    
}
