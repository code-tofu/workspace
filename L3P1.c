//is leap year function
#include <stdio.h>
int main(){
 int useryear = 0;  
 printf("Input year:");
 scanf("%d",&useryear);
 
 if ((useryear%400 ==0) || ( (useryear%4 ==0) && (useryear%100!=0))){
     printf("%d is a leap year",useryear); 
 }
 else
{
  printf("%d is a not leap year",useryear);   
}
 
    
}