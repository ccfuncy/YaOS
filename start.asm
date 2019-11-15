; 这里是整个操作系统内核的入口

[BITS 32]
global start
start:
    mov esp,_sys_stack      ;这里存储着我们系统栈的地址
    jmp stublet

ALIGN 4
mboot:
    MULTIBOOT_PAGE_ALIGN    equ 1<<0
    MULTIBOOT_MEMORY_INFO   equ 1<<1
    MULTIBOOT_AOUT_KLUDGE   equ 1<<16
    MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS  equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM      equ -(MULTIBOOT_HEADER_MAGIC+MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end


    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd mboot
    dd code
    dd bss
    dd end
    dd start

stublet:
    extern main
    call main
    jmp $


;GDT
global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10   ;0x10为gdt中的偏移地址
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2 ;0x08为代码段偏移
flush2:
    ret
;IDT
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

;ISR 软件中断
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31


;0除以零例外
;1调试异常
;2不可屏蔽中断异常
;3断点异常
;4检测到溢出异常
;5个界外异常
;6无效的操作码异常
;7否协处理器异常
;8双重故障异常
;9协处理器段溢出异常
;10错误的TSS异常
;11段不存在异常
;12堆栈故障异常
;13一般保护故障异常
;14页错误异常
;15未知中断异常
;16协处理器故障异常
;17对齐检查异常（486+）
;18机器检查异常（Pentium / 586 +）
;19到31个保留异常

;除0异常
isr0:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 0
    jmp isr_common_stub
isr1:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 1
    jmp isr_common_stub
isr2:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 2
    jmp isr_common_stub
isr3:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 3
    jmp isr_common_stub
isr4:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 4
    jmp isr_common_stub
isr5:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 5
    jmp isr_common_stub
isr6:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 6
    jmp isr_common_stub
isr7:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 7
    jmp isr_common_stub
isr8:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 8
    jmp isr_common_stub
isr9:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 9
    jmp isr_common_stub

isr10:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 10
    jmp isr_common_stub
isr11:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 11
    jmp isr_common_stub
isr12:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 12
    jmp isr_common_stub
isr13:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 13
    jmp isr_common_stub
isr14:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 14
    jmp isr_common_stub
isr15:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 15
    jmp isr_common_stub
isr16:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 16
    jmp isr_common_stub
isr17:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 17
    jmp isr_common_stub
isr18:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 18
    jmp isr_common_stub
isr19:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 19
    jmp isr_common_stub

isr20:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 20
    jmp isr_common_stub
isr21:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 21
    jmp isr_common_stub
isr22:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 22
    jmp isr_common_stub
isr23:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 23
    jmp isr_common_stub
isr24:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 24
    jmp isr_common_stub
isr25:
    cli ;禁用中断并防止IRQ触发
    push byte 0 
    push byte 25
    jmp isr_common_stub
isr26:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 26
    jmp isr_common_stub
isr27:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 27
    jmp isr_common_stub
isr28:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 28
    jmp isr_common_stub
isr29:
    cli ;禁用中断并防止IRQ触发
    push byte 0
    push byte 29
    jmp isr_common_stub

isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub


extern fault_handler
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

;IRQ 硬件中断
;主PCI 处理 可编程中断控制器
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7

;从PCI处理
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
    cli
    push byte 0
    push byte 32
    jmp  irq_common_stub

irq1:
    cli
    push byte 0
    push byte 33
    jmp  irq_common_stub

irq2:
    cli
    push byte 0
    push byte 34
    jmp  irq_common_stub

irq3:
    cli
    push byte 0
    push byte 35
    jmp  irq_common_stub

irq4:
    cli
    push byte 0
    push byte 36
    jmp  irq_common_stub

irq5:
    cli
    push byte 0
    push byte 37
    jmp  irq_common_stub

irq6:
    cli
    push byte 0
    push byte 38
    jmp  irq_common_stub

irq7:
    cli
    push byte 0
    push byte 39
    jmp  irq_common_stub

irq8:
    cli
    push byte 0
    push byte 40
    jmp  irq_common_stub

irq9:
    cli
    push byte 0
    push byte 41
    jmp  irq_common_stub

irq10:
    cli
    push byte 0
    push byte 42
    jmp  irq_common_stub

irq11:
    cli
    push byte 0
    push byte 43
    jmp  irq_common_stub

irq12:
    cli
    push byte 0
    push byte 44
    jmp  irq_common_stub

irq13:
    cli
    push byte 0
    push byte 45
    jmp  irq_common_stub

irq14:
    cli
    push byte 0
    push byte 46
    jmp  irq_common_stub

irq15:
    cli
    push byte 0
    push byte 47
    jmp  irq_common_stub

extern irq_handler

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

SECTION.bss
    resb 8192

_sys_stack:
