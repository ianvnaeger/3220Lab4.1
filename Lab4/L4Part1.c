/*
 ============================================================================
 Name        : 3220Lab4.c
 Author      : Ian Naeger
 Version     :
 Copyright   : N/A
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int* ReadFile( int num , int *len);
double* ScaleIt( int* data , double scale , int* len );
double* OffsetIt( int* data , double offset , int* len);
double FindMean( int* data , int* len );
int FindMax( int* data , int* len );
double* CenterIt( int* data , int* len , double mean );
double* NormalizeIt( int* data , int* len , double max );

int main(void) {

	int num , choice , k;
	int *array , *len;

	printf("Enter File to Open: \n");
	scanf("%d", &num);
	getchar();
	printf("Would you like to Scale or Offset the Data? \n1. Scale \n2. Offset \n");
	scanf("%d", &choice);
	getchar();
// Gets file and mode from user
	array = ReadFile( num , len );
// gets array from file
	if( choice == 1 )
	{
		double scale;
		double *ScaledArray;
		char *Output;
		Output = malloc( 18 * sizeof(char));

		printf("Enter Scaling Factor:");
		scanf("%lf", &scale);
		getchar();

		ScaledArray = ScaleIt(array , scale , len);

		sprintf(Output, "Scaled_data_%02d.txt", num);
		FILE* fp = fopen(Output , "w");

		fprintf(fp , "%d %lf\n" , *len , scale);

		for(k = 0; k < *len; k++)
		{
			fprintf( fp , "%f\n" , *(ScaledArray + k));
		}

		fclose(fp);
// takes array, scales it, puts it in a new array and prints it to a file 
	}
	else if( choice == 2 )
	{
		double Offset;
		double *OffsetArray;
		char *Output;
		Output = malloc( 18 * sizeof(char));

		printf("Enter Offset:");
		scanf("%lf", &Offset);
		getchar();

		OffsetArray = OffsetIt(array , Offset , len);

		sprintf(Output, "Offset_data_%02d.txt", num);
		FILE* fp = fopen(Output , "w");

		fprintf(fp , "%d %lf\n" , *len , Offset);

		for(k = 0; k < *len; k++)
		{
			fprintf( fp , "%f\n" , *(OffsetArray + k));
		}
		fclose(fp);
// takes array, offsets it, puts it in a new array and prints it to a file 
	}

	double mean , max;
	double *CenteredArray;
	double *NormalizedArray;
	char *OutputA;
	char *OutputB;
	char *OutputC;
	
	OutputA = malloc( 22 * sizeof(char));
	
	mean = FindMean( array , len ); 
	max = FindMax( array , len );
	
	sprintf(OutputA, "Statistics_data_%02d.txt", num); 
	FILE* fpA = fopen(OutputA , "w"); 
	
	fprintf(fpA, "%lf %lf\n" , mean , max); 
	
	fclose( fpA );  
	// finds the mean and max of the array and prints it to a file 
	CenteredArray = CenterIt(array , len , mean);
 
	OutputB = malloc( 20 * sizeof(char));

	sprintf(OutputB, "Centered_data_%02d.txt", num);
	FILE* fpB = fopen(OutputB , "w");

	fprintf(fpB , "%d %lf\n" , *len , mean);

	for(k = 0; k < *len; k++)
	{
		fprintf( fpB , "%f\n" , *(CenteredArray + k));
	}
	fclose(fpB);
// centers the array and prints it to a file 
	
	NormalizedArray = NormalizeIt(array , len , max);
	OutputC = malloc( 22 * sizeof(char) );

	sprintf(OutputC, "Normalized_data_%02d.txt", num);
	FILE* fpC = fopen(OutputC , "w");

	fprintf(fpC , "%d %lf\n" , *len , max);

	for(k = 0; k < *len; k++)
	{
		fprintf( fpC , "%f\n" , *(NormalizedArray + k));
	}
	fclose(fpC);
		// normalizes the array and prints it to a file 
	return 0;
}

int* ReadFile( int num , int* len)
{
	int *array;
	int max , k;
	char *Filename = malloc( 15 * sizeof( char ));

	sprintf(Filename, "Raw_data_%02d.txt", num);
	FILE* fp = fopen(Filename, "r");

	fscanf( fp , "%d %d\n" , len , &max);

	array = malloc( (*len) * sizeof(int) );

	for(k = 0; k < *len; k++)
	{
		fscanf(fp, "%d", (array + k));
	}

	fclose(fp);
	free( Filename );
// Takes file number, finds the file, and makes it into an array
	return array;
}

double* ScaleIt( int* data , double scale , int* len )
{
	int k;
	double *array;
	array = malloc( (*len) * sizeof(char) );
	for(k = 0; k < *len; k++)
	{
		*(array + k) = (double)*(data + k) * scale;
	}
// scales the array
	return array;
}

double* OffsetIt( int* data , double offset , int* len)
{
	int k;
		double *array;
		array = malloc( (*len) * sizeof(char) );
		for(k = 0; k < *len; k++)
		{
			*(array + k) = (double)*(data + k) + offset;
		}
// offsets the array
		return array;
}

double* NormalizeIt( int* data , int* len , double max )
{
	int k;
	double *array;
	array = malloc( (*len) * sizeof(char) );
	for(k = 0; k < *len; k++)
	{
		*(array + k) = (double)*(data + k) / max;
	}
// normalizes the array
	return array;
}

double* CenterIt( int* data , int* len , double mean )
{
	int k;
	double *array = malloc( (*len) * sizeof(char) );
 
	for(k = 0; k < *len; k++)
	{
		*(array + k) = (double)*(data + k) - mean;
	}
// Centers the array 
	return array;
}

double FindMean( int* data , int* len )
{
	int k; 
	double mean = 0; 
	for(k = 0; k < *len; k++)
	{
		mean = mean + (double)*(data + k); 
	}
	mean = mean / *len;
// Finds the mean of the array
	return mean; 
}

int FindMax( int* data , int* len )
{
	int k; 
	double max = 0;
	for( k = 0; k < *len; k++)
	{ 
		if( *(data + k) > max )
		{ 
			max = *(data + k);
		}
	}
// Finds the max of the array
	return max; 
}
















