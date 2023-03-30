#include <stdio.h>

int main() {

    int n1, n2, n3, n4, n5, n6, n7, n8;
    int n9, n10, n11, n12, n13, n14, n15 ,n16;
    // sum
    int row1, row2, row3, row4, col1, col2, col3, col4;
    int diagonal1, diagonal2;
    
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
        &n1, &n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9, &n10, &n11, &n12, &n13, &n14, &n15, &n16);
    
    row1 = n1 + n2 + n3 + n4;
    row2 = n5 + n6 + n7 + n8;
    row3 = n9 + n10 + n11 + n12;
    row4 = n13 + n14 + n15 + n16;
    col1 = n1 + n5 + n9 + n13;
    col2 = n2 + n6 + n10 + n14;
    col3 = n3 + n7 + n11 + n15;
    col4 = n4 + n8 + n12 + n16;
    diagonal1 = n1 + n6 + n11 + n16;
    diagonal2 = n4 + n7 + n10 + n13;
    
    printf("%d\t%d\t%d\t%d\n", n1, n2, n3, n4);
    printf("%d\t%d\t%d\t%d\n", n5, n6, n7, n8);
    printf("%d\t%d\t%d\t%d\n", n9, n10, n11, n12);
    printf("%d\t%d\t%d\t%d\n", n13, n14, n15, n16);
    printf("%d\t%d\t%d\t%d\n", row1, row2, row3, row4);
    printf("%d\t%d\t%d\t%d\n", col1, col2, col3, col4);
    printf("%d\t%d", diagonal1, diagonal2);

    
	return 0;
}