#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE *fl=NULL;
char str[100],user[5],seat[7][5][4][4];
int time=-1,raw=0,column=0,abool=0,bbool=0,cbool=0,dbool=0,ebool=0,fbool=0,wbool=0,floor=0,endbool=0;
void login();
void readstr();
void admin();
int main(){
    memset(seat,'0',sizeof(seat));
    fl=fopen("seatdata.txt","r");
    if(fl==NULL){
        fl=fopen("seatdata.txt","w");
        fwrite(seat,sizeof(seat),1,fl);
        fclose(fl);
    }
    do
    {   
        printf("请输入(Login登录用户，Quit退出程序)：");
        scanf("%s",str);
        if(strcmp(str,"Quit")==0)
        {
            printf("感谢与你相遇，我们下次再见~\n");
            return 0;
        }
        if(strcmp(str,"Login")==0){
            login();
            return 0;
        }
        if(user[0]=='\0'){
            printf("请先登录~\n");
        }
    }while(1);
    return 0;
}
void login(){
    do
    {   
        if(user[0]!='\0'){
            printf("已登录，若要切换用户请输入Exit退出当前用户\n");
        }
        if(user[0]=='\0'){
            printf("请输入登录用户名：");
        }
        scanf("%s",str);
        if(strcmp(str,"Admin")==0){
            strcpy(user,str);
            printf("管理您好!\n(若要切换用户请输入Exit退出当前用户)\n");
            do{
                char op;
                while((op=getchar())!='\n'){
                    int i=0;
                    while(op!=' '){
                        if(op=='\n')break;
                        str[i]=op;
                        i++;
                        op=getchar();
                    }
                    str[i]='\0';
                    if(strcmp(str,"Exit")==0&&op=='\n'){
                        user[0]='\0';
                        printf("您已退出登录\n");
                        break;
                    }
                    if(strcmp(str,"Quit")==0&&op=='\n'){
                        user[0]='\0';
                        printf("感谢与你相遇，我们下次再见~\n");
                        return;
                    }
                    admin(str);
                    if(endbool!=1&&op=='\n')printf("输入有误~\n");
                }
                if(strcmp(str,"Exit")==0&&op=='\n')break;
            }while(1);
            user[0]='\0';
            continue;
        }
        if(str[0]>='A'&&str[0]<='Z'&&str[1]=='\0'){
            strcpy(user,str);
            printf("登录成功，%s同学你好呀~\n(若要切换用户请输入Exit退出当前用户)\n",user);
            do{
                char op;
                while((op=getchar())!='\n'){
                    int i=0;
                    while(op!=' '){
                        if(op=='\n')break;
                        str[i]=op;
                        i++;
                        op=getchar();
                    }
                    str[i]='\0';
                    if(strcmp(str,"Exit")==0&&op=='\n'){
                        user[0]='\0';
                        printf("您已退出登录\n");
                        break;
                    }
                    if(strcmp(str,"Quit")==0&&op=='\n'){
                        user[0]='\0';
                        printf("感谢与你相遇，我们下次再见~\n");
                        return;
                    }
                    readstr(str);
                    if(endbool!=1&&op=='\n')printf("输入有误~\n");
                }
                if(strcmp(str,"Exit")==0&&op=='\n')break;
            }while(1);
            user[0]='\0';
            continue;
        }
        else if(strcmp(str,"Quit")==0){
                    user[0]='\0';
                    printf("感谢与你相遇，我们下次再见~\n");
                    return;
                }else{
                    printf("用户名错误，请重新输入\n");
                    continue;
                }
    }while(1);
}

