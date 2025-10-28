#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char seat[11][11];
int len=20;
FILE *fl;
void cleaall();
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
typedef struct strstruct
{
    char str[20];
    struct strstruct *next;
}strinit;
strinit* floorcmp();
strinit* error;
int main(){
    initialize_seat();
    initialize_file();
    return 0;
}
void initialize_seat(){
    memset(seat,' ',sizeof(seat));
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++)seat[i][j]='0';
    }
    for(int i=0;i<=10;i++)seat[i][10]='\n';
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