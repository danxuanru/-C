#include <stdio.h>

int main() {

    int item; 
    float price; // catch float
    int year, month, day;
    scanf("%d %f %d/%d/%d", &item, &price, &month, &day, &year);
    
    // tab => "\t"  newline => "\n"
    // at least 2 degits after decimal point => "%.2f"
    // backslash => "\\"
    printf("Item\tUnit\tPurchase\n");
    printf("\tPrice\tDate\n");
    printf("%d\t$%.2f\t%.2d\\%.2d\\%.4d", item, price, month, day, year);

	return 0;
}