//LOGIC;
/*Taking the array and dividing it into 3 ways until in the sub arrays the difference between the last and first term is 1, then checking if the 
number is a perfect square by calculating the square root of the number, converting it to integer and then checking whether the integer and square
root are equal. If yes then the number is a perfect square.*/

//Test Cases;
// Input : 16 9 21 25, Output = 3
// Input : 1 5 2 56 43 23 42 77 11 23, Output = 1
// Input : 0 1 2, Output = 2
// Input : -4 -18 16 20 29, Output = 1

#include<iostream>
#include<math.h>
using namespace std;

int divide(int* arr, int end, int beg);
int perfectsquare(int arr);

int main()
{ 
	int size; int arr[1000];
    printf("Enter the length of the array:  \n");
	scanf("%d", &size);
	
	printf("Enter the integers:  \n");
	for(int i = 0; i < size; i = i+1)
        {
            scanf("%d", &arr[i]);
        }    
    
    printf("The entered numbers are: \n");
    for(int i = 0; i < size; i = i+1)
        {
            printf("%d ", arr[i]);
        }    
        
    printf("\nThe number of perfect squares in the given array is: %d",divide(arr, size, 0));    
}					

int divide(int* arr, int end, int beg)
{
	int mid1; int mid2;
	if(end == beg)
	{
		return 0;
	}
	if(end - beg == 1)
	{
		if(perfectsquare(arr[beg]) == 1)
			return 1;
		else
			return 0;
	}
	
	mid1 = beg + (end - beg) / 3;
	mid2 = beg + 2 * ((end - beg) / 3) + 1;
	return divide(arr, mid1, beg) + divide(arr, mid2, mid1) + divide(arr, end, mid2);
}

int perfectsquare(int arr)
{
    float b = sqrt(arr);
    int c = b;
    if(c == sqrt(arr))
    {
        return 1;
	}
    else		
	    return 0;
}
