#include "system.h"

//记录系统运行次数
int timer_ticks = 0;

void timer_handler(struct regs *r){
    timer_ticks++;

    if(timer_ticks%18==0){
        puts("hello world\n");
    }
}

//硬件中断0为时钟中断
void timer_install(){
    irq_install_handler(0,timer_handler);
}

//时钟等待
void timer_wait(int ticks){
    unsigned long eticks;
    eticks = timer_ticks +ticks;
    while(timer_ticks < eticks);
}
