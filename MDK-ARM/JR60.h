#pragma once
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"

char Start[]="A2";
char Pause[]="A3";
char Stop[]="A4";  //ֹͣ
char Former_item[]="A5";
char Next_item[]="A6";
//00001��99999
char* Select_One(int item);  // ���ŵ�ǰ�洢���µ��ļ�



char Stop_play[]="AE";

char AddVoice[]="B0";
char SubVoice[]="B1";

char mode1[]="B4:00";//ȫ��ѭ��
char mode2[]="B4:01";//����ѭ��
char mode3[]="B4:02";//����ֹͣ
char mode4[]="B4:03";//ȫ�����
char mode5[]="B4:04";//Ŀ¼ѭ��
char mode6[]="B4:05";//Ŀ¼���
char mode7[]="B4:06";//Ŀ¼˳��
char mode8[]="B4:07";//˳�򲥷�


//flash Ϊ A8:02+·��,TFΪ01��U��Ϊ00
char* Select_Two(int hard,char* path) ;   //�̷���·����ѡ
char* Set_voice(int voicenum);
char* setmode(int modenum);
char* addvoice();
char* subvoice();
char* StartVoice();
char* PauseVoice();
char* Former();
char* Next();