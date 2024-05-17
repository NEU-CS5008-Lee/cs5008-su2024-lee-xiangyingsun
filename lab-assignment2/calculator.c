//Xiangying Sun
//sun.xiangyi@northeastern.edu
#include<stdio.h>
int main()
{
    int a,b,c, choice;
    
    printf("Enter your choice\n");
    printf(" 1. Addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
    
    printf("Enter a value: ");
    scanf("%d", &a);
    printf("Enter b value: ");
    scanf("%d", &b);
    
    switch (choice)
    {
        case 1:
            printf("Result: %d + %d = %d\n", a, b, a+b);
            break;
        
        case 2:
            printf("Result: %d - %d = %d\n", a, b, a-b);
            break;
        
        case 3:
            printf("Result: %d * %d = %d\n", a, b, a*b);
            break;
        
        case 4:
            if (b != 0) {
                printf("Result: %d / %d = %d\n", a, b, a / b);
            } else {
                printf("Error: b cannot be zero.\n");
            }
            break;

        default:
            printf("Invalid choice. Please choose a number from 1,2,3,4.\n");
            break;
    }
           
    return 0;
}
