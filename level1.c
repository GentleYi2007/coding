#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE *fl=NULL;
char superstr[100],user[5],seat[11][11],day[7][9]={"Monday","Tuesday","Wendsday","Thursday","Friday","Saturday","Sunday"};
char (*pday)[9];
int time=-1,raw=0,column=0,floor=0,QEbool=0,len=20;
void login();
void reserve();
void viewseat();
void reservation();
void DelAll();
void initialize_seat();
void initialize_file();
void first_initialize(){
    fl=fopen("A_Reservation.txt","r");
    if(fl==NULL){
        initialize_seat();
        initialize_file();
        fclose(fl);
    }
    fclose(fl);
    return;
}
void admin_clear();
void admin_viewseat();
void write_reservation();
int process();
int admin_process();
int reservecmp();
int viewseatcmp();
int reservationcmp();
int clearcmp();
int QEcmp();
typedef struct strstruct
{
    char str[20];
    struct strstruct *next;
}strinit;
strinit* readstr();
strinit* seatcmp();
strinit* floorcmp();
strinit* timecmp();
strinit* error;
int main(){
    first_initialize();
    pday=day;
    error=(strinit*)malloc(sizeof(strinit));
    do
    {   
        printf("请输入(Login登录用户，Quit退出程序)：");
        scanf("%s",superstr);
        if(strcmp(superstr,"Quit")==0)
        {
            printf("感谢与你相遇，我们下次再见~\n");
            return 0;
        }
        if(strcmp(superstr,"Login")==0){
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
        scanf("%s",superstr);
        if(strcmp(superstr,"Admin")==0){
            strcpy(user,superstr);
            printf("管理您好!\n(若要切换用户请输入Exit退出当前用户)\n");
            do{
                QEbool=admin_process();
                if(QEbool==100)break;
                if(QEbool==200)return;
            }while(1);
            continue;
        }
        if(superstr[0]>='A'&&superstr[0]<='Z'&&superstr[1]=='\0'){
            strcpy(user,superstr);
            printf("登录成功，%s同学你好呀~\n(若要切换用户请输入Exit退出当前用户)\n",user);
            do{
                QEbool=process();
                if(QEbool==100)break;
                if(QEbool==200)return;
            }while(1);
            continue;
        }
        else if(strcmp(superstr,"Quit")==0){
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
int process(){    
    int superbool=0;
    strinit *head=NULL;
    head=readstr();
    if((superbool=reservecmp(head))==0)
        if((superbool=viewseatcmp(head))==0)
            if((superbool=reservationcmp(head))==0)
                superbool=QEcmp(head);
    switch(superbool){
        case 0:printf("输入错误~\n");break;
        case 1:reserve();break;
        case 2:viewseat();break;
        case 3:reservation();break;
        case 100:return 100;
        case 200:return 200;
    }
    DelAll(head);
    return 0;
}
int admin_process(){    
    int superbool=0;
    strinit *head=NULL;
    head=readstr();
    if((superbool=clearcmp(head))==0)
        if((superbool=viewseatcmp(head))==0)
                superbool=QEcmp(head);
    switch(superbool){
        case 0:printf("输入错误~\n");break;
        case 2:admin_viewseat();break;
        case 4:admin_clear();break;
        case 100:return 100;
        case 200:return 200;
    }
    DelAll(head);
    return 0;
}
void DelAll(strinit *phead){
    if(phead==NULL)return;
    DelAll(phead->next);
    free(phead);
    phead=NULL;
}
strinit* readstr(){
    strinit *head=NULL,*temphead,*new;
    while(scanf("%s",superstr)){
        if(head==NULL){
            head=(strinit*)malloc(sizeof(strinit));
            strcpy(head->str,superstr);
            head->next=NULL;
            temphead=head;
        }else{
            new=(temphead->next=(strinit*)malloc(sizeof(strinit)));
            strcpy(new->str,superstr);
            new->next=NULL;
            temphead=new;
        }
        if(getchar()=='\n')return head;
    }
}
int reservecmp(strinit *tmpstruct){
    if(strcmp(tmpstruct->str,"Reserve")==0){
        if(tmpstruct->next==NULL)return 0;
        tmpstruct=tmpstruct->next;
        tmpstruct=timecmp(tmpstruct->str,tmpstruct);
        if(tmpstruct==error||tmpstruct==NULL)return 0;
        tmpstruct=floorcmp(tmpstruct->str,tmpstruct);
        if(tmpstruct==error||tmpstruct==NULL)return 0;
        tmpstruct=seatcmp(tmpstruct->str,tmpstruct);
        if(tmpstruct==NULL)return 1;
        else return 0;
    }else return 0;
}//比较输入指令符合reserve返回1否则返回0
int viewseatcmp(strinit *tmpstruct){
    tmpstruct=timecmp(tmpstruct->str,tmpstruct);
    if(tmpstruct==error||tmpstruct==NULL)return 0;
    tmpstruct=floorcmp(tmpstruct->str,tmpstruct);
    if(tmpstruct==NULL)return 2;
    else return 0;
}//比较输入指令符合viewseat返回2否则返回0
int reservationcmp(strinit *tmpstruct){
    if(strcmp(tmpstruct->str,"Reservation")==0&&tmpstruct->next==NULL)return 3;
    else return 0;
}//比较输入指令符合reservation返回3否则返回0
int clearcmp(strinit *tmpstruct){
    if(strcmp(tmpstruct->str,"Clear")==0&&tmpstruct->next==NULL)return 4;
    else return 0;
}//比较输入指令符合clear返回4否则返回0
strinit* timecmp(char *tmp,strinit *tmpstruct){
    if(strcmp(tmp,"Monday")==0){
        time=MONDAY;
        return tmpstruct->next;
    }
    if(strcmp(tmp,"Tuesday")==0){
        time=TUESDAY;
        return tmpstruct->next;
    }
    if(strcmp(tmp,"Wednesday")==0){
        time=WEDNESDAY;
        return tmpstruct->next;
    }
    if(strcmp(tmp,"Thursday")==0){
        time=THURSDAY;
        return tmpstruct->next;
    }
    if(strcmp(tmp,"Friday")==0){
        time=FRIDAY;
        return tmpstruct->next;
    }
    if(strcmp(tmp,"Saturday")==0){
        time=SATURDAY;
        return tmpstruct->next;
    }
    if(strcmp(tmp,"Sunday")==0){
        time=SUNDAY;
        return tmpstruct->next;
    }
    return error;
}//若符合“strx”(strx=Monday~Sunday)则返回strx的后一位字符串的地址，否则返回error对应的地址
strinit* floorcmp(char *tmp,strinit *tmpstruct){
    char op;
    if(strcmp(tmp,"Floor")==0){
        if(tmpstruct->next==NULL)return error;
        tmpstruct=tmpstruct->next;
        op=tmpstruct->str[0];
        if(op>='1'&&op<='5'){
            floor=op-'0';
            return tmpstruct->next;
        }else return error;
    }else return error;
}//若符合“Floor x”(x=1~5)则返回x的后一位字符串的地址，否则返回error对应的地址
strinit* seatcmp(char *tmp,strinit *tmpstruct){
    char op;
    if(strcmp(tmp,"Seat")==0){
        if(tmpstruct->next==NULL)return error;
        tmpstruct=tmpstruct->next;
        op=tmpstruct->str[0];
        if(op>='1'&&op<='9'){
            raw=op-'0';
            if(tmpstruct->next==NULL)return error;
            tmpstruct=tmpstruct->next;
            op=tmpstruct->str[0];
            if(op>='1'&&op<='9'){
                column=op-'0';
                return tmpstruct->next;
            }else return error;
        }else return error;
    }else return error;
}//若符合“Seat x x”(x=1~4)则返回第二个x的后一位字符串的地址，否则返回error对应的地址
int QEcmp(strinit *tmpstruct){
    if(strcmp(tmpstruct->str,"Exit")==0&&tmpstruct->next==NULL){
        user[0]='\0';
        printf("您已退出登录\n");
        return 100;
    }
    if(strcmp(tmpstruct->str,"Quit")==0&&tmpstruct->next==NULL){
        user[0]='\0';
        printf("感谢与你相遇，我们下次再见~\n");
        return 200;
    }
    return 0;
}//比较输入指令符合Exit返回100符合Quit返回200否则返回0
void reserve(){
    char* newtxt=(char*)malloc(sizeof(char)*len);
    snprintf(newtxt,len,"Time%cFloor%c.txt",time+'0',floor+'0');
    fl=fopen(newtxt,"r");
    if(fl==NULL){
        char* newtxt=(char*)malloc(sizeof(char)*len);
        snprintf(newtxt,len,"Time%cFloor%c.txt",time+'0',floor+'0');
        fl=fopen(newtxt,"w");
        fwrite(seat,sizeof(seat),1,fl);
        fclose(fl);
    }else fclose(fl);
    fl=fopen(newtxt,"r+");
    int i=0,j=0;
    do{
        char op=fgetc(fl);
        if(i==column-1&&j==raw-1&&op!=' '&&op!='\n'){
            if(op=='0')
            {
                fseek(fl,-1,SEEK_CUR);
                fputc(user[0],fl);
                free(newtxt);
                fclose(fl);
                newtxt=NULL;
                fl=NULL;
                write_reservation();
                printf("座位预订成功~\n");
            }
            else printf("座位已被预订哦~\n");
            break;
        }
        i++;
        if(op=='\n'){
            i=0;
            j++;
        }
        if(op==EOF){
            printf("未找到该座位呢\n");
            break;
        }
    }while(1);
    free(newtxt);
    fclose(fl);
    newtxt=NULL;
    fl=NULL;
    return;
}
void viewseat(){
    char* newtxt=(char*)malloc(sizeof(char)*len);
    snprintf(newtxt,len,"Time%cFloor%c.txt",time+'0',floor+'0');
    fl=fopen(newtxt,"r");
    if(fl==NULL){
        newtxt=(char*)malloc(sizeof(char)*len);
        snprintf(newtxt,len,"Time%cFloor%c.txt",time+'0',floor+'0');
        fl=fopen(newtxt,"w");
        fwrite(seat,sizeof(seat),1,fl);
        fclose(fl);
    }else fclose(fl);
    fl=fopen(newtxt,"r");
    do{
        char op=fgetc(fl);
        if(op=='0')printf("0 ");
        if(op=='\n')printf("\n");
        if(op>='A'&&op<='Z'){
            if(op==user[0])printf("2 ");
            else printf("1 ");
        }
        if(op==EOF)break;
    }while(1);
    free(newtxt);
    fclose(fl);
    return;
}
void admin_viewseat(){
    char* newtxt=(char*)malloc(sizeof(char)*len);
    snprintf(newtxt,len,"Time%cFloor%c.txt",time+'0',floor+'0');
    fl=fopen(newtxt,"r");
    if(fl==NULL){
        newtxt=(char*)malloc(sizeof(char)*len);
        snprintf(newtxt,len,"Time%cFloor%c.txt",time+'0',floor+'0');
        fl=fopen(newtxt,"w");
        fwrite(seat,sizeof(seat),1,fl);
        fclose(fl);
    }else fclose(fl);
    fl=fopen(newtxt,"r");
    do{
        char op=fgetc(fl);
        if(op=='0')printf("0 ");
        if(op=='\n')printf("\n");
        if(op>='A'&&op<='Z'){
            printf("%c ",op);
        }
        if(op==EOF)break;
    }while(1);
    free(newtxt);
    fclose(fl);
    return;
}
void reservation(){
    char* newtxt=(char*)malloc(sizeof(char)*len);
    snprintf(newtxt,len,"%c_Reservation.txt",user[0]);
    fl=fopen(newtxt,"r");
    if(fl==NULL){
        char* newtxt=(char*)malloc(sizeof(char)*len);
        snprintf(newtxt,len,"%c_Reservation.txt",user[0]);
        fl=fopen(newtxt,"w");
        fclose(fl);
    }else fclose(fl);
    fl=fopen(newtxt,"r");
    int tmptime,tmpfloor,tmpraw,tmpcolumn,i=0;
    do{
        char op=fgetc(fl);
        if(op==' ')i++;
        if(i==0&&op>='0')tmptime=op-'0';
        if(i==1&&op>='0')tmpfloor=op;
        if(i==2&&op>='0')tmpraw=op;
        if(i==3&&op>='0')tmpcolumn=op;
        if(op=='\n'){
            printf("%s Floor %c Seat %c %c",pday[tmptime],tmpfloor,tmpraw,tmpcolumn);
            printf("\n");
        }
        if(op==EOF)break;
    }while(1);
    free(newtxt);
    fclose(fl);
    return;
}
void admin_clear(){
    initialize_seat();
    initialize_file();
    printf("所有预约信息已全部取消\n");
    return;
}
void write_reservation(){
    char* newtxt=(char*)malloc(sizeof(char)*len);
    snprintf(newtxt,len,"%c_Reservation.txt",user[0]);
    fl=fopen(newtxt,"r");
    if(fl==NULL){
        char* newtxt=(char*)malloc(sizeof(char)*len);
        snprintf(newtxt,len,"%c_Reservation.txt",user[0]);
        fl=fopen(newtxt,"w");
        fclose(fl);
    }else fclose(fl);
    fl=fopen(newtxt,"a");
    free(newtxt);
    newtxt=(char*)malloc(sizeof(char)*len);
    snprintf(newtxt,len,"%c %c %c %c\n",time+'0',floor+'0',raw+'0',column+'0');
    fputs(newtxt,fl);
    free(newtxt);
    fclose(fl);
    return;
}
void initialize_file(){
    for(int i=0;i<=6;i++){
        for(int j=1;j<=5;j++){
            char* newtxt=(char*)malloc(sizeof(char)*len);
            snprintf(newtxt,len,"Time%cFloor%c.txt",i+'0',j+'0');
            fl=fopen(newtxt,"w");
            fwrite(seat,sizeof(seat),1,fl);
            fclose(fl);
            free(newtxt);
            fl=NULL;
            newtxt=NULL;
        }
    }
    for(int i=0;i<=25;i++){
        char* newtxt=(char*)malloc(sizeof(char)*len);
        snprintf(newtxt,len,"%c_Reservation.txt",'A'+i);
        fl=fopen(newtxt,"w");
        fclose(fl);
        free(newtxt);
        fl=NULL;
        newtxt=NULL;
    }
}
void initialize_seat(){
    memset(seat,' ',sizeof(seat));
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++)seat[i][j]='0';
    }
    for(int i=0;i<=10;i++)seat[i][10]='\n';
    return;
}