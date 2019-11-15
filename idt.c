#include "system.h"

#define NIDT 256

//IDT 结构体
struct idt_entry{
    unsigned short base_low; 
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));
//IDT 指针
struct idt_ptr{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

//idt数组
struct idt_entry idt[NIDT];
struct idt_ptr idtp;

//用于加载idt
extern void idt_load();

//设置idt
void idt_set_gate(unsigned char num,unsigned long base,unsigned short sel,
unsigned char flags){
    idt[num].base_low=(base & 0xFFFF); //中断程序的基地址
    idt[num].base_high = (base >> 16)& 0xFFFF;

    idt[num].sel=sel; //标明内核段
    idt[num].always0 = 0; 
    idt[num].flags =flags;//idt 条目第一位为段是否存在 2-3为Ring 后面为14
}

//安装idt
void idt_install(){
    idtp.limit = (sizeof(struct idt_entry)* NIDT);
    idtp.base = &idt;

    memset(&idt,0,sizeof(struct idt_entry)*NIDT);

    idt_load(); 
}