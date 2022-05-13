#include "JR60.h"
int Int2String(int num,char *str)
{   int i;
    i=sprintf(str,"%d", num);
 
    return i;
}

//在C语言中，一个字符串结束的标志位是\0,NUL
//以字符串,字符数组初始化赋值，多余部分初始化为0x0
//字符数组在声明时，是没有初始化为全零的

//而用指针声明时，没有指明长度，自然没办法申请空间,更没办法初始化
//字符指针可以用字符串直接或者间接赋值

//另外，用sizeof实际上是求的指针变量的大小，也就是数组声明的长度;
//但是用strlen函数可以求出字符串的有效长度，也就是到\0的长度
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
char* Select_Two(int hard,char* path) {   //盘符和路径可选
    
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