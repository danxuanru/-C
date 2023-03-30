#include <stdio.h>

int GCD(int, int);

int main(void) {

    while (1)
    {
        int N, G = 0;
        scanf("%d", &N);
        if(N==0) break;

        for(int i=1; i<N; i++) {
            for(int j=i+1; j<=N; j++){
                G += GCD(i, j);
            }
        }
        printf("%d\n", G);
    }
    

	return 0;
}

int GCD(int i, int j)
{
    int gcd=1;
    if(i<j){ // keep i>j
        int temp = i;
        i = j;
        j = temp;
    }
    for (int n=2; n<=j; n++){
        if(i%n==0 && j%n==0) gcd = n;
    }

    return gcd;
}