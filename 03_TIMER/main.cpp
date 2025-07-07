#include <iostream>

#include <wiringPi.h>
#include "tim.h"
using namespace std;

int main(){
    timerInit();
    while(1){

    }
    return 0;
}

//run the code
/*
'''bash
cd 03_TIM
cmake -S . -B build
cmake --build build
sudo ./build/tim_test
'''

*/