#include "JR60.h"
int Int2String(int num,char *str)
{   int i;
    i=sprintf(str,"%d", num);
 
    return i;
}

//��C�����У�һ���ַ��������ı�־λ��\0,NUL
//���ַ���,�ַ������ʼ����ֵ�����ಿ�ֳ�ʼ��Ϊ0x0
//�ַ�����������ʱ����û�г�ʼ��Ϊȫ���

//����ָ������ʱ��û��ָ�����ȣ���Ȼû�취����ռ�,��û�취��ʼ��
//�ַ�ָ��������ַ���ֱ�ӻ��߼�Ӹ�ֵ

//���⣬��sizeofʵ���������ָ������Ĵ�С��Ҳ�������������ĳ���;
//������strlen������������ַ�������Ч���ȣ�Ҳ���ǵ�\0�ĳ���
    char select[8]="A7:000\0\0";
    char num[5]="";

char* Select_One(int item){
    int lenofnum;
    lenofnum=Int2String(item,num);
    if(lenofnum==1){select[6]='0';select[7]=num[0];}
    else if(lenofnum==2){select[6]=num[0];select[7]=num[1];}
    return select;
}

char send[20]="A8:0";
char* Select_Two(int hard,char* path) {   //�̷���·����ѡ
    
    send[4]=hard+'0';
    for(int i=0;i<strlen(path);i++)send[5+i]=path[i];
    return send;
}
char voice[2]="";
char* Set_voice(int voicenum){
   Int2String(voicenum,voice);
   return voice; 
}
char mode[2];
char* setmode(int modenum){
    
     Int2String(modenum,mode);
    return mode;
}
char* addvoice(){
     return AddVoice;
}
char* subvoice(){
     return SubVoice;
}
char* StartVoice(){
     return  Start;
}
char* PauseVoice(){
     return Pause;
}
char* Former(){
     return Former_item;
}
char* Next(){
     return Next_item;
}