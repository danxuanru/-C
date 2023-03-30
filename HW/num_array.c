#include <stdio.h>
#define N 10000

int swap(int*, int*);

int main(void)
{
    int L, arr1[N], arr2[N];
    scanf("%d", &L);
    for (int i = 0; i < L; i++) scanf("%d", &arr1[i]);
    for (int i = 0; i < L; i++) {
        scanf("%d", &arr2[i]);
        swap(&arr1[i], &arr2[i]);
    }

    printf("1st array: ");
    for(int i=0; i<L; i++) printf("%d ", arr1[i]);
    printf("\n");
    printf("2nd array: ");
    for(int i=0; i<L; i++) printf("%d ", arr2[i]);
}

int swap(int *n1, int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}