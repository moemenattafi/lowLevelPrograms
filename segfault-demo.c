#include<stdio.h>
#include<string.h>

int main(){
	//Trying to read from the kernel
	unsigned long * kernel_addr = (unsigned long *) 0xffffffff81000000UL;
 	printf("Attempting to read kernel memory...\n");
	printf("Value:%lu\n",*kernel_addr);
	return 0;
}
