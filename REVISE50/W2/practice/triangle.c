#include <stdio.h>
int valid_triangle(float sideA, float sideB, float sideC);

int main (void)
{
    float sideA = 0, sideB = 0, sideC = 0, valid = 0;

    printf("Input length of first side of triangle:");
    scanf("%f",&sideA);
    printf("Input length of first side of triangle:");
    scanf("%f",&sideB);
    printf("Input length of first side of triangle:");
    scanf("%f",&sideC);

    valid = valid_triangle(sideA,sideB,sideC);
    if (valid == 0)
    {
        printf("FALSE");
    }
    else
    {
        printf("TRUE");
    }

    return 0;
}

int valid_triangle(float sideA, float sideB, float sideC)
{
    //check negative sides
    if( (sideA <= 0) || (sideB <= 0) || (sideC <= 0))
    {
        return 0;
    }
    //check lengths
    if( (sideA + sideB <= sideC) || (sideB + sideC <= sideA) || (sideA + sideC <= sideB) )
    {
        return 0;
    }

    return 1;

}

/* CS50 L2 Practice Problem
Declare a write a function called valid_triangle that takes three real numbers representing the lengths of the three sides of a triangle as its arguments, and outputs either true or false, depending on whether those three lengths are capable of making a triangle

Note the following rules about triangles:
- A triangle may only have sides with positive length.
- The sum of the lengths of any two sides of the triangle must be greater than the length of the third side.
*/
