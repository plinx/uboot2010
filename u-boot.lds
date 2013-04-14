OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
 . = 0x00000000;
 . = ALIGN(4);
 .text :
 {
   cpu/arm1176/start.o (.text)
   cpu/arm1176/s3c64xx/cpu_init.o (.text)
          board/samsung/smdk6410/lowlevel_init.o (.text)
          cpu/arm1176/nand_cp.o (.text)
          lib_arm/board.o (.text)
   *(.text)
 }
 . = ALIGN(4);
 .rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }
 . = ALIGN(4);
 .data : { *(.data) }
 . = ALIGN(4);
 .got : { *(.got) }
 __u_boot_cmd_start = .;
 .u_boot_cmd : { *(.u_boot_cmd) }
 __u_boot_cmd_end = .;
 . = ALIGN(4);
 .mmudata : { *(.mmudata) }
 . = ALIGN(4);
 __bss_start = .;
 .bss : { *(.bss) . = ALIGN(4); }
 _end = .;
}
