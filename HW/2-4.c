#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n);
    printf("%d ", n);

    while(n!=1){  // n=1時停止
        // odd => 3*n+1
        // even => n/2
        if(n%2==1){
            n = 3*n+1;
            printf("%d", n);
        }
        else{
            n = n/2;
            printf("%d", n);
        }
        printf(" ");
    }

	return 0;
}