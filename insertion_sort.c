#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
void insertion_sort(int *,int);

int main(void){
    int i;
    int *array=(int *)malloc(sizeof(int));
    
    printf("排序前:");
    for(i=0;i<10;i++){
        *(array+i)=SIZE-i;
        printf("%d ",*(array+i));
    }
    printf("\n");

    printf("排序後:");
    insertion_sort(array,SIZE);
    for(i=0;i<SIZE;i++){
        printf("%d ",*(array+i));
    }
    return 0;
}

void insertion_sort(int *arr,int n){
    int i,j;
    for(i=1;i<n;i++){
        int tmp=arr[i];
        for(j=i;j>0 && arr[j]<arr[j-1];j--){
            arr[j]=arr[j-1];
            arr[j-1]=tmp;
        }
    }
}