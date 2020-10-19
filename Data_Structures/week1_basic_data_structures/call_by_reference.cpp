// C program to illustrate
// call by reference
#include <stdio.h>
void swapnum(int* i, int* j)
{
    int temp = *i;
    printf("temp is %d\n", temp);
    *i = *j;
    *j = temp;

    printf("i is %d and j is %d\n", *i, *j);

}

int main(void)
{
    int a = 10, b = 20;

    // passing parameters
    swapnum(&a, &b);

    printf("a is %d and b is %d\n", a, b);
    return 0;
}
