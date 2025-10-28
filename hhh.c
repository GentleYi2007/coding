#include<stdio.h>
typedef struct people
{
    char name[10];
    int gender;
    int age;
    int idcard;
}pp;
int main(){
    pp a;
    printf("name,gender(male1,female2),age,idcard\n");
    scanf("%s %d %d %d",a.name,&a.gender,&a.age,&a.idcard);
    printf("name:%s gender(male1,female2):%d age:%d idcard:%d\n",a.name,a.gender,a.age,a.idcard);
    return 0;
}