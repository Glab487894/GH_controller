#include <LiquidCrystal.h>

#define potentPin 14 //define port for potentiometer


const int pumpOne = 1000 * 60; //define time of working for pump to move 1 liter of water

int val; //vall from potentiometer

byte periodWater; // How often must work water pump
byte counter;   
int lightTimeOn; // How long light must be On
int lightTimeOff; // How long light must be Off
int pumpTime; //How long the pump mast work

//the switch for changing modes
boolean buttWater; //period of watering
boolean buttWaterVolume; //volume of watering
boolean buttLightOn; //light

//start button and flag
boolean start; 
boolean startFlag;

//define ports for lcd 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
    //install the pinmodes
    pinMode(10, INPUT_PULLUP); //start
    pinMode(11, INPUT_PULLUP); //buttWater
    pinMode(12, INPUT_PULLUP); //buttWaterVolume
    pinMode(13, INPUT_PULLUP); //buttLightOn
    pinMode(2, OUTPUT);        //light
    pinMode(3, OUTPUT);        //pump

    //start lcd
    lcd.begin(16, 2);
}

void loop(){

    //assign values ​​to variables from digitalRead
    start = !digitalRead(10);
    buttWaterVolume = !digitalRead(12);
    buttWater = !digitalRead(11);
    buttLightOn = !digitalRead(13);

    //install the position of Cursor
    lcd.setCursor(0, 1);

    // tool to set user watering period
    if(buttWater == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 0, 7);
        constrain(val, 0, 7);
        periodWater = val;
        lcd.print(val);
    }

    // tool to set user watering valume
    if(buttWaterVolume == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 1, 10);
        constrain(val, 1, 10);
        pumpTime = pumpOne * val;
        lcd.print(val);
    }

    // tool to set user light
    if(buttLightOn == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 1, 24);
        constrain(val, 1, 24);
        lightTimeOn = val;
        lightTimeOff = 24 - val;
        lcd.print(val);
    }

    //block of changing flags of sistem work status
    if(start == 1 && startFlag == 0){
        startFlag == 1;
    }
    if(start == 1 && startFlag == 1){
        startFlag == 0;
    }

    //the main block
    if (start == 0 && startFlag == 1){
        digitalWrite(2, HIGH); //turn light On
        //pump work
        if(counter == periodWater){
            digitalWrite(3, HIGH);
            delay(pumpTime);
            digitalWrite(3, LOW);
            counter++; //increase the value of the time counter
        }
        int lightTimeOnB = lightTimeOn * 60 * 60 * 1000 - pumpTime; //chage the lightTimeOn from hours to millisecond
        delay(lightTimeOnB);
        digitalWrite(10, LOW);
        int lightTimeOffB = lightTimeOff * 60 * 60 * 1000; //chage the lightTimeOff from hours to millisecond
        delay(lightTimeOffB);
    }
    
}
