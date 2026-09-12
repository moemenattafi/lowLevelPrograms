#include<stdio.h>
#include<sys/prctl.h>
#include<linux/filter.h>
#include<linux/audit.h>
#include<stddef.h>
#include<unistd.h>
#include<linux/seccomp.h>

int main(){
	printf("Before seccomp: can Write To stdout\n");
	//Installing a seccomp filter that only allows write and exit group
	struct sock_filter filter[] = {
		//load syscall number into accumulator
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, offsetof(struct seccomp_data,nr)),
		//Allow write syscall (1)
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K,1,0,1),
		BPF_STMT(BPF_RET + BPF_K , SECCOMP_RET_ALLOW),
		//Allow exit syscall (231)
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K,231,0,1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		//Kill everything else
		BPF_STMT(BPF_RET+BPF_K,SECCOMP_RET_KILL_PROCESS),
	};

	struct sock_fprog prog = {
		.len = sizeof(filter) / sizeof(filter[0]),
		.filter = filter,
	};

	prctl(PR_SET_NO_NEW_PRIVS,1,0,0,0);
	prctl(PR_SET_SECCOMP,SECCOMP_MODE_FILTER, &prog);
	printf("After seccomp : This write works (write syscall is allowed) \n");
	//This will cause the process to be killed (openat is not allowed)
	//open("/etc/passwd",0);
	return 0;
}
