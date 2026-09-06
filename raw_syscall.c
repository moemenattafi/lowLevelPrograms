#include<sys/syscall.h>
#define SYS_WRITE 1
#define SYS_EXIT 60


static long sys_write(int fd, const char *buf, long count){
	long ret;
	asm volatile (
		"syscall"
		:"=a" (ret)
		: "0" (SYS_WRITE), "D" (fd), "S" (buf), "d" (count)
		: "rcx","r11","memory" 
	);
	return ret;
}


static void sys_exit(int code){
	asm volatile ("syscall"::"a"(SYS_EXIT),"D" (code):);
	__builtin_unreachable();
}

void _start(void){
	const char msg[] = "HEllo my friend\n";
	sys_write(1,msg,sizeof(msg));
	sys_exit(0);
}
