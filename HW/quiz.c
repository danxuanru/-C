#include <stdio.h>

int main() {

	int sum[5] = {0};
	int average[5] = {0};
	int n1, n2, n3, n4, n5;

	for(int i=0; i<5; i++){
		scanf("%d %d %d %d %d", &n1, &n2, &n3, &n4, &n5);
		sum[i] = n1+n2+n3+n4+n5;
		average[i] = sum[i] / 5;
	}

	for(int i=0; i<5; i++){
		printf("%d %d %d\n", i+1, sum[i], average[i]);
	}

	return 0;
}