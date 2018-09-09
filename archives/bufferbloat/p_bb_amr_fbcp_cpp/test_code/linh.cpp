#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	struct rusage usage;
	struct timeval start, end;
	int i, j, k = 0;
	
	getrusage(RUSAGE_SELF, &usage);
	//start = usage.ru_stime;
	start = usage.ru_utime;
	
	/*Put your code which you want to measure here*/
	for (i = 0; i < 10000; i++) {
		for (j = 0; j < 10000; j++) {
			k += 20;
		}
	}
	/*--------------------------------------------*/
	
	getrusage(RUSAGE_SELF, &usage);
	//end = usage.ru_stime; //system CPU time (kernel-mode, i.e., processing system calls)
	end = usage.ru_utime; //user CPU time (user-mode, i.e., running application code)
	
	printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
	printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
	printf("Peak resident set size: %ld (kilobytes) \n", usage.ru_maxrss);
	return 0;
}
