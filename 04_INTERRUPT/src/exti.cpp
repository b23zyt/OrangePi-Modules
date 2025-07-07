#include <iostream>
#include <wiringPi.h>
using namespace std;

#define EIT_PIN 6 //PIN12

int i = 0;
void buttonCallback(){
    i++;
    cout << "Interrupt starts " << i << " times" << endl;
    delay(10); //use timer instead
}

void EIT_init(){
    wiringPiSetup();
    pinMode(EIT_PIN, INPUT);
    pullUpDnControl(EIT_PIN, PUD_UP);
    wiringPiISR(EIT_PIN, INT_EDGE_FALLING, buttonCallback);
}

/*
INT_EDGE_FALLING        falling edge trigger
INT_EDGE_RISING         rising edge trigger
INT_EDGE_BOTH           clock edge trigger
INT_EDGE_SETUP          none
*/