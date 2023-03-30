#include <stdio.h>

int main() {

    int h, m;
    scanf("%d:%d", &h, &m);

    if(h<0 || m<0 || h>24 || m>59){  //輸入錯誤
        printf("Incorrect Input");
    }
    // h>=12 => PM
    // other => AM
    else if(h>=12){ //PM

        if(h==12){
            printf("%d:%.2d PM", h, m);
        }else{
            int PM_h = h-12;
            printf("%d:%.2d PM", PM_h, m);
        }

    }else{ //AM
        if(h==0){
            printf("%d:%.2d AM", 12, m);
        }else{
            printf("%d:%.2d AM", h, m);
        }
    }

	return 0;
}