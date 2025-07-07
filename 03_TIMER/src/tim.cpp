#include "signal.h"
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "tim.h"
using namespace std;

int i = WAIT_TIME;
void signalHandler(int signum){
    i++;
    cout << "Program starts" << i << " s" << endl;

    //close the timer by re initialize:
    if(i >= 5){
        struct itimerval timerHandler;
        timerHandler.it_interval.tv_sec = 0;
        timerHandler.it_interval.tv_usec = 0;
        timerHandler.it_value.tv_sec = 0;
        timerHandler.it_value.tv_usec = 0;
        
        if(setitimer(ITIMER_REAL, &timerHandler, NULL) == -1){
            perror("TIM_CLOSE ERROR");
            exit(-1);
        }else{
            perror("TIM_CLOSE SUCCESS");
        }
    }

    //close the timer by remove the connection of with the timer
    if(i > 5){
        signal(SIGALRM, SIG_IGN);
        cout << "Timer Closed" << endl;
    }
}

void timerInit(){
    struct itimerval timerHandler;
    timerHandler.it_value.tv_sec = WAIT_TIME; //the timer is triggered after the program runs for 3 seconds
    timerHandler.it_value.tv_usec = 0;

    timerHandler.it_interval.tv_sec = 1; //the timer is triggered in every 1 second
    timerHandler.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &timerHandler, NULL) == -1){
        perror("TIM_INIT ERROR");
        exit(-1);
    }else{
        perror("TIM_INIT SUCCESS");
    }

    //SIGALRM is the signal send when the timer expires
    //Call signalHandler() when timer expires
    signal(SIGALRM, signalHandler);
}