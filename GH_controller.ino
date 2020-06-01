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

void setup(){
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);

}

void loop(){
    start = !digitalRead(9);
    buttWaterVolume = !digitalRead(10);
    buttWater = !digitalRead(11);
    buttLightOn = !digitalRead(12);

    if(buttWater == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 0, 7);
        constrain(val, 0, 7);
        periodWater = val;
    }

    if(buttWaterVolume == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 1, 10);
        constrain(val, 1, 10);
        pumpTime = pumpOne * val;
    }

    if(buttLightOn == 1){
        val = analogRead(potentPin);
        map(val, 0, 1023, 1, 24);
        constrain(val, 1, 24);
        lightTimeOn = val;
        lightTimeOff = 24 - val;
    }

    if(start == 1 && startFlag == 0){
        startFlag == 1;
    }
    if(start == 1 && startFlag == 1){
        startFlag == 0;
    }



    if (start == 0 && startFlag == 1){
        digitalWrite(10, HIGH);
        if(counter == periodWater){
            digitalWrite(8, HIGH);
            delay(pumpTime);
            digitalWrite(8, LOW);
            counter++;
        }
        int lightTimeOnB = lightTimeOn * 60 * 60 * 1000 - pumpTime;
        delay(lightTimeOnB);
        digitalWrite(10, LOW);
        int lightTimeOffB = lightTimeOff * 60 * 60 * 1000; 
        delay(lightTimeOffB);
    }
    
}