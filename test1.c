#include<stdio.h>
#include<string.h>
int main(){
    char str[100],stdstr1[100]="Dian",stdstr2[100]="Quit";
    while(1){
            printf("请输入：");
            scanf("%s",str);
            if(strcmp(str,stdstr1)==0){
                    printf("%d\n",2002);
            }else if(strcmp(str,stdstr2)==0){
                    return 0;
            }else{
                    printf("%s\n","Error");
            }
    }
    return 0;
}