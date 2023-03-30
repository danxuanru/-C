#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n); // 總行數 n
    
    for(int i=1; i<n+1; i++){  // 目前行數 i
        
        for(int j=0; j<n-i; j++){  // 每行內星星前的空白數 j = n-i
            printf(" ");
        }
        for(int k=0; k<(2*i-1); k++){  // 每行的星星數 k = 2*i-1
            printf("*");
        }
        printf("\n"); //換行
    }

	return 0;
}