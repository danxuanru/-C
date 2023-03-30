#include <stdio.h>
#include "ctype.h" 

int main() {

    // k=母音數 j=總字數
    int k=0, j=1;
    int space=0; // space紀錄前一個char是否為空白
    char ch;
    
    do {
        ch=getchar();

        if(ch==' ' && space==0){

            j += 1;
            space = 1; // 若下一個char仍為空白 j不增加
        }
        else if(ch!=' ')
        {

            ch = tolower(ch);
            // if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'){
            //     k += 1;
            // }
            switch (ch)
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                k += 1;
                break;
            default:
                break;
            }
            space = 0; // 若下一個char為空白 j可以增加
        }

    }while (ch != '\n' && ch != EOF);  // !!!EOF

    printf("%d %d", k, j);

	return 0;
}