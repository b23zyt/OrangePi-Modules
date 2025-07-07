#include "wiringPi.h"
#include <stdio.h>
#include "key.h"

//定义按键引脚
#define KEY_Pin 7 //对应13号引脚

int key_num = 2;

void key_init()
{
    pinMode(KEY_Pin, INPUT);// 设置KEY_Pin（引脚7）为输入模式，用于读取按键状态
    pullUpDnControl(KEY_Pin, PUD_UP);// 启用上拉电阻，确保按键未按下时电平为高
}

void key()
{
    if (digi talRead(KEY_Pin) == 0)// 如果按键被按下（引脚电平为低），更新key_num为0，表示按键按下状态
    {
        key_num = 0;
        delay(100);
    }
    if (digitalRead(KEY_Pin) == 1) // 如果按键未按下（引脚电平为高），更新key_num为1，表示按键未按下
    {
        key_num = 1;
        delay(100);
    }
}