#include <stdio.h>

int main() {

    int year, month, day;
    scanf("%d/%d/%d", &month, &day, &year);
    // yyyymmdd => 4,2,2 degit
    // fill in 0 infront => "."
    printf("%.4d%.2d%.2d", year, month, day);

	return 0;
}
