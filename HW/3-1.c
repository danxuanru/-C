#include <stdio.h>

int main() {

	// GCD (greatest common divisor)

    int i, j, k=1;
	scanf("%d %d", &i, &j);

	// set i>j
	if(i<j){ 
		int temp = i;
		i=j;
		j=temp;
	}
	
	if(j==0){ // 兩數中有0 GCD=另一數
		k=i;

	}else{
		for(int n=2; n<=j; n++){
			// 同時整除(公因數) => 存在k 直至最大
			if(i%n==0 && j%n==0){
				k=n;
			}
		}
	}

	printf("%d", k);


	return 0;
}