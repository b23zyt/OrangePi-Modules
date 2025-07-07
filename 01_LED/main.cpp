 #include <stdio.h>
#include <wiringPi.h>

//定义引脚
#define LED_Pin 5 //对应11号引脚

int main()
{
    //pin initialize
    wiringPiSetup();
    //检测初始化引脚是否成功
    if (wiringPiSetup()<0) return 1;
    //配置引脚IO模式为输出模式
    pinMode(LED_Pin,OUTPUT);
    while (1)
    {
        digitalWrite(LED_Pin,1);// 设置LED引脚（LED_Pin）为高电平（点亮LED）
        delay(100);
        digitalWrite(LED_Pin,0);// 设置LED引脚（LED_Pin）为低电平（熄灭LED）
        delay(100);
    }
    return 0;
}