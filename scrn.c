#include "system.h"

//文本指针
unsigned short *textmemptr; 
//属性
/*
vga大小25*80
Value	Color	Value	Color
0	BLACK	8	DARK GREY
1	BLUE	9	LIGHT BLUE
2	GREEN	10	LIGHT GREEN
3	CYAN	11	LIGHT CYAN
4	RED	12	LIGHT RED
5	MAGENTA	13	LIGHT MAGENTA
6	BROWN	14	LIGHT BROWN
7	LIGHT GREY	15	WHITE
*/
int attrib = 0x0F;//0x0f白色
//x和y的坐标
int csr_x=0,csr_y=0;

/*屏幕滚动*/
void scroll(void){
    unsigned blank,temp;
    //0x20是空格 下面的
    blank = 0x20 | (attrib << 8);
    //向下滑动，如果大于了25行，我们将24行向上移动一行
    if(csr_y>=25){
        temp =csr_y-25+1;
        memcpy(textmemptr,textmemptr+temp*80,(25-temp)*80*2);

        //最后一行填充空格
        memsetw(textmemptr+(25-temp)*80,blank,80);
        csr_y=25-1;
    }
}
/* 更新光标位置: 在最后一个字符下添加一条闪烁的下划线 */
void move_csr(void){
    unsigned temp;

    /* 虚拟坐标与物理地址转换的公式:
     * Index = [(y * width) + x] */
    temp = csr_y * 80 + csr_x;

    /* 往VAG的CRT控制寄存器内发送命令, 设置光标的高地址和低地址
     * 想了解更多细节, 需要查找VGA编程文档 */
    outportb(0x3D4, 14);  // 设置光标高8位地址,颜色
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);  // 设置光标低8位地址，内容
    outportb(0x3D5, temp);
}
//清空屏幕
void cls(){
    unsigned blank;
    int i;

    /*空格*/
    blank = 0x20 | (attrib << 8);
    //填充
    for (i = 0; i < 25; i++){
        memsetw(textmemptr+i*80,blank,80);
    }
    //更新光标坐标
    csr_x=0;
    csr_y=0;
    move_csr();
}
//打印单个字符
void putch(unsigned char C){
    unsigned short *where;
    unsigned att = attrib << 8;

    //处理backspace键，光标回退一格
    if(C == 0x08){
        if(csr_x !=0){
            csr_x--;
        }
    }else if (C == 0x09){ //处理tab键
        csr_x = (csr_x + 8) & ~(8-1);
    }else if (C == '\r'){ //处理回车键, 将光标回退到行首
        csr_x = 0;
    }else if (C == '\n'){ //处理换行, 光标移动到下一行行首
        csr_x=0;
        csr_y++;
    }else if (C >= ' '){ //处理其他字符
        where = textmemptr +(csr_y*80+csr_x);
        *where = C | att;
        csr_x++;
    }
    /* 当光标到达屏幕又边界, 移动到下一行行首 */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* 在需要的时候滚动屏幕, 并移动光标 */
    scroll();
    move_csr();
}
//打印字符串
void puts(unsigned char *text){
    int i;
    for (i = 0; i < strlen(text); i++){
        putch(text[i]);
    }
}
//设置前景色和背景色
void settextcolor(unsigned char forecolor,unsigned char backcolor){
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

//设置文本模式VGA指针, 并清屏
void init_video(void){
    //0xB800为VGA位置
    textmemptr = (unsigned short *)0xB800;
    cls();
}
