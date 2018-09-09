#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

# define BILLION 1000000000L

int main(){
	struct timespec requestStart, requestEnd;
	int i, j, k = 0;

clock_gettime(CLOCK_REALTIME, &requestStart);

	for (i = 0; i < 10000; i++) {
		for (j = 0; j < 10000; j++) {
			k += 20;
		}
	}
	
clock_gettime(CLOCK_REALTIME, &requestEnd);

double accum = ( requestEnd.tv_sec - requestStart.tv_sec ) + (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;

printf("%lf\n", accum);

return 0;
}
