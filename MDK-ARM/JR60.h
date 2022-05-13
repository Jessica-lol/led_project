#pragma once
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"

char Start[]="A2";
char Pause[]="A3";
char Stop[]="A4";  //停止
char Former_item[]="A5";
char Next_item[]="A6";
//00001－99999
char* Select_One(int item);  // 播放当前存储器下的文件



char Stop_play[]="AE";

char AddVoice[]="B0";
char SubVoice[]="B1";

char mode1[]="B4:00";//全部循环
char mode2[]="B4:01";//单曲循环
char mode3[]="B4:02";//单曲停止
char mode4[]="B4:03";//全盘随机
char mode5[]="B4:04";//目录循环
char mode6[]="B4:05";//目录随机
char mode7[]="B4:06";//目录顺序
char mode8[]="B4:07";//顺序播放


//flash 为 A8:02+路径,TF为01，U盘为00
char* Select_Two(int hard,char* path) ;   //盘符和路径可选
char* Set_voice(int voicenum);
char* setmode(int modenum);
char* addvoice();
char* subvoice();
char* StartVoice();
char* PauseVoice();
char* Former();
char* Next();