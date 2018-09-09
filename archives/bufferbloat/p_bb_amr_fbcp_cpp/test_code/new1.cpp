#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

# define BILLION 1000000000L

int main(){
	clock_t start = clock();
	
	int i, j, k = 0;
	
	for (i = 0; i < 10000; i++) {
		for (j = 0; j < 10000; j++) {
			k += 20;
		}
	}
	
	clock_t end = clock();

	double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

	printf("%lf\n", time);
	// 230 ~ 240 (approx in ms)

return 0;
}
