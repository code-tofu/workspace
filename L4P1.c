/*
Leture 4 Problem 1
Write a function that determines if an input year is a leap year

Year Yis a leap year (366 days):
- If Y is divisible by 400
- If Y is divisible by 4, unless it is also divisible by 100
- Leap year: 1604, 2000
- Not leap year: 1900, 2009
*/


#include <stdio.h>

int main(){
  int useryear = 0;  
  printf("Input year:");
  scanf("%d",&useryear);
 
  if ((useryear%400 ==0) || ( (useryear%4 ==0) && (useryear%100!=0))){
    printf("%d is a leap year",useryear); 
  }
  else{
    printf("%d is a not leap year",useryear);   
  }
}