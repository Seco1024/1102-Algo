#include <stdio.h>
#include <stdlib.h>

int main(void){
    int a[7]={2,3,4,5,6,7,8};
    int x=10,i,total=a[0];
    for(i=0;i<7;i++){
        total=total*x+a[i+1];
    }
    printf("%d",total);
    return 0;
}