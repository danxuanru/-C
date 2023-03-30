#include <stdio.h>
#include "ctype.h"


int arr[10] = {1,2,3,4,5,6,7,8,9,10};
void insertion(void);
void updation(void);
void traversing(void);
void deletion(void);

int main() {

	char action_arr[50] = {0};
	char c;
	int num_action, i=0;
	printf("num of actions:");
	scanf("%d", &num_action);
	printf("\n");

	while(i!=num_action){

		c = getchar();
		// c = getch();
		// putchar(c);
		
		if(islower(c)){
			action_arr[i] = c;
			i++;
			// printf("In ");
			// printf("%c\n", c);
		}
		
	}

	// fflush(stdin);

	for (int i=0; i<num_action; i++)
	{
		// insertion - index右邊的數字都向右移
		if(action_arr[i]=='i')  insertion();
			
		// update - 更改index數字
		else if (action_arr[i] == 'u')  updation();

		// traversing
		else if (action_arr[i] == 't')  traversing();

		// deletion
		else if(action_arr[i] == 'd')  deletion();
			
		else printf("INVALID ACTION\n");
	}
	
	return 0;
}

void insertion(void)
{
	int index, num;
	printf("position to insert:");
	scanf("%d", &index);
	printf("\n");
	if( index>9 || index<0 ){
		printf("INVALID POSITION\n");
		return;
	}
	printf("enter the value to insert:");
	scanf("%d", &num);
	printf("\n");
	
	// left shift
	for(int i=9; i>index; i--) {
		arr[i] = arr[i-1];
	}

	arr[index] = num;
	traversing();
}

void updation(void)
{
	int index, num;
	printf("position to update:");
	scanf("%d", &index);
	printf("\n");
	if( index>9 || index<0 ){
		printf("INVALID POSITION\n");
		return;
	}
	printf("enter the value to update:");
	scanf("%d", &num);
	printf("\n");
	arr[index] = num;
	traversing();
}

void traversing(void)
{
	for (int i=0; i<10; i++)  printf("%d ", arr[i]);
	printf("\n");
}

void deletion(void)
{
	int index;
	printf("position to delete:");
	scanf("%d", &index);
	printf("\n");
	if( index>9 || index<0 ){
		printf("INVALID POSITION\n");
		return;
	}
	arr[index] = 0;
	traversing();
}