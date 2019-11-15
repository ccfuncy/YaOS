#ifndef __SYSTEM_H
#define __SYSTEM_H
/* MAIN.C */
//复制
extern unsigned char *memcpy(unsigned char *dest,const unsigned char *src,int count);
//字符串值单字节设置
extern unsigned char *memset(unsigned char *dest,unsigned char val,int count);
//字符串值双字节设置
extern unsigned short *memsetw(unsigned short *dest,unsigned short val,int count);
//字符串长度
extern int strlen(const char *str);
//从I/O端口读取数据
extern unsigned char inportb(unsigned short _port);
//向I/O端口写入数据
extern void outportb(unsigned short _port,unsigned char _data);

/**VGA有关函数**/
//清空屏幕
extern void cls();
//打印单个字符
extern void putch(unsigned char C);
//使用putch来打印字符串
extern void puts(unsigned char *str);
//设置前景色和背景色
extern void settextcolor(unsigned char forecolor,unsigned char backcolor);
//设置文本模式VGA指针, 并清屏
extern void init_video();

/**GDT 全局描述表**/
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/**IDT 中断描述表**/
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/**ISR 中断请求处理**/
//堆栈结构
struct regs{
    unsigned int gs, fs, es, ds; 
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};
extern void isrs_install();

/**IRQ 中断请求处理**/
extern void irq_install();
extern void irq_install_handler();
extern void irq_uninstall_handler();

/**PIT 可编程间隔计时器**/
extern void timer_wait(int ticks);
extern void timer_install();

/**keyboard 键盘**/
extern void keyboard_install();
#endif