#include <stdio.h>
#include <math.h>

void FIB(int, int);
long int fib[40] = {0};
int binary[40] = {0};

int main() {

	fib[0] = 1;
	fib[1] = 2;
	for(int i=2; i<40; i++) fib[i] = fib[i-1] + fib[i-2];
	// for(int i=2; i<40; i++) printf("%d ",fib[i]);
	int T, d;
	scanf("%d", &T);

	for(int i=0; i<T; i++)
	{
		int N=0;
		scanf("%d", &d);
		while(fib[N]<=d) N++;
		N-=1;
		
		FIB(d, N);
		printf("%d = ", d);
		for(int k=N; k>=0; k--) {
			printf("%d", binary[k]);
			binary[k] = 0;  // reset 
		}
		printf(" (fib)\n");
	}
	
	return 0;
}

void FIB(int n, int i)
{
	n-=fib[i];
	binary[i] = 1;
    // printf("%d %d %d\n", n,i,binary[i]);
	if(n==0) return;
	
	while(fib[i]>n) i--;

	FIB(n, i);
	return;
}
