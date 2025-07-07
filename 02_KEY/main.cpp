#include <iostream>
#include <wiringPi.h>
#include "key.h"
using namespace std;

//定义灯泡引脚
#define LED_Pin 5 //对应11号引脚
//检测按键是否按下标志位
extern int key_num;
int main()
{
    //初始化引脚
    wiringPiSetup();
    //初始化按键
    key_init();
    while (1)
    {
        //检测初始化是否成功
        if (wiringPiSetup()<0) return 1;
        key();
        cout << "按键的值：" << key_num <<endl;
        if (key_num == 1) // 如果按键值为1（表示松开）
        {
            digitalWrite(LED_Pin, HIGH);// 将LED引脚输出设置为高电平，点亮LED
        }
        if (key_num == 0)// 如果按键值为0（表示按下）
        {
            digitalWrite(LED_Pin, LOW);// 将LED引脚输出设置为低电平，熄灭LED
        }
    }
    return 0;
}
