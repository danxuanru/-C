#include <stdio.h>

int main() {

	int number[10] = {0,1,2,3,4,5,6,7,8,9};
	// char number[10] = {'0','1','2','3','4','5','6','7','8','9'};
	int time[10] = {0};
	char c;
	int n, first=0;
	
	while ((c=getchar())!='\n' && c!=EOF)
	{
		if(c=='0' && first==0) continue;
		first = 1;

		n = c-'0';
		for(int i=0; i<10; i++){
			if(n==number[i]){
				time[i]++;
				break;
			}
		}
	}
	
	for(int i=0; i<10; i++){
		printf("%d ", number[i]);
	}
	printf("\n");
	for(int i=0; i<10; i++){
		printf("%d ", time[i]);
	}

	return 0;
}