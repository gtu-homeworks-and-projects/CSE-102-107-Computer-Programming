#include <stdio.h>

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main()
{
	double inputArr[] = {5, 6, 7, 8, 9};
	double outputArr[255];
	int outputArrSize = 0 , i;
	int x = 10, a = 6, b = 5 , y = 20; 
	
	addPadding(inputArr, 5, outputArr, outputArrSize, 4,samePadding);
	for (i = 0; i < 13; ++i)
	{
		printf("%f\n",outputArr[i] );
	}

	for (i = 0; i < (a > b ? x : y); ++i)
	{
		printf("MnM\n");
	}
	return 0;
}

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int outputArraySize, int paddingWidth,  void paddingMethod(double[], int, int))
{
	int i;

	for (i = 0; i < inputArraySize; ++i)
		outputArr[i+paddingWidth] = inputArr[i];
	outputArraySize = inputArraySize + (paddingWidth*2);
	paddingMethod(outputArr,outputArraySize,paddingWidth);

}

void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;
	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = 0;
	}
	for (i = outputArraySize-1 ; i >= (outputArraySize - paddingWidth); --i)
	{
		outputArr[i] = 0;
	}
}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;
	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = outputArr[paddingWidth];
	}
	for (i = outputArraySize-1 ; i >= (outputArraySize - paddingWidth); --i)
	{
		outputArr[i] = outputArr[outputArraySize-paddingWidth-1];
	}
}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;
	for (i = 0; i < paddingWidth; ++i)
	{
		outputArr[i] = outputArr[paddingWidth] / 2;
	}
	for (i = outputArraySize-1 ; i >= (outputArraySize - paddingWidth); --i)
	{
		outputArr[i] = outputArr[outputArraySize-paddingWidth-1] / 2;
	}
}