enum {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
void readstr(char *tmp){
    if(strcmp(tmp,"Monday")==0){
        time=MONDAY;
        abool=2;
    }
    if(strcmp(tmp,"Tuesday")==0){
        time=TUESDAY;
        abool=2;
    }
    if(strcmp(tmp,"Wednesday")==0){
        time=WEDNESDAY;
        abool=2;
    }
    if(strcmp(tmp,"Thursday")==0){
        time=THURSDAY;
        abool=2;
    }
    if(strcmp(tmp,"Friday")==0){
        time=FRIDAY;
        abool=2;
    }
    if(strcmp(tmp,"Saturday")==0){
        time=SATURDAY;
        abool=2;
    }
    if(strcmp(tmp,"Sunday")==0){
        time=SUNDAY;
        abool=2;
    }
    if(strcmp(tmp,"Floor")==0&&abool==1){
        bbool=2;
    }
    if(tmp[0]>='1'&&tmp[0]<='5'&&bbool==1){
        floor=tmp[0]-'0';
        cbool=2;
    }
    if(strcmp(tmp,"Seat")==0&&wbool!=0&&cbool==1){
        dbool=2;
    }
    if(tmp[0]>='1'&&tmp[0]<='4'&&dbool==1){
        raw=tmp[0]-'0';
        ebool=2;
    }
    if(tmp[0]>='1'&&tmp[0]<='4'&&ebool==1){
        column=tmp[0]-'0';
        fbool=1;
    }
    if(strcmp(tmp,"Reserve")==0){
        wbool=7;
    }
    if(wbool==1&&fbool==1&&user[1]=='\0'){
        fl=fopen("seatdata.txt","r");
        fseek(fl,time*80+(floor-1)*16+(raw-1)*4+(column-1),SEEK_SET);
        seat[time][floor][raw][column]=fgetc(fl);
        fclose(fl);
        fl=fopen("seatdata.txt","r+");
        fseek(fl,time*80+(floor-1)*16+(raw-1)*4+(column-1),SEEK_SET);
        if(seat[time][floor][raw][column]=='0'){
            fputc(user[0],fl);
            seat[time][floor][raw][column]=user[0];
            printf("OK预订成功~\n");
        }else{
            printf("该座位已被预订，请重新选择~\n");
        }
        fclose(fl);
        endbool=2;
    }
    if(cbool==2&&wbool<=0){
        fl=fopen("seatdata.txt","r");
        fseek(fl,time*80+(floor-1)*16,SEEK_SET);
        for(int c=0;c<4;c++){
            for(int d=0;d<4;d++){
                seat[time][floor][c+1][d+1]=fgetc(fl);
                if(seat[time][floor][c+1][d+1]>='A'&&seat[time][floor][c+1][d+1]<='Z'&&user[1]=='\0'){
                    if(seat[time][floor][c+1][d+1]==user[0])printf("2 ");
                    else printf("1 ");
                }
                else printf("%c ",seat[time][floor][c+1][d+1]);
            }
            printf("\n");
        }
        printf("\n");
        fclose(fl);
        endbool=2;
    }
    if(strcmp(tmp,"Reservation")==0){
        fl=fopen("seatdata.txt","r");
        for(int a=0;a<7;a++){
            for(int b=0;b<5;b++){
                for(int c=0;c<4;c++){
                    for(int d=0;d<4;d++){
                        seat[a][b+1][c+1][d+1]=fgetc(fl);
                        if(seat[a][b+1][c+1][d+1]==user[0]&&user[1]=='\0'){
                            char day[10];
                            switch(a){
                                case 0:strcpy(day,"Monday");break;
                                case 1:strcpy(day,"Tuesday");break;
                                case 2:strcpy(day,"Wednesday");break;
                                case 3:strcpy(day,"Thursday");break;
                                case 4:strcpy(day,"Friday");break;
                                case 5:strcpy(day,"Saturday");break;
                                case 6:strcpy(day,"Sunday");break;
                            }
                            printf("%s Floor %d Seat %d %d\n",day,b+1,c+1,d+1);
                        }
                    }
                }
            }
        }
        fclose(fl);
        endbool=2;
    }
    abool--;
    bbool--;
    cbool--;
    dbool--;
    ebool--;
    wbool--;
    fbool--;
    endbool--;
}
void admin(char *tmp){
    if(strcmp(tmp,"Clear")==0){
        memset(seat,'0',sizeof(seat));
        fl=fopen("seatdata.txt","w");
        fwrite(seat,sizeof(seat),1,fl);
        fclose(fl);
        printf("所有座位预约数据已清除\n");
        endbool=2;
    }
    readstr(tmp);
}
