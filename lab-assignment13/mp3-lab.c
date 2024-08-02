//sun.xiangyi@northeastern.edu
//Xiangying Sun

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    int res_index = 0;
    int i = 0;

    while(i < n){
        int count = 1;
        while(i+1 < n && arr[i] == arr[i+1]){
            count++;
            i++;
        }

        res[res_index++] = arr[i]; // store the letter in res

        //store the frequency of the letter in res if frequency is more than 1
        if(count > 1){
            char count_str[10];
            sprintf(count_str, "%d", count);
            for (int j = 0; count_str[j] != '\0'; j++){
                res[res_index++] = count_str[j];
            }
        }

        i++; 
    }
    
    
    
    res[res_index] = '\0';
    
    return res_index;
}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("Compressed string: %s\n", res);
    printf("length of the compressed string:%d\n",r);
    return 0;
}
