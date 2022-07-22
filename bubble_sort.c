#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
void bubble_sort(int *,int);

int main(void){
    int i;
    int array[10]={4,7,2,1,8,9,6,5,3,0};
    
    printf("排序前:");
    for(i=0;i<10;i++){
        printf("%d ",array[i]);
    }
    printf("\n");

    printf("排序後:");
    bubble_sort(array,SIZE);
    for(i=0;i<SIZE;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

void bubble_sort(int *arr,int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i;j++){
            int tmp=arr[j];
            if(tmp>arr[j+1]){
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
            }
        }
    }
}