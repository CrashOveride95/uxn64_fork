ENTRY(_start)

STACK_SIZE = 8K;

MEMORY {
    rom (R) : ORIGIN = 0, LENGTH = 64M
    ram (RWX) : ORIGIN = 0x80000400, LENGTH = 4M - 0x400
}

SECTIONS {
    .header : {
        LONG(0x80371240)
        LONG(0x0000000f)
        LONG(0x80000400)
        LONG(0x0000144c)
        . = 0x1000;
    } >rom

    .text : {
        _text_start = .;
        *(.text.entry)
        *(.text .text.*)
        *(.rodata .rodata.*)
        *(.data .data.*)
        _text_end = .;
    } >ram AT>rom

    .bss (NOLOAD) : ALIGN(16) {
        _bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        *(.scommon .scommon.*)
        _bss_end = .;
    } >ram

    .stack (NOLOAD) : ALIGN(16) {
        . += STACK_SIZE;
        . = ALIGN(8);
        _boot_stack = .;
        _main_thread_stack = .;

        . += STACK_SIZE;
        . = ALIGN(8);
        _audio_thread_stack = .;

        . += STACK_SIZE;
        . = ALIGN(8);
        _idle_thread_stack = .;
    } >ram

    /DISCARD/ : {
        *(*)
    }
}
