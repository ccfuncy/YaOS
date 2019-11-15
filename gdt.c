#include "system.h"
//gdt描述符数量
#define NGDT 3
//gdt 选择子
#define SEL_NULL    0x0 // NULL段
#define SEL_KCODE   0x1 // 内核代码段
#define SEL_KDATA   0x2 // 内核数据段
//寻址范围
#define LIMIT_SIZE  0xFFFFFFFF //寻址范围

#define GDT_GR  0x8     // 页面粒度 page granularity, limit in 4k blocks
#define GDT_SZ  0x4     // 大小位 size bt, 32 bit protect mode


//gdt索引结构  __attribute__((packed))用于防止编译器优化对齐
struct gdt_entry{
    unsigned short limit_low;//寻址最大范围
    unsigned short base_low;//基址
    unsigned char base_middle;
    unsigned char access;//访问权限 1 3
    unsigned char granularity;//段界限粒度 0 1
    unsigned char base_high;
}__attribute__((packed));

//GDTR指针 48位
struct gdt_ptr{
    unsigned short limit;//16位表界限
    unsigned int base;//32位基地址
}__attribute__((packed));

// 声明包含3个索引的GDT和GDTR指针gp 
struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush();
/* 在全局描述符表中设置描述符 */
void gdt_set_gate(int num,unsigned long base,
unsigned long limit,unsigned char access,unsigned char gran){
    /* 设置描述符基地址 */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* 设置描述符边界 */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* 最后，设置粒度和访问标志 */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;

}
 /*设置GDTR指针, 设置GDT的3个索引条码
 * 最后调用汇编中的gdt_flush告诉处理器新GDT的位置
 * 并跟新新的段寄存器 */
void gdt_install(){
    gp.limit=(sizeof(struct gdt_entry) * NGDT) - 1;
    gp.base = &gdt;

    //NULL描述符
    gdt_set_gate(SEL_NULL , 0, 0, 0, 0);
    gdt_set_gate(SEL_KCODE, 0,LIMIT_SIZE,0X9A,GDT_GR | GDT_SZ);
    gdt_set_gate(SEL_KDATA, 0,LIMIT_SIZE, 0x92, GDT_GR | GDT_SZ);

    /* 清除旧的GDT安装新的GDT */
    gdt_flush();
}