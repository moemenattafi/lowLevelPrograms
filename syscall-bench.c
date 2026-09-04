#include<stdio.h>
#include<time.h>
#include<sys/time.h>

int main(){
	struct timespec ts;
	long long count = 1000000;
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(long long i = 0 ; i < count; i++) {
		clock_gettime(CLOCK_MONOTONIC, &ts);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	long long ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
	printf("clock_gettime vDSO : %.1f ns per call\n", (double)ns/count);
	return 0;
}
