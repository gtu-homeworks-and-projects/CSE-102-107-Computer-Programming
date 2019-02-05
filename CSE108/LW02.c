#include <stdio.h>

double mean();

/*double minimum();
double maximum();*/
double maxSumOfIncSeq();

int main()
{
	
	/*printf("%.1f\n",mean() );*/
	printf("%.1f\n",maxSumOfIncSeq() );
	return 0;
}

double mean(){
    int cur_val=1;
    double total=0;
    int counter=0;
    double mean=0;

    while(cur_val>0){
    	printf("User Input: ");
   		scanf("%d", &cur_val);
   		if (cur_val>0)
   		{
   			total += cur_val;
   			counter +=1;
   		}
    }
    mean = (total/counter);
    return mean;
}
/*
double maximum(){  
	int cur_val=1;
	int tmp=0;
	int counter=0;
	while(cur_val>0){

    	printf("User Input: ");
   		scanf("%d", &cur_val);
   		if (cur_val>tmp)
   		{
   			tmp=cur_val;
   			counter+=1;
   		}
    }
    if (counter==0)
    {
    	tmp=cur_val;
    }
    return tmp;
}

double minimum(){  
	int cur_val=1;
	int tmp=0;
	int counter=0;
	while(cur_val>0){

    	printf("User Input: ");
   		scanf("%d", &cur_val);
   		if (cur_val>0)
   		{
   			if (cur_val<=tmp)
   			{
   				tmp=cur_val;
   				counter+=1;
   			}
   			if ((tmp==0) & (counter==0))
   			{
   				tmp=cur_val;
   			}
   		
    }
}
    return tmp;
}
*/
double maxSumOfIncSeq(){
	int counter;
	int tmp_count;
	double tmp=0;
	double cur_val=1;
	double sum1;
	double sum2;
	double lastsum=0;

	while(cur_val>0){
    	printf("User Input: ");
   		scanf("%lf", &cur_val);
   		if ((tmp<cur_val))
   		{
   			tmp=cur_val;
   			sum1 += cur_val;
   			counter += 1;
   		}
   		
   		else if ((cur_val>0) & (tmp>cur_val)){
   			printf("silindi\n");
   			tmp = cur_val;
   			tmp_count = counter;
   			sum2=sum1;
   			sum1=0;
   			counter = 0;
   			sum1 += cur_val;
   			counter += 1;
   		}
   		if (tmp_count<counter)
   		{
   			
   			lastsum=sum1;
   		}
   		else if(tmp_count>counter){
   			
   			lastsum=sum2;
   		}
    }
    printf("%f %f\n", sum1,sum2);
    printf("%f\n", lastsum);
    return lastsum;
}