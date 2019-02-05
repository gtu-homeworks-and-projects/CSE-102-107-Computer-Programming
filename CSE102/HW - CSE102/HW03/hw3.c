#include <stdio.h>

int goldbach(int num, int *p1, int *p2);
int isPrime (int num);
int dispenseChange(double paid, double due, int *tl1, int *krs50,
int *krs25, int *krs10, int *krs5, int *krs1);

int charge(int cardType, int* monthlyUse, double* balance);

int main()
{
	int nm,f,s;
	double paid = 4.91, due = 3;
	int tl1,krs50,krs25,krs10,krs5,krs1;
	int monthlyUse = 0;
	double balance = 4;
	if(charge(2,&monthlyUse, &balance) == 0)
		printf("Remaining monthly use: %d – Remaining Balance: %.2f\n",monthlyUse,balance);
	else
		printf("Insufficient balance.\n");
	/*scanf("%d",&nm);
	goldbach(nm,&f,&s);*/
	/* printf("%d = %d + %d\n",nm,f,s ); */
	if(dispenseChange(paid,due,&tl1,&krs50, &krs25, &krs10, &krs5, &krs1)) /* returns 1 */
		printf("Change: 1TL:%d, Kurus-50:%d, 25:%d, 10:%d, 5:%d, 1:%d\n",tl1,krs50,krs25,krs10,krs5,krs1);
	else
		printf("Unable to dispense change.");
	return 0;
}

int charge(int cardType, int* monthlyUse, double* balance)
{
	if (*monthlyUse > 0)
	{
		*monthlyUse -= 1 ;
		return 0;
	}
	else
	{
		switch(cardType)
		{
			case 1 :	
				if (*balance >= 2.30)
				{
					*balance -= 2.30;
					return 0;
				}
				else
					return (-1);
			case 2 :	
				if (*balance >= 1.15)
				{
					*balance -= 1.15;
					return 0;
				}
				else
					return (-1);
			case 3 :	
				if (*balance >= 1.65)
				{
					*balance -= 1.65;
					return 0;
				}
				else
					return (-1);
			default :
					return -2;
		}
	}
}

int dispenseChange(double paid, double due, int *tl1, int *krs50,
int *krs25, int *krs10, int *krs5, int *krs1)
{
	double change, fracCalc;
	int fl;

	if (paid > due)
	{
		change = paid - due ;
		printf("%f\n", change );
		fracCalc =  (change - (int)(change/1)) * 100;
		printf("%d\n", (int)fracCalc );
		fl = (int)(fracCalc + .1) ;
		printf("%d\n", fl );
		*tl1 = (int) (change / 1);
		*krs50 = (int) (fl / 50);
		*krs25 = (int) (fl%50)/25;
		*krs10 = (int) ((fl%50)%25)/10;
		*krs5 = (int) (((fl%50)%25)%10)/5;
		*krs1 = (int) (((fl%50)%25)%10)%5;
		return 1;
	}
	return 0;
}

int goldbach(int num, int *p1, int *p2)
{
	int i,middleODD;

	/* obtaining middle odd number to use in for loops initialization */
	if ((num/2)%2 == 0)
		middleODD = num/2 - 1;

 	else 
 		middleODD = num/2;
	/* ------------------------------ */


	if ((num%2) == 0)
	{
		/* checking every odd number starting from middle and decreasing it */
		for (i = middleODD; (i > 2); i -= 2)
		{
			if ((isPrime(num-i) == 1) & (isPrime(i) == 1))
			{
				*p1 = i;
				*p2 = (num - i);
				return 1;
			}
		}
		/* ------------------------------ */
	}
	
	else
	{
		return 0;
	}

	return 0;
}


/* Checks is the number prime or not */
int isPrime (int num)
{
	int i;

	if (num < 2)
		return 0;
	
	else if (num <= 3)
		return 1;
	
	else if (num > 3)
	{
		for (i = 2; i < (num/2); ++i)
			if ((num%i) == 0)
				return 0;
		return 1;
	}
	return 0;
}
/* ------------------------------ */