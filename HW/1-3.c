#include <stdio.h>

int main() {

    int group1, group2, group3, group4, group5;
    scanf("%d-%d-%d-%d-%d", &group1, &group2, &group3, &group4, &group5);
    
    // left justification => "-"
    // minimum degit of 3 => 3d
    // fill space infront => "."
    printf("%-.3d\n", group1);
    printf("%-.3d\n", group2);
    printf("%-.3d\n", group3);
    printf("%-.3d\n", group4);
    printf("%-.3d\n", group5);

    
	return 0;
}