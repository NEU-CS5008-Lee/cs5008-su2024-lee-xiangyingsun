//Xiangying Sun
//sun.xiangyi@northeastern.edu
//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>

void insertion_sort(int* arr, int count){
    int i, j, key;

    for (i = 1; i < count; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are greater than key,
           to one position ahead of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    FILE *fp;
    int arr[10],temp;
    int count=0,i,j;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp=fopen("Input1.txt","r");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }
    
    /* Read integers from file into array */
    while (fscanf(fp, "%d", &arr[count]) != EOF && count < 10) {
        count++;
    }
    fclose(fp);

    /* Perform insertion sort */
    insertion_sort(arr, count);

    /* Display the sorted array */
    printf("Sorted array: \n");
    for (i = 0; i < count; i++) {
        printf("%d\n", arr[i]);
    }

    /* Store the sorted array in another file */
    fp = fopen("Output.txt", "w");
    if (fp == NULL) {
        printf("\n Cannot open the file \n");
        exit(0);
    }
    for (i = 0; i < count; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);

    return 0;
}
