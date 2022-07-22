#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i,temp;
    char ch;
    int suffix_max=0,suffix_min=0,global_min=0,global_max=0,acc=0;
    while(scanf("%d",&temp)!=EOF){  
        acc+=temp;
        if(suffix_max+temp>=global_max){
            suffix_max+=temp;
            global_max=suffix_max;
        }
        else if(suffix_max+temp>0)
            suffix_max+=temp;
        else
            suffix_max=0;
        if(suffix_min+temp<=global_min){
            suffix_min+=temp;
            global_min=suffix_min;
        }
        else if(suffix_min+temp<0){
            suffix_min+=temp;
        }
        else{
            suffix_min=0;
        }
        if(ch=getchar()=='\n'){
            break;
        }
    }
    if(acc-global_min>global_max){
        global_max=acc-global_min;
    }
        printf("%d\n",global_max);
        suffix_max=0;
        suffix_min=0;
        global_min=0;
        global_max=0;
        acc=0;

    return 0;
}