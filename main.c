#include "system.h"

unsigned char *memcpy(unsigned char *dest,const unsigned char *src,int count){
    /* 在此处添加代码, 将'src'中count字节的数据复制到'dest'中, 
     *  最后返回'dest' */
    const unsigned char *sp=(const unsigned char*)src;
    unsigned char *dp=dest;
    for (; count != 0;count-- ){
        *dp++=*sp++;
    }
    return dest;
}
unsigned char *memset(unsigned char *dest,unsigned char val,int count){
    /* 在此处添加代码, 将'dest'中的count字节全部设置成值'val', 
     * 最后返回'dest' */
    unsigned char *temp=(unsigned char *)dest;
    for (;count!=0; count--){
        *temp++=val;
    }
    return dest;
}
unsigned short *memsetw(unsigned short *dest,unsigned short val,int count){
    /* 在此处添加代码, 将'dest'中的count双字节设置成值'val', 
     * 最后返回'dest' 
     * 注意'val'是双字节 16-bit*/
    unsigned short *temp=(unsigned char *)dest;
    for (;count!=0; count--){
        *temp++=val;
    }
    return dest;
}
int strlen(const char *str){
    /* 返回字符串的长度
     * 遇到某个字节的值为0x00结束 */
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return 0;
}
/* 我们之后将使用这个函数通过IO端口从设备读取数据, 如键盘等
 * 我们使用内联汇编代码(inline assembly)实现该功能 */
unsigned char inportb(unsigned short _port){
    unsigned char rv;
    __asm__ __volatile__(
        "inb %1, %0" : "=a" (rv) : "dN"(_port)
    );
    return rv;
}
/* 我们将使用这个函数通过I/O端口向设备写数据
 * 用来修改文本模式和光标位置
 * 同样,我们使用内联汇编来实现这个单用C无法实现的功能 */
void outportb(unsigned short _port,unsigned char _data){
    __asm__ __volatile__(
        "outb %1,%0" ::"dN"(_port),"a"(_data)
    );
}
void main(){
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    init_video();
    timer_install();
    keyboard_install();


    __asm__ __volatile__ ("sti");
    puts("hello world");

    for (;;);
}