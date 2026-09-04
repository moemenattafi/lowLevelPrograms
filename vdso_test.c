//gettimeofday uses vdso automatically
#include<sys/time.h>
#include<stdio.h>

int main(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	printf("%ld.%ld\n",tv.tv_sec,tv.tv_usec);
	return 0;
}
