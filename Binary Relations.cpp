//LOGIC;
/* Brute force method, creating the matrix from the set of elements we have. Then each element from the n×n matrix i.e each pair would either be
includes or excluded. Thus doing the same for the remaining n*n - 1 pairs.*/

//Test Cases
//Input = 2, Output = 16 listed binary relations
//Input = 1, Output = 2 listed binary relations
//Input = 3, Ouput = 512 listed binary relations 

//NOTE : Not working for 0 or negative input size

#include<iostream>
#include<stdlib.h>
using namespace std;

void print();
void Listing_Relations(int k, int j);

int count = 0;
int size;
int *array; 
int **matrix;

int main()
{	
	printf("Enter the number of elements in the set: \n");
	scanf("%d",&size);
	
	array = (int*)malloc(size*sizeof(int));
	matrix = (int**)malloc(size*sizeof(int*));
	
	for(int j=0; j<size; j = j+1)
	{
		array[j] = j;
		matrix[j] = (int*)malloc(size*sizeof(int));
	}
	
	Listing_Relations(0,0);
	
}

void print()
{
	count = count+1;
	printf("Relation number %d\n",count);
	for(int m = 0; m < size; m = m+1 )
	{
		for(int n = 0; n < size; n = n+1)
		{
			if(matrix[m][n] == 1)
			{
				printf("\n(%d,%d)",array[m],array[n]);
			}
		}
	}
	
	printf("\n");
}

void Listing_Relations(int k, int j)
{
	for(int l=1; l>=0; l--)
	{
		matrix[k][j] = l;
		if( k == size-1 && j == size-1)
			print();
		else if( j == size-1)
			Listing_Relations(k+1,0);
		else 
			Listing_Relations(k,j+1);
	}
	
}
