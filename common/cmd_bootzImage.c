#include <common.h>
#include <command.h> 

#ifdef CONFIG_CMD_BOOTZIMAGE 
#define LINUX_PAGE_SHIFT 12
#define LINUX_PAGE_SIZE (1<<LINUX_PAGE_SHIFT)
#define LINUX_MACHINE_ID  1099		//根据平台修改

void do_bootzImage(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int i;
	u32 addr;
	char *cmdline = getenv("bootargs");
	void(*run)(int zero, int arch);
	struct param_struct *params = (struct param_struct*)0x20000100;
	//这里要注意根据平台的不同改,一般 约定俗成是内存首地址+100dex

	if(argc < 2){
		addr = load_addr; 	//默认加载地址
	}
	else{
		addr = simple_strtoul(argv[1], NULL, 16);
	}

	for(i=0; i<(sizeof(struct param_struct)>>2); i++){
		((u32 *)params)[i] = 0;
	}

	params->u1.s.page_size = LINUX_PAGE_SIZE;
	params->u1.s.nr_pages = (0x04000000 >> LINUX_PAGE_SHIFT);

	memcpy(params->commandline, cmdline, strlen(cmdline));
	run = (void(*)(int, int))addr;
	printf("start kernel.../n");
	run(0, LINUX_MACHINE_ID);

}

U_BOOT_CMD( bootzImage, 2, 1, do_bootzImage,"bootzImage --boot zImage from ram./n","[addr] boot zImage directoly."); 

#endif
