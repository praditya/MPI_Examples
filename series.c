#include<stdio.h>
#include<time.h>

int main(){

 int i,array[999999],sum=0;
 double start_time,end_time;
 start_time = clock();
 for(i=1;i<1000000;i++){
   array[i]= i;
   sum = sum + array[i];
 }

 end_time = clock();
 printf("Total sum = %d and time taken = %lf start_time %lf end_time %lf CPU speed %ld\n",sum,end_time-start_time,start_time,end_time,CLOCKS_PER_SEC);
 return 0;
}
