#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

# define BILLION 1000000000L

int main(){
	time_t start = time(0);
	
	int i, j, k = 0;
	
	for (i = 0; i < 10000; i++) {
		for (j = 0; j < 10000; j++) {
			k += 20;
		}
	}
	
	time_t end = time(0);

	double time = difftime(end, start) * 1000.0;

printf("%lf\n", time);
// 230 ~ 240 (approx in ms)

return 0;
}
